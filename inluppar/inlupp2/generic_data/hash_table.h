#include <stdbool.h>
#include <stddef.h>
#include "common.h"
#pragma once

/**
* @file hash_table.h
* @author Lowe lindin, Lucas stenros
* @date 2026-09-22
* @brief Simple hash table that maps string keys to integer values.
*
* Here typically goes a more extensive explanation of what the header
* defines. Doxygens tags are words preceeded by either a backslash @\
* or by an at symbol @@.
*
*/


typedef struct entry entry_t;
typedef struct hash_table ioopm_hash_table_t;

/// @brief Create a new hash table
/// @return A new empty hash table
ioopm_hash_table_t *ioopm_hash_table_create(ioopm_hash_function *hash_fn, ioopm_eq_function *key_eq_fn);

/// @brief Delete a hash table and free its memory
/// @param ht a hash table to be deleted
void ioopm_hash_table_destroy(ioopm_hash_table_t *ht);

/// @brief add key => value entry in hash table ht
/// @param ht hash table operated upon
/// @param key key to insert
/// @param value value to insert
void ioopm_hash_table_insert(ioopm_hash_table_t *ht, elem_t key, elem_t value);

/// @brief lookup value for key in hash table ht
/// @param ht hash table operated upon
/// @param key key to lookup
/// @return true if the value is in the hash table, side effect where the value is put at the address for result
bool ioopm_hash_table_lookup(ioopm_hash_table_t *ht, elem_t key, elem_t *result);

/// @brief remove any mapping from key to a value
/// @param ht hash table operated upon
/// @param key key to remove
/// @return true if the value was removed, side effect where the value is put at the address for result
bool ioopm_hash_table_remove(ioopm_hash_table_t *ht, elem_t key, elem_t *result);

/// @brief check if a key exists in the hash table
/// @param ht hash table to look in
/// @param key the key to look for
/// @return true if the key is in the hash table
bool ioopm_hash_table_has_key(ioopm_hash_table_t *ht, elem_t key);

/// @brief Checks if a hash table is empty
/// @param ht the hash table to check
/// @return true if the hash table is empty, otherwise false
bool ioopm_hash_table_is_empty(ioopm_hash_table_t *ht);

/// @brief Gets the size of given hashtable
/// @param ht Hashtable to look in
/// @return Number of elements in hashtable
size_t ioopm_hash_table_size(ioopm_hash_table_t *ht);
