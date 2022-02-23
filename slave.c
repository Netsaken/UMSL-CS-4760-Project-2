#include <stdio.h>

int main(int argc, char *argv[]) {
    for (int i = 0; i < 5; i++) {
        // execute code to enter critical section;
        // sleep for random amount of time (between 0 and 5 seconds);
        // critical_section();
        // sleep for random amount of time (between 0 and 5 seconds);
        // execute code to exit from critical section;
    }

    printf("This is slave, reporting!\n");

    return 0;
}