#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>

#include "business.h"


void input_item(warehouse_t *wh){
    char *name = ask_question_string("Varans namn:");
    char *desc = ask_question_string("Varubeskrivning:");
    int price = ask_question_int("Varans kostnad (uttryckt i ören):");

    if(!add_item(wh, name, desc, price)){ // Frees the data even if the item exists
        printf("Varan finns redan\n");
    }
    free(name);
    free(desc);
    return;
}