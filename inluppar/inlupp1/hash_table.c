#include "hash_table.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

//This is a great example for both M39 and O44!

#define No_Buckets 17

typedef struct entry entry_t;

struct entry
{
  char *key;     // holds the key
  int value;     // holds the value
  entry_t *next; // points to the next entry (possibly NULL)
};



struct hash_table
{
  // DODGE: hard-coding number of buckets as 17.
  // NOTE: addressing this dodge is optional.
  entry_t buckets[No_Buckets];
};

ioopm_hash_table_t *ioopm_hash_table_create(void) {
  /// Allocate space for a ioopm_hash_table_t = 17 pointers to entry_t's
  /// Allocate zeroed-out space for a ioopm_hash_table_t = 17 pointers to entry_t's
  return calloc(1, sizeof(ioopm_hash_table_t));
}

static size_t string_knr_hash(const char *str)
{
  size_t result = 0;
  while (*str != '\0')
  {
    result = result * 31 + ((unsigned char) *str);
    str++;
  }
  return result;
}

static entry_t *entry_create(char *key, int value, entry_t *next)
{
  entry_t *entry = calloc(1, sizeof(entry_t));
  // TODO: Stub
  entry->key = key;
  entry->value = value;
  entry->next = next;
  return entry;
}

static void entry_destroy(entry_t *entry) {
  free(entry);
}


void ioopm_hash_table_destroy(ioopm_hash_table_t *ht) {
    for (int i = 0; i < No_Buckets; i++) {
      entry_t *current = ht->buckets[i].next;
      while (current != NULL)  {
        entry_t *next = current->next;
        entry_destroy(current);
        current = next;
      }
    }
    free(ht);
}


static entry_t *find_previous_entry(ioopm_hash_table_t *ht, char *key) {

   size_t bucket = string_knr_hash(key) % No_Buckets;
   entry_t *current = &ht->buckets[bucket];
   while (current->next != NULL && strcmp(current->next->key, key) != 0) {
      current = current->next;
   }
   return current;
}

int ioopm_hash_table_remove(ioopm_hash_table_t *ht, char *key) {
  entry_t *previous = find_previous_entry(ht, key);
  if (previous->next != NULL && strcmp(previous->next->key, key) == 0) {
    int deleted = previous->next->value;
    // If previous is A then put C into A's next thereby jumping over B
    entry_t *new_next = previous->next->next;
    entry_destroy(previous->next);
    previous->next = new_next;
    return deleted;
  }
  else {
    return 0;
  }
}


void ioopm_hash_table_insert(ioopm_hash_table_t *ht, char *key, int value)
{
  // find previous entry, or the last entry if the key does not exist
  entry_t *previous = find_previous_entry(ht, key);

 // if the key exists, update the value, otherwise create a new entry
  if (previous->next != NULL)
  {
    previous->next->value = value;
  }
  else
  {
    previous->next = entry_create(key, value, NULL);
  }
}

bool ioopm_hash_table_lookup(ioopm_hash_table_t *ht, char *key, int *result)
{
  size_t bucket = string_knr_hash(key) % No_Buckets;
  // look for an entry with the key we want
  entry_t *current = ht->buckets[bucket].next;
  while (current != NULL && strcmp(current->key, key) != 0)
  {
    current = current->next;
  }

  // if the key exists, return the value, otherwise, indicate that the lookup failed
  if (current != NULL)
  {
    *result = current->value;
    return true;
  }
  else
  {
    return false;
  }
}


