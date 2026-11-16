#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>

#include "hash_table.h"
#include "hash_table_iterator.h"
#include "common.h"

struct entry
{
  elem_t key;    // holds the key
  elem_t value;  // holds the value
  entry_t *next; // points to the next entry (possibly NULL)
};

// Check for achievements (M39) and (O44) for using double pointers
struct hash_table
{
  size_t size;
  size_t bucket_amount;
  ioopm_hash_function *hash_fn;
  ioopm_eq_function *key_eq_fn;
  entry_t **buckets;
  double load;
  size_t prime_checker;
};

static size_t primes[] = {17, 31, 67, 127, 257, 509, 1021, 2053, 4099, 8191, 16381};

struct hash_table_iterator
{
  ioopm_hash_table_t *ht;
  size_t current_bucket;
  entry_t *current_entry;
};



static ioopm_hash_table_t *create_dynamic(ioopm_hash_table_t *ht, size_t primes_index, double load){
  ht->bucket_amount = primes[primes_index];
  ht->load = load;
  ht->prime_checker = 0;
  return ht;
}


ioopm_hash_table_t *ioopm_hash_table_create(ioopm_hash_function *hash_fn, ioopm_eq_function *key_eq_fn)
{
  ioopm_hash_table_t *new = calloc(1, sizeof(ioopm_hash_table_t));
  
  new->hash_fn = hash_fn;
  new->key_eq_fn = key_eq_fn;
  new = create_dynamic(new, 0, 0.75);
  new->buckets = calloc(new->bucket_amount, sizeof(entry_t*));
  new->prime_checker = 0;
  return new;
}

static void entry_destroy(entry_t *entry_remove)
{
  free(entry_remove);
}

static void iter_remove_all_entry(entry_t *entry_to_remove)
{
  entry_t *current = entry_to_remove;
  while (current != NULL)
  {
    entry_t *next = current->next;
    entry_destroy(current);
    current = next;
  }
}

/*static void recursive_remove_all_entry(entry_t *entry_to_remove)
{
  if (entry_to_remove == NULL)
  {
    return;
  }
  else
  {
    entry_t *next = entry_to_remove->next;
    entry_destroy(entry_to_remove);
    recursive_remove_all_entry(next);
  }
}
*/

void ioopm_hash_table_destroy(ioopm_hash_table_t *ht)
{
  for (size_t i = 0; i < ht->bucket_amount; i++)
  {
    entry_t *entry_to_remove = ht->buckets[i];     
    iter_remove_all_entry(entry_to_remove);
  }
  free(ht->buckets);
  free(ht);
  return;
}

static entry_t *entry_create(elem_t key, elem_t value, entry_t *next)
{
  entry_t *new = calloc(sizeof(entry_t), 1);
  new->key = key;
  new->value = value;
  new->next = next;
  return new;
}

/*static size_t string_knr_hash(const char *str)
{
  size_t result = 0;
  while (*str != '\0')
  {
    result = result * 31 + ((unsigned char)*str);
    str++;
  }
  return result;
}*/

static size_t hash_function(ioopm_hash_table_t *ht, elem_t key)
{
  return ht->hash_fn(key);
}

/*static entry_t *find_previous_entry(ioopm_hash_table_t *ht, elem_t key)
{
  size_t bucket = hash_function(ht, key) % No_Buckets;
  entry_t *previous = &ht->buckets[bucket];
  while (previous->next != NULL && !ht->key_eq_fn(previous->next->key, key))
  {
    previous = previous->next;
  }
  return previous;
}*/

static entry_t **find_previous_entry(ioopm_hash_table_t *ht, elem_t key){
  size_t bucket = hash_function(ht, key) % ht->bucket_amount;
  entry_t **previous = &ht->buckets[bucket];
  while(*previous != NULL && !ht->key_eq_fn((*previous)->key, key)){
    previous = &(*previous)->next;
  }
  return previous;
}

void scale_and_rehash(ioopm_hash_table_t *ht)
{
  ht->prime_checker += 1;
  size_t amount_of_new_buckets = primes[ht->prime_checker]; 
  entry_t** new_buckets = calloc(amount_of_new_buckets, sizeof(entry_t*));
  
  for (size_t i = 0; i < ht->bucket_amount; i++)
  {
    entry_t *current = ht->buckets[i];
    while(current != NULL){
      entry_t *save = current->next;
      size_t new_bucket = ht->hash_fn(current->key) % amount_of_new_buckets;
      current->next = new_buckets[new_bucket];
      new_buckets[new_bucket] = current;
      current = save;
    }
  }
  free(ht->buckets);   
  ht->buckets = new_buckets;
  ht->bucket_amount = amount_of_new_buckets;
}



void ioopm_hash_table_insert(ioopm_hash_table_t *ht, elem_t key, elem_t value_too_insert)
{
  entry_t **previous = find_previous_entry(ht, key);

  if((*previous) != NULL)  
  {
    (*previous)->value = value_too_insert;
    return;
  }
  else
  {
    *previous = entry_create(key, value_too_insert, NULL);
    size_t future_size = ht->size +=1;
    if((double)future_size / ht->bucket_amount > ht->load){
      scale_and_rehash(ht);
    }
  }
}

bool ioopm_hash_table_lookup(ioopm_hash_table_t *ht, elem_t key, elem_t *result)
{
  // look for an entry with the key we want
  entry_t **previous = find_previous_entry(ht, key);
  // if the key exists, return the value, otherwise, indicate that the lookup failed
  if (*previous != NULL)
  {
    *result = (*previous)->value;
    return true;
  }
  else
  {
    return false;
  }
}

bool ioopm_hash_table_remove(ioopm_hash_table_t *ht, elem_t key, elem_t *result)
{
  entry_t **previous = find_previous_entry(ht, key);
  entry_t *target = *previous;
  if (target == NULL)
  {
    return false;
  }
  else
  {
    *result = target->value;
    *previous = target->next;
    entry_destroy(target);
    ht->size -= 1;
    return true;
  }
}

bool ioopm_hash_table_has_key(ioopm_hash_table_t *ht, elem_t key)
{
  elem_t result;
  return ioopm_hash_table_lookup(ht, key, &result);
}

size_t ioopm_hash_table_size(ioopm_hash_table_t *ht)
{
  return ht->size;
}

bool ioopm_hash_table_is_empty(ioopm_hash_table_t *ht)
{
  return ioopm_hash_table_size(ht) > 0 ? false : true;
}

//ITERATOR

static void skip_empty_buckets(ioopm_hash_table_iterator_t *it)
{
  while (it->current_entry == NULL &&
         ++it->current_bucket < it->ht->bucket_amount)
  {
    it->current_entry = it->ht->buckets[it->current_bucket];
  }
}

ioopm_hash_table_iterator_t *ioopm_hash_table_iterator_create(ioopm_hash_table_t *ht)
{
  ioopm_hash_table_iterator_t *it = malloc(sizeof(ioopm_hash_table_iterator_t));
  it->ht = ht;
  it->current_bucket = 0;
  it->current_entry = ht->buckets[0];
  skip_empty_buckets(it);
  return it;
}

void ioopm_hash_table_iterator_destroy(ioopm_hash_table_iterator_t *it)
{
  free(it);
}


bool ioopm_hash_table_iterator_at_end(ioopm_hash_table_iterator_t *it)
{
  return it->current_bucket >= it->ht->bucket_amount;
}

void ioopm_hash_table_iterator_advance(ioopm_hash_table_iterator_t *it)
{
  assert(!ioopm_hash_table_iterator_at_end(it) && "iterator at end when advancing");
  it->current_entry = it->current_entry->next;
  skip_empty_buckets(it);
}

elem_t ioopm_hash_table_iterator_current_key(ioopm_hash_table_iterator_t *it)
{
  return it->current_entry->key;
}

elem_t ioopm_hash_table_iterator_current_value(ioopm_hash_table_iterator_t *it)
{
  return it->current_entry->value;
}
