#ifndef __UTILS_H__
#define __UTILS_H__
#include <stdbool.h>
extern char *strdup(const char *);


typedef union { 
  int   int_value;
  float float_value;
  char *string_value;
} answer_t;

typedef bool(check_func)(char *);
typedef answer_t(convert_func)(char *);

int read_string(char *buf, int buf_siz);
answer_t ask_question(char *question, check_func *check, convert_func *convert);
bool is_number(char *str);
bool not_empty(char *str);
bool shelfcheck(char *str);
int ask_question_int(char *question);
char *ask_question_string(char *question); 
char *ask_question_shelf(char *question);
void print(char *strängen);
void println(char *strängen);
#endif 
