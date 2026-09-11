#include <stdio.h>
void print(char *strängen) {
    char *start = strängen;
    for (; *start != '\0'; start++) {
        putchar(*start);
    }
}

int main(void) {
    print("geege\n");
}