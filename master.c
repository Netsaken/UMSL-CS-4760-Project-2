#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int main(int argc, char *argv[])
{
    int option;
    int s = 100;
    int n = 2;
    int max_n = 20;

    int *sharedInts;
    bool *sharedBools;

    //Construct format for "perror"
    char* title = argv[0];
    char report[10] = ": shm";
    char* message;

    //Command line option
    while ((option = getopt(argc, argv, ":t:")) != -1) {
        switch (option) {
        case 't':
            //Maximum time before termination
            s = atoi(optarg);
            break;
        case 'h':
        case '?':
            printf("Usage: %s [-t # (maximum time running)] # (number of processes to run)\n", argv[0]);
            return 1;
        default:
            break;
        }
    }
    
    //Get the argument for number of options, if it exists
    if (argv[optind] != NULL) {
        n = atoi(argv[optind]);

        //Check for invalid entries
        if (n > max_n) {
            printf("Sorry, the maximum allowed processes for this program is %i.\n", max_n);
            printf("Number of processes has been set to %i...\n\n", max_n);
            n = max_n;
        } else if (n < 1) {
            printf("There was an error with your input. Please only use numbers.\n");
            printf("Number of processes has been set to 1...\n\n");
            n = 1;
        }
    }

    //Initialize shared memory
    int shmid_int = shmget(IPC_PRIVATE, n*sizeof(int), IPC_CREAT | 0666);
    if (shmid_int == -1) {
        strcpy(report, ": shmget");
        message = strcat(title, report);
        perror(message);
        return 1;
    }

    int shmid_bool = shmget(IPC_PRIVATE, n*sizeof(bool), IPC_CREAT | 0666);
    if (shmid_bool == -1) {
        strcpy(report, ": shmget");
        message = strcat(title, report);
        perror(message);
        return 1;
    }

    //Attach shared memory
    sharedInts = shmat(shmid_int, NULL, 0);
    if (sharedInts == (void *) -1) {
        strcpy(report, ": shmat");
        message = strcat(title, report);
        perror(message);
        return 1;
    }

    sharedBools = shmat(shmid_bool, NULL, 0);
    if (sharedBools == (void *) -1) {
        strcpy(report, ": shmat");
        message = strcat(title, report);
        perror(message);
        return 1;
    }

    //Detach shared memory
    if (shmdt(sharedInts) == -1) {
        strcpy(report, ": shmdt");
        message = strcat(title, report);
        perror(message);
        return 1;
    }

    if (shmdt(sharedBools) == -1) {
        strcpy(report, ": shmdt");
        message = strcat(title, report);
        perror(message);
        return 1;
    }

    //Remove shared memory
    if (shmctl(shmid_int, IPC_RMID, 0) == -1) {
        strcpy(report, ": shmctl");
        message = strcat(title, report);
        perror(message);
        return 1;
    }

    if (shmctl(shmid_bool, IPC_RMID, 0) == -1) {
        strcpy(report, ": shmctl");
        message = strcat(title, report);
        perror(message);
        return 1;
    }

    //Do stuff...
    printf("This is master, reporting!\n");
    printf("S is %i, N is %i\n", s, n);

    return 0;
}