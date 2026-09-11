#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

void print_number(int num) { 
        if (num % 15 == 0) {
            printf("FizzBuzz, ");
        }
        else if (num % 5 == 0) {
            printf("Buzz, ");
        }
        else if (num % 3 == 0) {
            printf("Fizz, ");
        }
        else {
            printf("%d, ", num);
        }
}


int main(int argc, char *argv[]) {
    int T = atoi(argv[1]);
    if (argc == 2) {
        for (int i = 1; i <= T; i++) {
           print_number(i);
    }}
    else {
        printf("Fel input\n");
    }
}

