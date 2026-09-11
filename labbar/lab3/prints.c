#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

void print(char *strängen) {
    int length = strlen(strängen);
    for (int i = 0; i < length; i++) {
        putchar(strängen[i]);
    }
}

void println(char *strängen) {
    int length = strlen(strängen);
    for (int i = 0; i < length; i++) {
        putchar(strängen[i]);
    }
    putchar('\n');
}

int main(void) {
    println("Shurda2");
}