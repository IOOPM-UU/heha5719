#pragma once
#include <stddef.h>
#include <stdbool.h>
#include "common.h"


/**
* @file hash_table.h
* @author Henrik Harmén and Alexander Brundin
* @date 14/09/26
* @brief Simple hash table that maps string keys to integer values.
*
* Here typically goes a more extensive explanation of what the header
* defines. Doxygens tags are words preceeded by either a backslash @\
* or by an at symbol @@.
*
*/

typedef struct hash_table ioopm_hash_table_t;

/// @brief Create a new hash table
/// @return A new empty hash table

ioopm_hash_table_t *ioopm_hash_table_create(ioopm_hash_function *hash_fn, ioopm_eq_function *key_eq_fn);

void ioopm_hash_table_destroy(ioopm_hash_table_t *ht);

/// @brief add key => value entry in hash table ht
/// @param ht hash table operated upon
/// @param key key to insert
/// @param value value to insert
void ioopm_hash_table_insert(ioopm_hash_table_t *ht, elem_t key, elem_t value);

/// @brief lookup value for key in hash table ht
/// @param ht hash table operated upon
/// @param key key to lookup
/// @return the value mapped to by key (FIXME: what if the key does not exist?)
bool ioopm_hash_table_lookup(ioopm_hash_table_t *ht, elem_t key, elem_t *result);

/// @brief remove any mapping from key to a value
/// @param ht hash table operated upon
/// @param key key to remove
/// @return the value mapped to by key (FIXME: what if the key does not exist?)
bool ioopm_hash_table_remove(ioopm_hash_table_t *ht, elem_t key, elem_t *result);

// TODO: documentation
bool ioopm_hash_table_has_key(ioopm_hash_table_t *ht, elem_t key);

// TODO: documentation
bool ioopm_hash_table_is_empty(ioopm_hash_table_t *ht);

// TODO: documentation
size_t ioopm_hash_table_size(ioopm_hash_table_t *ht);