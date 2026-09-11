#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include "utils.h" 

int main() {
    int talet = random() % 1024;
    int guesscount = 0;
    char* namnet = ask_question_string("Skriv in ditt namn: ");
    printf("Du %s,", namnet);
    int gissning = ask_question_int("jag tänker på ett tal ... kan du gissa vilket?"); 
    do {
        if (gissning == talet) {
            guesscount++;
            break; 
        }
        else if (gissning > talet) {
            gissning = ask_question_int("För stort!");
            guesscount++;
        }
        else {
            gissning = ask_question_int("För litet!");
            guesscount++;
        }
    }
    while (guesscount < 15 && gissning != talet);
    if (guesscount >= 15) {
        printf("Nu har du slut på gissningar! Jag tänkte på talet %d\n", talet);
    }
    else {
        printf("Bingo!\n Det tog %s %d att komma fram till %d\n", namnet, guesscount, talet);
    }
    return 0;
}