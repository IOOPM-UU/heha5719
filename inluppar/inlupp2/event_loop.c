#include "utils.h"
#include "business.h"
#include "ui.h"
#include <stdio.h>
#include <string.h>

int main(void){
    char input;
    do{
    warehouse_t *wh = create_warehouse();
    input = ask_question_menu();
    if(input == 'A'){
        input_item(wh);
    }
    } while(input != 'Q');

    return 0;
}