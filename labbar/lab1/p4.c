#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) 
{
    if (argc < 2 || argc > 3) {
        puts("Fel antal argument");
    }
    else {
    int counter = 0;
    int columner = 0;
    int num1 = atoi(argv[1]);
    int num2 = atoi(argv[2]);
    for (int nummer = num2; columner < num1; columner++) {
        for (int i = 1; i <= nummer; i++) {
            printf("*");
            counter++;
        }
    printf("\n");
    nummer = nummer + num2;
    }
    printf("Totalt: %d\n", counter);
    return 0;

}}
