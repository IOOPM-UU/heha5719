#pragma once
#include "hash_table.h"
#include <stdbool.h>

/**
* @file hash_table_iterator.h
* @author Lowe Lindin, Lucas Stenros
* @date 2026-09-16
* @brief Simple hash table iterator
*
* Hash table iterators provide an interface to iterate through all entries in a hash table.
* An iterator is either positioned at an entry, called the current entry, or it is positioned at-the-end, if it has already iterated through all entries.
* If the underlying hash table of an iterator is modified using any non-iterator function, the iterator is invalidated and should not be used anymore.
*
*/

typedef struct hash_table_iterator ioopm_hash_table_iterator_t;

/// @brief Create an iterator for a hash table.
/// @param ht hash table to iterate over
/// @return a new iterator positioned at the first entry if it exists, and positioned at-the-end if ht is empty
ioopm_hash_table_iterator_t *ioopm_hash_table_iterator_create(ioopm_hash_table_t *ht);

/// @brief Destroy an iterator and free its memory
/// @param it iterator to destroy
void ioopm_hash_table_iterator_destroy(ioopm_hash_table_iterator_t *it);

/// @brief Check if the current element exists, or equivalently, if it is positioned at an entry
/// @param it iterator operated upon
/// @return true iff the current element exists
bool ioopm_hash_table_iterator_at_end(ioopm_hash_table_iterator_t *it);

/// @brief Move the iterator forward to the next entry if it exists or to at-the-end if no more entries exist
/// @pre it is positioned at an entry
/// @param it iterator operated upon
void ioopm_hash_table_iterator_advance(ioopm_hash_table_iterator_t *it);

/// @brief Get the key of the current entry
/// @pre it is positioned at an entry
/// @param it iterator operated upon
/// @return the key of the current entry
elem_t ioopm_hash_table_iterator_current_key(ioopm_hash_table_iterator_t *it);

/// @brief Get the value of the current entry
/// @pre it is positioned at an entry
/// @param it iterator operated upon
/// @return the value if the current entry
elem_t ioopm_hash_table_iterator_current_value(ioopm_hash_table_iterator_t *it);