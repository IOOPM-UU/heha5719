#include <stdio.h>
int main(void) 
{
    int counter = 0;
    int nummer = 1; 
    char *asterisk = "*";
    for (int nummer = 1; nummer < 11; nummer++) {
        for (int i = 1; i <= nummer; i++) {
            printf("%s", asterisk);
            counter++;
        }
    printf("\n");
    }
    printf("Totalt: %d\n", counter);
}   