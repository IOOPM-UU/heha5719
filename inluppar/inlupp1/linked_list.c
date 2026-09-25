#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include "linked_list.h"

typedef struct link link_t;

struct link {
    int value;
    link_t *next;
};

struct list {
    link_t *head;
    link_t *last;
    int size; 
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

int ioopm_list_size(ioopm_list_t *list) {
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

void ioopm_list_append(ioopm_list_t *list, int value) {
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

void ioopm_list_prepend(ioopm_list_t *list, int value) {
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

int ioopm_list_head(ioopm_list_t *list) {
    return list->head->value;
}

int ioopm_list_last(ioopm_list_t *list) {
    return list->last->value;
}

void ioopm_list_insert(ioopm_list_t *list, int index, int value) {
    if (index == 0) {
        ioopm_list_prepend(list, value);
    }
    else if (index == ioopm_list_size(list)) {
        ioopm_list_append(list, value);
    }
    else if (index > ioopm_list_size(list) || index < 0) {
        printf("Incorrect index");
    }
    else {
        link_t *new_link = calloc(1, sizeof(link_t));
        new_link->value = value;
        link_t *current = list->head;
        for (int i = 0; i < index - 1; i++) {
            current = current->next;
        }
        new_link->next = current->next;
        current->next = new_link;
        list->size++;
    }
}

int ioopm_list_remove(ioopm_list_t *list, int index) {
    if (list->head == NULL || index >= ioopm_list_size(list) || index < 0) {
        printf("Nothing to remove");
        return 0;
    }
    else if (index == 0) {
        link_t *removed = list->head;
        int value = removed->value;
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
        for (int i = 0; i < index - 1; i++) {
            current = current->next;
        }
        link_t *removed = list->last;
        int value = removed->value;
        list->last = current;
        current->next = NULL;
        link_destroy(removed);
        list->size--;
        return value;
    }
    else {
        link_t *current = list->head;
        for (int i = 0; i < index - 1; i++) {
            current = current->next;
        }
        link_t *removed = current->next;
        int value = removed->value;
        current->next = current->next->next;
        link_destroy(removed); 
        list->size--;
        return value;
    }
}

int ioopm_list_get(ioopm_list_t *list, int index) {
    if (list->head == NULL || index >= ioopm_list_size(list) || index < 0) {
        printf("Not valid");
        return 0;
    }
    else {
    link_t *current = list->head;
    for (int i = 0; i < index; i++) {
        current = current->next;
    }
    return current->value;
    }
}





