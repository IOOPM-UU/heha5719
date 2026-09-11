/// passthrough.c
#include <stdio.h>

int main(void)
{
  int c = getchar();
  int safety = 1024;

  while (c != EOF && --safety > 0)
  {
    putchar(c);
    c = getchar();
  }

  return 0;
}
