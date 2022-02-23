#include <stdio.h>

const int n = 5;

bool choosing[n];
int number[n];

int main(int argc, char *argv[]) {
    printf("This is master, reporting!\n");

    return 0;
}

void process_i(const int i) /* ith Process */
{
    do {
        choosing[i] = true;
        //number[i] = 1 + max(number[0], ..., number[n - 1]);
        choosing[i] = false;
        for (int j = 0; j < n; j++) {
            while (choosing[j]) {
                ; // Wait if j happens to be choosing
            }
            while ( (number[j] != 0) 
            && (number[j] < number[i] || (number[j] == number[i] && j < i)) ) {
                ;
            }
        }
        //critical_section();

        number[i] = 0;
        //remainder_section();
    } while (1);
}