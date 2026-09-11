/// cat.c
#include <stdio.h>

void cat(char *filename)
{
  FILE *f = fopen(filename, "r");
  int c = fgetc(f);

  int counter = 1;
  fprintf(stdout, "%d    ", counter);
  while (c != EOF)
  {
    if (c == '\n') {
        counter++;
        fputc('\n', stdout);
        fprintf(stdout, "%d    ", counter);
    }
    fputc(c, stdout);
    c = fgetc(f);
  }
  fclose(f);
}

int main(int argc, char *argv[])
{
  if (argc < 2)
  {
    fprintf(stdout, "Usage: %s fil1 ...\n", argv[0]);
  }
  else
  {
    for (int i = 1; i < argc; ++i)
    {
      cat(argv[i]);
    }
  }

  return 0;
}