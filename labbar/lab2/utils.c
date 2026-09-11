#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include "utils.h" 

extern char *strdup(const char *);

int read_string(char *buf, int buf_siz) {
    int avslut = buf_siz - 1;
    int counter = 0; 
    for (int i = 0; i < avslut; i++) {
          int c = getchar(); 
          if (c == '\n' && EOF) {
            break;
        }
          buf[counter] = c;
          counter++;
    }
    buf[counter] = '\0';
    return counter; 
}

bool is_number(char *str) {
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


bool not_empty(char *str)
{
  return strlen(str) > 0;
}

answer_t ask_question(char *question, check_func *check, convert_func *convert) {
    int buf_siz = 100; 
    char bufen[buf_siz];
    do { 
      printf("%s\n", question);
      read_string(bufen, buf_siz);
    } while (!check(bufen));
      return convert(bufen); 
}

char *ask_question_string(char *question)
{
  return ask_question(question, not_empty, (convert_func *) strdup).string_value;
}


/* char *ask_question_string(char *question, char *buf, int buf_siz) {
  do
    {
      printf("%s\n", question);
      int räknaren = read_string(buf, buf_siz);
      int c;
      do {
        c = getchar();
      }
      while (c != '\n');
      putchar('\n');
    }
  while (strlen(buf) == 0);
  return strdup(buf);
}
*/

int ask_question_int(char *question)
{
  answer_t answer = ask_question(question, is_number, (convert_func *) atoi);
  return answer.int_value; // svaret som ett heltal
}

/* int ask_question_int(char *question)
{
  int result = 0;
  int conversions = 0;
  do
    {
      printf("%s\n", question);
      conversions = scanf("%d", &result);
      int c;
      do
        {
          c = getchar();
        }
      while (c != '\n');
      putchar('\n');
    }
  while (conversions < 1);
  return result;
}
*/

