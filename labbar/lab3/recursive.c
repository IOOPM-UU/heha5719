#include <stdio.h>
#include <stdlib.h>

typedef int int_fold_func(int, int);

/*
/// Den intressanta delen av programmet
int fib(int num) {
  int ppf = 0; // the two given fib values
  int pf  = 1;
  if (num == 0) {
     return 0;
  }
  if (num == 1) {
      return 1;
  }
  if (num >= 2) {
     return fib(num-1) + fib(num-2);
  }
}

/// Den ointressanta main()-funktionen
int main(void)
{
    int test = fib(10);
    printf("Detta är resultatet %d\n", test);
    return 0;
}
*/

long sum(int numbers[], int numbers_siz)
{
    return foldl_int_int(numbers, numbers_siz, add);
}

int foldl_int_int(int numbers[], int numbers_siz, int_fold_func *f)
{
  int result = 0;

  // Loopa över arrayen och för varje element e utför result = f(result, e)
  for (int i = 0; i < numbers_siz; ++i)
  {
    result = f(result, numbers[i]);
  }

  return result;
}

int add(int a, int b)
{
  return a + b;
}