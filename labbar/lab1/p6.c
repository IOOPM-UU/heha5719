#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

bool is_number(char *str)
{
    int length = strlen(str);
    for (int i = 0; i < length; i++){
        if (isdigit(str[i]) == false) {
            return false;
        }
        else {
        }
    }
  return true;
}


int main(int argc, char *argv[]) 
{
    if (argc < 2 || argc > 3) {
        puts("Fel antal argument");
    }
    else {
        int a = atoi(argv[1]);
        int a2 = atoi(argv[1]);
        int b = atoi(argv[2]);
        int b2 = atoi(argv[2]);
        if (is_number(argv[1]) && is_number(argv[2]) && a >= 0 && b >= 0) {
            while (a > 0 || b > 0) {
            if (a == b) {
                printf("gcd(%d,%d) = %d\n", a2, b2, a);
                return 0; 
            }
            if (a > b) {
                a = a - b;
            }
            else {
                b = b - a;
            }
          }
        }
        else {
            return printf("Not a positive number\n");
        }
}}