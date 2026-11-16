#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>

#include "Headers/linked_list.h"
#include "Headers/list_iterator.h"
#include "Headers/common.h"

struct ioopm_list_element
{
    elem_t value;
    ioopm_list_element_t *tail;
};

struct list
{
    ioopm_list_element_t *first;
    ioopm_list_element_t *last;
    size_t size;
};

struct list_iterator
{
    ioopm_list_t *list;
    ioopm_list_element_t *current_element;
    size_t index;
};

ioopm_list_t *ioopm_list_create(void)
{
    ioopm_list_t *new = calloc(sizeof(ioopm_list_t), 1);
    new->size = 0;
    return new;
}

static ioopm_list_element_t *create_element(elem_t value)
{
    ioopm_list_element_t *new = calloc(sizeof(ioopm_list_element_t), 1);
    new->value = value;
    return new;
}

void ioopm_list_destroy(ioopm_list_t *list)
{
    ioopm_list_element_t *element = list->first;
    if (element == NULL)
    {
        free(list);
        return;
    }
    list->first = element->tail;
    free(element);
    ioopm_list_destroy(list);
}

static void list_first_node_create(ioopm_list_t *list, ioopm_list_element_t *element)
{
    list->first = element;
    list->last = element;
    list->size++;
}

static void list_insert_last_node(ioopm_list_t *list, ioopm_list_element_t *element)
{
    list->last->tail = element;
    list->last = element;
    list->size++;
}

static void list_insert_first_node(ioopm_list_t *list, ioopm_list_element_t *element)
{
    element->tail = list->first;
    list->first = element;
    list->size++;
}

static ioopm_list_element_t *find_previous_node(ioopm_list_t *list, size_t index)
{
    ioopm_list_element_t *previous = list->first;

    for (size_t i = 0; i < index - 1; i++)
    {
        previous = previous->tail;
    }
    return previous;
}

void ioopm_list_append(ioopm_list_t *list, elem_t value)
{
    ioopm_list_element_t *new = create_element(value);

    if (list->size == 0)
    {
        list_first_node_create(list, new);
    }
    else
    {
        list_insert_last_node(list, new);
    }
}

void ioopm_list_prepend(ioopm_list_t *list, elem_t value)
{
    ioopm_list_element_t *new = create_element(value);

    if (list->size == 0)
    {
        list_first_node_create(list, new);
        return;
    }
    else
    {
        ioopm_list_element_t *first = list->first;
        new->tail = first;
        list->first = new;
        list->size++;
    }
}

elem_t ioopm_list_head(ioopm_list_t *list)
{
    return list->first->value;
}

elem_t ioopm_list_last(ioopm_list_t *list)
{
    return list->last->value;
}

void ioopm_list_insert(ioopm_list_t *list, size_t index, elem_t value)
{
    size_t size = list->size;
    if (index > size)
    {
        return;
    }
    ioopm_list_element_t *new = create_element(value);

    if (list->size == 0)
    {
        list_first_node_create(list, new);
        return;
    }
    else if (index == 0)
    {
        list_insert_first_node(list, new);
        return;
    }
    else if (index == size)
    {
        list_insert_last_node(list, new);
        return;
    }

    ioopm_list_element_t *current = find_previous_node(list, index);
    new->tail = current->tail;
    current->tail = new;
    list->size++;
}

bool ioopm_list_remove(ioopm_list_t *list, size_t index, elem_t *result)
{
    size_t size = list->size;
    if (index >= size)
    {
        return false;
    }

    ioopm_list_element_t *current = list->first;
    if (index == 0)
    {
        *result = current->value;
        list->first = current->tail;
        free(current);
        list->size--;
        if (list->size == 0)
        {
            list->last = NULL;
        }
        return true;
    }

    current = find_previous_node(list, index);
    ioopm_list_element_t *to_remove = current->tail;
    if (index == size - 1)
    {
        list->last = current;
        *result = to_remove->value;
        free(to_remove);
        current->tail = NULL;
        list->size--;
        return true;
    }

    current->tail = to_remove->tail;
    *result = to_remove->value;
    free(to_remove);
    list->size--;
    return true;
}

bool ioopm_list_get(ioopm_list_t *list, size_t index, elem_t *result)
{
    if (index >= list->size)
    {
        return false;
    }
    else if (index == 0)
    {
        *result = list->first->value;
        return true;
    }

    ioopm_list_element_t *element = find_previous_node(list, index);
    *result = element->tail->value;
    return true;
}

size_t ioopm_list_size(ioopm_list_t *list)
{
    return list->size;
}

/*
//Normal recursive
size_t list_size_recursive(ioopm_list_element_t *element){
    if(element == NULL){
        return 0;
    }
    return 1 + (list_size_recursive(element->tail));
}

//Tail recursive
static size_t list_length_recursive(ioopm_list_element_t *element, size_t index){
    if(element == NULL){
        return index;
    }
    return list_length_recursive(element->tail, index + 1);
}

size_t ioopm_list_size(ioopm_list_t *list){
    return list_length_recursive(list->first, 0);
}
*/

bool ioopm_list_is_empty(ioopm_list_t *list)
{
    return ioopm_list_size(list) == 0 ? true : false;
}

// ITERATOR TYPESHIT

ioopm_list_iterator_t *ioopm_list_iterator_create(ioopm_list_t *l)
{
    ioopm_list_iterator_t *iter = calloc(sizeof(ioopm_list_iterator_t), 1);
    iter->list = l;
    iter->index = 0;
    if (iter->list->size == 0)
    {
        iter->current_element = NULL;
        return iter;
    }
    iter->current_element = l->first;
    return iter;
}

void ioopm_list_iterator_destroy(ioopm_list_iterator_t *iter)
{
    free(iter);
}

bool ioopm_list_iterator_at_end(ioopm_list_iterator_t *iter)
{
    return iter->current_element == NULL;
}

void ioopm_list_iterator_advance(ioopm_list_iterator_t *iter)
{
    assert(!ioopm_list_iterator_at_end(iter) && "iterator at end when advancing");
    iter->current_element = iter->current_element->tail;
    iter->index++;
}

elem_t ioopm_list_iterator_current(ioopm_list_iterator_t *iter)
{
    return iter->current_element->value;
}

bool ioopm_list_iterator_remove(ioopm_list_iterator_t *iter, elem_t *removed)
{
    ioopm_list_element_t *to_remove = iter->current_element;
    if (to_remove == NULL)
    {
        return false;
    }

    ioopm_list_element_t *next = to_remove->tail;
    if (ioopm_list_remove(iter->list, iter->index, removed))
    {
        iter->current_element = next;
        return true;
    }
    return false;
}

void ioopm_list_iterator_insert(ioopm_list_iterator_t *iter, elem_t value)
{
    ioopm_list_insert(iter->list, iter->index, value);

    if (iter->index == 0)
    {
        iter->current_element = iter->list->first;
    }
    else
    {
        ioopm_list_element_t *previous = find_previous_node(iter->list, iter->index);
        iter->current_element = previous->tail;
    }
}
