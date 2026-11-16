#pragma once

typedef union elem
{
    int int_value;
    unsigned int uint_value;
    bool bool_value;
    float float_value;
    void *pointer;
    char *string;
} elem_t;

typedef struct list ioopm_list_t;
typedef struct ioopm_list_element ioopm_list_element_t;
typedef struct list ioopm_list_t;
typedef struct list_iterator ioopm_list_iterator_t;
