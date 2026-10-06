#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "hash_table.h"
#include "hash_table_iterator.h"
#include "common.h"

#define Delimiters "+-#@()[]{}.,:;!? \t\n\r"

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

size_t string_hash(elem_t key)
{
  return string_knr_hash(key.s);
}

bool string_eq(elem_t a, elem_t b) {
  return strcmp(a.s, b.s) == 0;
}

/// @brief Process a single word, updating its frequency
/// @param word the word to process
/// @param ht a hash table containing the frequencies of the words found so far
void process_word(char *word, ioopm_hash_table_t *ht)
{
  elem_t result;
  if (ioopm_hash_table_lookup(ht, string_elem(word), &result)) {
    ioopm_hash_table_insert(ht, string_elem(word), int_elem(result.i + 1));
  }
  else {
  char* word_copy = strdup(word);
  ioopm_hash_table_insert(ht, string_elem(word_copy), int_elem(1));
  }
}
/// @brief Process a single file, updating the frequencies of its words
/// @param filename the name of the file to process
/// @param ht a hash table containing the frequencies of the words found so far
void process_file(char *filename, ioopm_hash_table_t *ht)
{
  FILE *f = fopen(filename, "r");
  while (true)
  {
    char *buf = NULL;
    size_t len = 0;
    getline(&buf, &len, f);
    if (feof(f))
    {
      free(buf);
      break;
    }
    for (char *word = strtok(buf, Delimiters);
         word && *word;
         word = strtok(NULL, Delimiters))
    {
      process_word(word, ht);
    }
    free(buf);
  }
  fclose(f);
}

/// @brief A word together with its frequency
struct freq_word
{
  elem_t word;
  elem_t freq;
};

/// @brief Compare the frequency of two freq_words through pointers to them
/// @param p1 the first freq_word
/// @param p2 the second freq_word
/// @return a number @n@:
///     @n@ > 0  if @p1@'s frequency is higher than @p2@'s
///     @n@ < 0  if @p1@'s frequency is lower than @p2@'s
///     @n@ == 0 if @p1@'s frequency is equal to @p2@'s
static int cmp_freq_words(const void *p1, const void *p2)
{
  const struct freq_word *w1 = p1;
  const struct freq_word *w2 = p2;

  return w1->freq.i - w2->freq.i;
}

/// @brief Like @cmp_freq_words@ but with the comparison result reversed
static int cmp_freq_words_reverse(const void *p1, const void *p2)
{
  return -cmp_freq_words(p1, p2);
}

/// @brief Sort an array of @freq_word@s in descending frequency order
/// @param words the array to be sorted
/// @param no_words the number of elements in the array
void sort_freq_words(struct freq_word words[], size_t no_words)
{
  qsort(words, no_words, sizeof(struct freq_word), cmp_freq_words_reverse);
}

int main(int argc, char *argv[])
{
  if (argc < 2)
  {
    printf("Usage: %s file1 ... filen", argv[0]);
    return 1;
  }

  ioopm_hash_table_t *ht = ioopm_hash_table_create(string_hash, string_eq);

  for (int i = 1; i < argc; ++i)
  {
    process_file(argv[i], ht);
  }

  size_t size = ioopm_hash_table_size(ht);
  struct freq_word freq_words[size];

  // Iterate over hash table to dump its words and frequencies into the array above
  ioopm_hash_table_iterator_t *it = ioopm_hash_table_iterator_create(ht);

  size_t i = 0;

  while (!ioopm_hash_table_iterator_at_end(it)) {
    freq_words[i].word = ioopm_hash_table_iterator_current_key(it);
    freq_words[i].freq = ioopm_hash_table_iterator_current_value(it);
    i++; 

    ioopm_hash_table_iterator_advance(it);
  }
  sort_freq_words(freq_words, size);

  for (size_t i = 0; i < size; ++i)
  {
    printf("%s: %d\n", freq_words[i].word.s, freq_words[i].freq.i);
  }

  // Frees memory
  ioopm_hash_table_iterator_destroy(it);

  ioopm_hash_table_iterator_t *cleanup_it = ioopm_hash_table_iterator_create(ht);
  while (!ioopm_hash_table_iterator_at_end(cleanup_it))
  {
    elem_t key = ioopm_hash_table_iterator_current_key(cleanup_it);
    free(key.s);
    ioopm_hash_table_iterator_advance(cleanup_it);
  }
  ioopm_hash_table_iterator_destroy(cleanup_it);
  ioopm_hash_table_destroy(ht);
}
