#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include "linked_list.h"
#include "list_iterator.h"
#include "common.h"

typedef struct link link_t;

struct link {
    elem_t value;
    link_t *next;
};

struct list {
    link_t *head;
    link_t *last;
    size_t size; 
};

struct list_iterator {
    ioopm_list_t *list;
    link_t *current;
};

// Own subfunction for freeing one sublist

static void link_destroy(link_t *removed) {
    free(removed);
}

// Create new list

ioopm_list_t *ioopm_list_create(void) {
    return calloc(1, sizeof(ioopm_list_t));
}

// CHecks size for list

size_t ioopm_list_size(ioopm_list_t *list) {
    return list->size;
}

// Checks if the list is empty

bool ioopm_list_is_empty(ioopm_list_t *list) {
    if (ioopm_list_size(list) == 0) {
        return true;
    }
    else {
        return false;
    }
}


// Destroy an existing list

void ioopm_list_destroy(ioopm_list_t *list) {
    while (!ioopm_list_is_empty(list)) {
        ioopm_list_remove(list, 0);
    }
    free(list);
}

void ioopm_list_append(ioopm_list_t *list, elem_t value) {
    link_t *new_link = calloc(1, sizeof(link_t));
    new_link->value = value;
    new_link->next = NULL;
    if (list->last == NULL) {
        list->head = new_link;
        list->last = new_link;
        list->size++;
    }
    else {
    list->last->next = new_link;
    list->last = new_link;
    list->size++;
    }
}

void ioopm_list_prepend(ioopm_list_t *list, elem_t value) {
    link_t *new_link = calloc(1, sizeof(link_t));
    new_link->value = value; 
    new_link->next = list->head;
    if (list->head == NULL) {
      list->head = new_link;
      list->last = new_link;
      list->size++;
    }
    else {
      list->head = new_link;
      list->size++;
    }
}

elem_t ioopm_list_head(ioopm_list_t *list) {
    return list->head->value;
}

elem_t ioopm_list_last(ioopm_list_t *list) {
    return list->last->value;
}

void ioopm_list_insert(ioopm_list_t *list, size_t index, elem_t value) {
    if (index == 0) {
        ioopm_list_prepend(list, value);
    }
    else if (index == ioopm_list_size(list)) {
        ioopm_list_append(list, value);
    }
    else if (index > ioopm_list_size(list)) {
        printf("Incorrect index");
    }
    else {
        link_t *new_link = calloc(1, sizeof(link_t));
        new_link->value = value;
        link_t *current = list->head;
        for (size_t i = 0; i < index - 1; i++) {
            current = current->next;
        }
        new_link->next = current->next;
        current->next = new_link;
        list->size++;
    }
}

elem_t ioopm_list_remove(ioopm_list_t *list, size_t index) {
    if (list->head == NULL || index >= ioopm_list_size(list)) {
        printf("Nothing to remove");
        return (elem_t) {0};
    }
    else if (index == 0) {
        link_t *removed = list->head;
        elem_t value = removed->value;
        list->head = list->head->next;
        if (list->size == 1) {
            list->last = NULL;
        }
        link_destroy(removed);
        list->size--;
        return value;
    }
    else if (index == ioopm_list_size(list) - 1) {
        link_t *current = list->head;
        for (size_t i = 0; i < index - 1; i++) {
            current = current->next;
        }
        link_t *removed = list->last;
        elem_t value = removed->value;
        list->last = current;
        current->next = NULL;
        link_destroy(removed);
        list->size--;
        return value;
    }
    else {
        link_t *current = list->head;
        for (size_t i = 0; i < index - 1; i++) {
            current = current->next;
        }
        link_t *removed = current->next;
        elem_t value = removed->value;
        current->next = current->next->next;
        link_destroy(removed); 
        list->size--;
        return value;
    }
}

elem_t ioopm_list_get(ioopm_list_t *list, size_t index) {
    if (list->head == NULL || index >= ioopm_list_size(list)) {
        printf("Not valid");
        return (elem_t) {0};
    }
    else {
    link_t *current = list->head;
    for (size_t i = 0; i < index; i++) {
        current = current->next;
    }
    return current->value;
    }
}


// LIST ITERATOR PART


ioopm_list_iterator_t *ioopm_list_iterator_create(ioopm_list_t *l) {
    ioopm_list_iterator_t *iterator = calloc(1, sizeof(ioopm_list_iterator_t));
    iterator->list = l;
    iterator->current = l->head;

    return iterator;
}

void ioopm_list_iterator_destroy(ioopm_list_iterator_t *iter) {
    free(iter);
}

bool ioopm_list_iterator_at_end(ioopm_list_iterator_t *iter) {
    return iter->current == NULL;
}

elem_t ioopm_list_iterator_current(ioopm_list_iterator_t *iter) {
    if (iter->current == NULL) {
        return (elem_t) {0};
    }
    else {
    return iter->current->value;
    }
}

void ioopm_list_iterator_advance(ioopm_list_iterator_t *iter) {
    if (ioopm_list_iterator_at_end(iter)) {
        printf("List is unable to advance");
    }
    else {
        iter->current = iter->current->next;
    }
}

