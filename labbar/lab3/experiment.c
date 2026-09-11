#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include "utils.h" 

typedef union { 
  int   int_value;
  float float_value;
  char *string_value;
} answer_t;

typedef bool(check_func)(char *);
typedef answer_t(convert_func)(char *);

answer_t ask_question(char *question, check_func *check, convert_func *convert) {
    int buf_siz = 100; 
    char bufen[buf_siz];
    do { 
      printf("%s\n", question);
      read_string(bufen, buf_siz);
    } while (!check(bufen));
      return convert(bufen); 
}

