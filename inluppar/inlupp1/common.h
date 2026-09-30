#pragma once
#define int_elem(x)   ((elem_t) { .i = (x) })
#define bool_elem(x)  ((elem_t) { .b = (x) })
#define ptr_elem(x)   ((elem_t) { .p = (x) })
#define string_elem(x) ((elem_t) { .s = (x) })

#include <stdbool.h>

union elem
{
  int i;
  unsigned int u;
  bool b;
  float f;
  void *p;
  char *s;
};

typedef union elem elem_t;
typedef bool ioopm_eq_function(elem_t a, elem_t b);
typedef size_t ioopm_hash_function(elem_t key);


