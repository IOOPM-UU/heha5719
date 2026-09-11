#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char *argv[]) 
{
    if (argc < 2 || argc > 3) {
        puts("Fel antal argument");
    }
    else {
    int n = atoi(argv[1]);
    float tmp = sqrt(n);
    int limit = floor(tmp) + 1;
    for (int a = 2; a < limit; a++) {
        for (int b = 2; b < n; b++) {
            if ((a * b) == n) {
                printf("%d is not a prime number", n);
                return 0;
            }
            else {
            }
        }
    }
    printf("%d is a prime number\n", n);
    return 0;
    }
}


