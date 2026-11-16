#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
extern char *strdup(const char *);

typedef union { 
  int   int_value;
  float float_value;
  char *string_value;
  char symbol;
} answer_t;

void clear_input_buffer(void){
    int c;
    do
    {
        c = getchar();
    } 
    while (c != '\n' && c != EOF);
}

/*int ask_question_int(char *question)
{

  int result = 0;
  int conversions = 0;
  do
    {
      printf("%s\n", question);
      conversions = scanf("%d", &result);
      clear_input_buffer();
      putchar('\n');
    }
  while (conversions < 1);
  return result;
}*/

int read_string(char *buf, int buf_size){
  int counter = 0;
  int c;

  while(counter < buf_size - 1){
    c = getchar();
    if(c != '\n' ){
      buf[counter] = c;
      counter += 1;
    }
    if(c == '\n' && EOF){
      break;
    }
    if(counter == buf_size - 1){
      clear_input_buffer();
      break;
    }
    
  }
    buf[counter] = '\0';
    return counter;
}

/*char *ask_question_string(char *question, char *buf, int buf_size){
  int result;
  do{
    printf("%s\n", question);
    result = read_string(buf, buf_size);
  }
  while(result == 0);
  return buf;
}*/

typedef bool check_func(char*);
typedef answer_t convert_func(char*);

bool is_number(char *str){
    int length = strlen(str);
    if(str[0] == '-' || isdigit(str[0])){
        if(str[0] == '-' && length == 1){
            return false;
        }
        for(int i = 1; i < length; i++){
            char symbol = str[i];
            if(!isdigit(symbol)){
                return false;
            }
        }
        return true;
    }
    return false;
}

bool not_empty(char *str) {
  return strlen(str) > 0;
}

bool correct_shelf(char *shelf){
  int length = strlen(shelf);
  if(length == 3){
    if(!isupper(shelf[0])){
      return false;
    }
    for(int i = 1; i < length; i++){
      if(!isdigit(shelf[i])){
        return false;
      }
    }
    return true;
  }
  return false;
}

bool accepted_menu(char *choice){
  size_t length = strlen(choice);
  char *accepted = "AaLlDdEeSsPpCcRr+-=OoQq";
  for(size_t i = 0; i < strlen(accepted); i ++){
    if(choice[0] == accepted[i]){
      return true;
    }
  }
  return false;
}

answer_t ask_question(char *question, check_func *check, convert_func *convert)
{
  int buf_size = 250;
  char buf[buf_size];
  do {
    printf("%s\n", question);
    read_string(buf, buf_size);
  } while(!check(buf));
  return convert(buf);
}

char *ask_question_string(char *question) {
  return ask_question(question, not_empty, (convert_func *) strdup).string_value;
}

int ask_question_int(char *question){
  answer_t answer = ask_question(question, is_number, (convert_func *) atoi);
  return answer.int_value;
}

char *ask_question_shelf(char *question){
  return ask_question(question, correct_shelf, (convert_func *) strdup).string_value;
}

void print_menu(){
  char *add = "[A]dd merchandise";
  char *list = "[L]ist merchandise";
  char *remove = "Remove merchandise with [D]";
  char *edit = "[E]dit merchandise";
  char *show = "[S]how stock";
  char *replenish = "Re[P]lenish stock";
  char *create_cart = "[C]reate cart";
  char *rm_cart = "[R]emove cart";
  char *add_to_cart = "Add a new cart with [+]";
  char *rm_from_cart = "Remove from cart with [-]";
  char *calc_cost = "Calculate the cost with [=]";
  char *checkout = "Check[O]ut";
  char *quit = "[Q]uit";

  fprintf(stdout,"%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n",add, list, remove, edit, show, replenish, create_cart, rm_cart, add_to_cart, rm_from_cart, calc_cost, checkout, quit);
}

char ask_question_menu(){
  int buf_size = 50;
  char buf[buf_size];
  do {
    print_menu();
    read_string(buf, buf_size);
    putchar('\n');
  }while(!accepted_menu(buf));
  return toupper(buf[0]);
}

