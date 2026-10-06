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
/// @param result modified value
/// @return true if the key exists and modify result and value, false if key to lookup doesn't exist and result is not modified
bool ioopm_hash_table_lookup(ioopm_hash_table_t *ht, elem_t key, elem_t *result);

/// @brief remove any mapping from key to a value
/// @param ht hash table operated upon
/// @param key key to remove
/// @param result value removed
/// @return true if the key exists and modify result and value, false if the key to remove doesn't exist and result is not modified
bool ioopm_hash_table_remove(ioopm_hash_table_t *ht, elem_t key, elem_t *result);

/// @brief checks if hash table has key
/// @param ht hash table operated upon
/// @param key key to lookup
/// @return true if hash table has key, false if key is not found in hash table
bool ioopm_hash_table_has_key(ioopm_hash_table_t *ht, elem_t key);

/// @brief checks if hash table is empty
/// @param ht hash table operated upon
/// @return true if hash table is empty, false if it has at least one element
bool ioopm_hash_table_is_empty(ioopm_hash_table_t *ht);

/// @brief checks size for hash table
/// @param ht hash table operated upon
/// @return size of the hash table
size_t ioopm_hash_table_size(ioopm_hash_table_t *ht);