#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

int string_length(char *stringen) {
    int length = 0;
    int index = 0;
    while (stringen[index] != '\0') { 
        index++;
        length++;
    }
    return length; 
}


int main(int argc, char *argv[])
{
  if (argc < 2)
  {
    printf("Usage: %s words or string", argv[0]);
  }
  else
  {
    for (int i = 1; i < argc; ++i)
    {
      int expected = strlen(argv[i]);
      int actual   = string_length(argv[i]);
      printf("strlen(\"%s\")=%d\t\tstring_length(\"%s\")=%d\n",
             argv[i], expected, argv[i], actual);
    }
  }
  return 0;
}

