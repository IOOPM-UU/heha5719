#include <CUnit/Basic.h>
#include "hash_table.h"
#include "hash_table_iterator.h"
#include <string.h>
#include "linked_list.h"
#include "list_iterator.h"
#include "common.h"

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

int init_suite(void) {
  // Change this function if you want to do something *before* you
  // run a test suite
  return 0;
}



int clean_suite(void) {
  // Change this function if you want to do something *after* you
  // run a test suite
  return 0;
}

// These are example test functions. You should replace them with
// functions of your own.

void test_create_destroy(void) {
    ioopm_hash_table_t *ht = ioopm_hash_table_create(string_hash, string_eq);
    CU_ASSERT_PTR_NOT_NULL(ht);
    ioopm_hash_table_destroy(ht);
}

// If succesfully inserted should return true.

void test_insert_once() {
  // create new hash table
  ioopm_hash_table_t *ht = ioopm_hash_table_create(string_hash, string_eq);

  elem_t key = string_elem("abc");
  elem_t value = int_elem(123);

  // check that key is not in ht
  elem_t result = int_elem(0);
  CU_ASSERT_FALSE(ioopm_hash_table_lookup(ht, key, &result));
  CU_ASSERT_EQUAL(result.i, 0);

  // insert key-value pair and check that the mapping exists
  ioopm_hash_table_insert(ht, key, value);
  CU_ASSERT_TRUE(ioopm_hash_table_lookup(ht, key, &result));
  CU_ASSERT_EQUAL(result.i, value.i);

  // destroy hash table
  ioopm_hash_table_destroy(ht);
}

void test_key_exist() {
  ioopm_hash_table_t *ht = ioopm_hash_table_create(string_hash, string_eq);
  // Create and insert one value
  elem_t key = string_elem("abc");
  elem_t result = int_elem(0); 
  elem_t value1 = int_elem(123);
  ioopm_hash_table_insert(ht, key, value1);
  CU_ASSERT_TRUE(ioopm_hash_table_lookup(ht, key, &result));
  CU_ASSERT_EQUAL(result.i, value1.i);

  // Test replacing the first value with another
  elem_t value2 = int_elem(321);
  ioopm_hash_table_insert(ht, key, value2);
  CU_ASSERT_TRUE(ioopm_hash_table_lookup(ht, key, &result));
  CU_ASSERT_EQUAL(result.i, value2.i);

  ioopm_hash_table_destroy(ht);
}

//remove existing value

//remove non existing value

void test_remove_exist() {
  // Inserta en entry
  ioopm_hash_table_t *ht = ioopm_hash_table_create(string_hash, string_eq);
  elem_t key = string_elem("abcde");
  elem_t value = int_elem(324);
  elem_t result = int_elem(0);
  ioopm_hash_table_insert(ht, key, value);
  CU_ASSERT_TRUE(ioopm_hash_table_lookup(ht, key, &result));
  CU_ASSERT_EQUAL(result.i, value.i);
  // Ta bort och kolla att nyckeln ej finns i hash-tablet längre
  ioopm_hash_table_remove(ht, key, &result);
  CU_ASSERT_FALSE(ioopm_hash_table_lookup(ht, key, &result));

  ioopm_hash_table_destroy(ht);
}

void test_remove_nonexist() {
  // Skapa key och hashtable
  ioopm_hash_table_t *ht = ioopm_hash_table_create(string_hash, string_eq);
  elem_t key = string_elem("abcde");
  elem_t result = int_elem(0);
  CU_ASSERT_FALSE(ioopm_hash_table_remove(ht, key, &result));

  ioopm_hash_table_destroy(ht);
}

//Create a hash table and check if it has some key k (it shouldn’t).


void test_has_key() {
  ioopm_hash_table_t *ht = ioopm_hash_table_create(string_hash, string_eq);
  elem_t key = string_elem("abcde");
  CU_ASSERT_FALSE(ioopm_hash_table_has_key(ht, key));

  ioopm_hash_table_destroy(ht);
}

//Create a hash table and insert some key k. Check if it has the key k (it should). Also check if it has some other key k2 (it shouldn’t).


void test_has_one_key() {
  ioopm_hash_table_t *ht = ioopm_hash_table_create(string_hash, string_eq);
  elem_t key = string_elem("abcde");
  elem_t key2 = string_elem("kdfkkd");
  elem_t value = int_elem(1);
  ioopm_hash_table_insert(ht, key, value);
  CU_ASSERT_TRUE(ioopm_hash_table_has_key(ht, key));
  CU_ASSERT_FALSE(ioopm_hash_table_has_key(ht, key2));

  ioopm_hash_table_destroy(ht);
}

//Create a hash table and insert keys k1, k2 and k3. Check if all three keys are present (they should be). Also check if it has some other key k4 (it shouldn’t).

void test_has_three_keys() {
  ioopm_hash_table_t *ht = ioopm_hash_table_create(string_hash, string_eq);
  elem_t key = string_elem("abcde");
  elem_t key2 = string_elem("kdfkkd");
  elem_t key3 = string_elem("ndvndnv");
  elem_t key4 = string_elem("xzzxxxx");
  elem_t value = int_elem(1);
  elem_t value2 = int_elem(2);
  elem_t value3 = int_elem(3);
  ioopm_hash_table_insert(ht, key, value);
  ioopm_hash_table_insert(ht, key2, value2);
  ioopm_hash_table_insert(ht, key3, value3);
  CU_ASSERT_TRUE(ioopm_hash_table_has_key(ht, key));
  CU_ASSERT_TRUE(ioopm_hash_table_has_key(ht, key2));
  CU_ASSERT_TRUE(ioopm_hash_table_has_key(ht, key3));
  CU_ASSERT_FALSE(ioopm_hash_table_has_key(ht, key4))

  ioopm_hash_table_destroy(ht);
}

//Create a hash table and insert key k, and immediately remove it. Check if has key k (it shouldn’t).

void test_insert_remove_key() {
  ioopm_hash_table_t *ht = ioopm_hash_table_create(string_hash, string_eq);
  elem_t key = string_elem("abc"); 
  elem_t value = int_elem(1);
  elem_t result = int_elem(0);
  ioopm_hash_table_insert(ht, key, value);
  ioopm_hash_table_remove(ht, key, &result);
  CU_ASSERT_FALSE(ioopm_hash_table_has_key(ht, key));

  ioopm_hash_table_destroy(ht);
}

//Create a hash table and insert keys k1, k2 and k3. Remove key k2. Check if it has keys k1 and k3 (it should). Check if it has key k2 (it shouldn’t).

void test_insert_remove_middle_key() {
  ioopm_hash_table_t *ht = ioopm_hash_table_create(string_hash, string_eq);
  elem_t key = string_elem("abcde");
  elem_t key2 = string_elem("kdfkkd");
  elem_t key3 = string_elem("ndvndnv");
  elem_t value = int_elem(1);
  elem_t value2 = int_elem(2);
  elem_t value3 = int_elem(3);
  elem_t result = int_elem(0);
  ioopm_hash_table_insert(ht, key, value);
  ioopm_hash_table_insert(ht, key2, value2);
  ioopm_hash_table_insert(ht, key3, value3);
  ioopm_hash_table_remove(ht, key2, &result);
  CU_ASSERT_TRUE(ioopm_hash_table_has_key(ht, key));
  CU_ASSERT_FALSE(ioopm_hash_table_has_key(ht, key2));
  CU_ASSERT_TRUE(ioopm_hash_table_has_key(ht, key3));

  ioopm_hash_table_destroy(ht);
}

//Size of empty hash table

void test_size_empty(void)
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create(string_hash, string_eq);
  CU_ASSERT_EQUAL(ioopm_hash_table_size(ht), 0);
  ioopm_hash_table_destroy(ht);
}


//Size of hash table with one insert

void test_size_one(void)
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create(string_hash, string_eq);
  elem_t key = string_elem("abc");
  elem_t value = int_elem(2);

  ioopm_hash_table_insert(ht, key, value);

  CU_ASSERT_EQUAL(ioopm_hash_table_size(ht), 1);

  ioopm_hash_table_destroy(ht);
}


//Size of hash table with multiple inserts

void test_size_multiple(void)
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create(string_hash, string_eq);
  elem_t key = string_elem("abcde");
  elem_t key2 = string_elem("kdfkkd");
  elem_t key3 = string_elem("ndvndnv");
  elem_t value = int_elem(1);
  elem_t value2 = int_elem(2);
  elem_t value3 = int_elem(3);

  ioopm_hash_table_insert(ht, key, value);
  ioopm_hash_table_insert(ht, key2, value2);
  ioopm_hash_table_insert(ht, key3, value3);

  CU_ASSERT_EQUAL(ioopm_hash_table_size(ht), 3);

  ioopm_hash_table_destroy(ht);
}


//Removing an element after multiple insertions to check size

void test_size_after_remove(void)
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create(string_hash, string_eq);
  elem_t key = string_elem("abcde");
  elem_t key2 = string_elem("kdfkkd");
  elem_t key3 = string_elem("ndvndnv");
  elem_t value = int_elem(1);
  elem_t value2 = int_elem(2);
  elem_t value3 = int_elem(3);
  elem_t result = int_elem(0);
  ioopm_hash_table_insert(ht, key, value);
  ioopm_hash_table_insert(ht, key2, value2);
  ioopm_hash_table_insert(ht, key3, value3);
  //Remove one insert
  ioopm_hash_table_remove(ht, key2, &result);
  CU_ASSERT_EQUAL(ioopm_hash_table_size(ht), 2);

  ioopm_hash_table_destroy(ht);
}

//Empty hashtable

void test_hash_table_is_empty(void) 
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create(string_hash, string_eq);
  CU_ASSERT_TRUE(ioopm_hash_table_is_empty(ht));

  ioopm_hash_table_destroy(ht);
}

//Iterating over an empty hash table


void test_iterator_empty()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create(string_hash, string_eq);

  ioopm_hash_table_iterator_t *it = ioopm_hash_table_iterator_create(ht);

  CU_ASSERT_TRUE(ioopm_hash_table_iterator_at_end(it));

  ioopm_hash_table_iterator_destroy(it);
  ioopm_hash_table_destroy(ht);
}

//Iterating over a hash table with one entry

void test_iterator_one_entry()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create(string_hash, string_eq);

  elem_t key = string_elem("abc");

  elem_t value = int_elem(123);

  ioopm_hash_table_insert(ht, key, value);

  ioopm_hash_table_iterator_t *it =
    ioopm_hash_table_iterator_create(ht);

  CU_ASSERT_FALSE(ioopm_hash_table_iterator_at_end(it));

  CU_ASSERT_STRING_EQUAL(ioopm_hash_table_iterator_current_key(it).s, "abc");

  CU_ASSERT_EQUAL(ioopm_hash_table_iterator_current_value(it).i, 123);

  ioopm_hash_table_iterator_destroy(it);
  ioopm_hash_table_destroy(ht);
}

//Iterating over a hash table with several entries

void test_iterator_several_entries()
{
  elem_t keys[3] = {string_elem("abc"), string_elem("qwe"), string_elem("asd")};
  elem_t values[3] = {int_elem(0), int_elem(1), int_elem(2)};

  ioopm_hash_table_t *ht = ioopm_hash_table_create(string_hash, string_eq);

  for (size_t i = 0; i < 3; ++i)
  {
    ioopm_hash_table_insert(ht, keys[i], values[i]);
  }

  size_t iteration_count = 0;

  ioopm_hash_table_iterator_t *it = ioopm_hash_table_iterator_create(ht);

  while (!ioopm_hash_table_iterator_at_end(it))
  {
    iteration_count++;
    ioopm_hash_table_iterator_advance(it);
  }

  CU_ASSERT_EQUAL(iteration_count, 3);

  ioopm_hash_table_iterator_destroy(it);
  ioopm_hash_table_destroy(ht);
}

//Making sure that every inserted key-value pair is visited exactly once

void test_iterator_every_entry_once()
{
  elem_t keys[3] = {string_elem("abc"), string_elem("qwe"), string_elem("asd")};
  elem_t values[3] = {int_elem(10), int_elem(20), int_elem(30)};

  int counts[3] = {0, 0, 0};

  ioopm_hash_table_t *ht = ioopm_hash_table_create(string_hash, string_eq);

  for (size_t i = 0; i < 3; ++i)
  {
    ioopm_hash_table_insert(ht, keys[i], values[i]);
  }

  ioopm_hash_table_iterator_t *it = ioopm_hash_table_iterator_create(ht);

  while (!ioopm_hash_table_iterator_at_end(it))
  {
    elem_t key = ioopm_hash_table_iterator_current_key(it);
    elem_t value = ioopm_hash_table_iterator_current_value(it);

    if (strcmp(key.s, "abc") == 0)
      {
        counts[0]++;
        CU_ASSERT_EQUAL(value.i, 10);
      }
    else if (strcmp(key.s, "qwe") == 0)
      {
        counts[1]++;
        CU_ASSERT_EQUAL(value.i, 20);
      }
    else if (strcmp(key.s, "asd") == 0)
      {
        counts[2]++;
        CU_ASSERT_EQUAL(value.i, 30);
      }
    else
      {
        CU_FAIL("Iterator visited an unexpected key");
      }
      ioopm_hash_table_iterator_advance(it);
    }
  CU_ASSERT_EQUAL(counts[0], 1);
  CU_ASSERT_EQUAL(counts[1], 1);
  CU_ASSERT_EQUAL(counts[2], 1);

  ioopm_hash_table_iterator_destroy(it);
  ioopm_hash_table_destroy(ht);
}

//Iterating over a hash table with several entries in the same bucket

void test_iterator_same_bucket(void)
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create(string_hash, string_eq);

  elem_t value = int_elem(1);
  elem_t value2 = int_elem(2);
  elem_t value3 = int_elem(3);
  elem_t key = string_elem("a");
  elem_t key2 = string_elem("b");
  elem_t key3 = string_elem("c");

  ioopm_hash_table_insert(ht, key, value);
  ioopm_hash_table_insert(ht, key2, value2);
  ioopm_hash_table_insert(ht, key3, value3);

  ioopm_hash_table_iterator_t *it =
    ioopm_hash_table_iterator_create(ht);

  size_t count = 0;

  while (!ioopm_hash_table_iterator_at_end(it))
  {
    count++;
    ioopm_hash_table_iterator_advance(it);
  }
  CU_ASSERT_EQUAL(count, 3);

  ioopm_hash_table_iterator_destroy(it);
  ioopm_hash_table_destroy(ht);
}




// LINKED LIST TESTS








//Create linked list

void test_list_create(void) {
  ioopm_list_t *list = ioopm_list_create();

  CU_ASSERT_PTR_NOT_NULL(list);

  ioopm_list_destroy(list);
}

//Destroy linked list and checks that it doesn't crash

void test_list_destroy(void) {
  ioopm_list_t *list = ioopm_list_create();

  ioopm_list_destroy(list);
}

//Append linked list

void test_list_append(void)
{
  ioopm_list_t *list = ioopm_list_create();

  ioopm_list_append(list, int_elem(10));

  CU_ASSERT_EQUAL(ioopm_list_size(list), 1);
  CU_ASSERT_EQUAL(ioopm_list_get(list, 0).i, 10);

  ioopm_list_destroy(list);
}


// Get from linked list

void test_list_get(void)
{
  ioopm_list_t *list = ioopm_list_create();

  ioopm_list_append(list, int_elem(10));

  CU_ASSERT_EQUAL(ioopm_list_get(list, 0).i, 10);

  ioopm_list_destroy(list);
}


// Head of linked list

void test_list_head(void)
{
  ioopm_list_t *list = ioopm_list_create();

  ioopm_list_append(list, int_elem(10));
  ioopm_list_append(list, int_elem(20));

  CU_ASSERT_EQUAL(ioopm_list_head(list).i, 10);

  ioopm_list_destroy(list);
}


// Insert in linked list

void test_list_insert(void)
{
  ioopm_list_t *list = ioopm_list_create();

  ioopm_list_append(list, int_elem(10));
  ioopm_list_append(list, int_elem(30));

  ioopm_list_insert(list, 1, int_elem(20));

  CU_ASSERT_EQUAL(ioopm_list_get(list, 1).i, 20);

  ioopm_list_destroy(list);
}


// Is linked list empty?

void test_list_empty(void)
{
  ioopm_list_t *list = ioopm_list_create();

  CU_ASSERT_TRUE(ioopm_list_is_empty(list));

  ioopm_list_append(list, int_elem(10));

  CU_ASSERT_FALSE(ioopm_list_is_empty(list));

  ioopm_list_destroy(list);
}


// Last of linked list

void test_list_last(void)
{
  ioopm_list_t *list = ioopm_list_create();

  ioopm_list_append(list, int_elem(10));
  ioopm_list_append(list, int_elem(20));

  CU_ASSERT_EQUAL(ioopm_list_last(list).i, 20);

  ioopm_list_destroy(list);
}


// Remove from linked list

void test_list_remove(void)
{
  ioopm_list_t *list = ioopm_list_create();

  ioopm_list_append(list, int_elem(10));
  ioopm_list_append(list, int_elem(20));
  ioopm_list_append(list, int_elem(30));

  elem_t removed = ioopm_list_remove(list, 1);

  CU_ASSERT_EQUAL(removed.i, 20);
  CU_ASSERT_EQUAL(ioopm_list_size(list), 2);
  CU_ASSERT_EQUAL(ioopm_list_get(list, 0).i, 10);
  CU_ASSERT_EQUAL(ioopm_list_get(list, 1).i, 30);

  ioopm_list_destroy(list);
}


// Prepend to linked list

void test_list_prepend(void)
{
  ioopm_list_t *list = ioopm_list_create();

  ioopm_list_prepend(list, int_elem(20));
  ioopm_list_prepend(list, int_elem(10));

  CU_ASSERT_EQUAL(ioopm_list_size(list), 2);
  CU_ASSERT_EQUAL(ioopm_list_get(list, 0).i, 10);
  CU_ASSERT_EQUAL(ioopm_list_get(list, 1).i, 20);

  ioopm_list_destroy(list);
}


// Check size of linked list

void test_list_size(void)
{
  ioopm_list_t *list = ioopm_list_create();

  CU_ASSERT_EQUAL(ioopm_list_size(list), 0);

  ioopm_list_append(list, int_elem(10));

  CU_ASSERT_EQUAL(ioopm_list_size(list), 1);

  ioopm_list_destroy(list);
}





// ITERATOR TESTS

// Checks that the iterator has been created

void test_iterator_create(void)
{
    ioopm_list_t *list = ioopm_list_create();
    ioopm_list_append(list, int_elem(1));

    ioopm_list_iterator_t *it = ioopm_list_iterator_create(list);

    CU_ASSERT_EQUAL(ioopm_list_iterator_current(it).i, 1);

    ioopm_list_iterator_destroy(it);
    ioopm_list_destroy(list);
}

// Checks that no memory leaks appear

void test_iterator_destroy(void)
{
    ioopm_list_t *list = ioopm_list_create();
    ioopm_list_iterator_t *it = ioopm_list_iterator_create(list);

    ioopm_list_iterator_destroy(it);

    ioopm_list_destroy(list);
}

// Checks that the iterator is at the end

void test_iterator_at_end(void)
{
    ioopm_list_t *empty = ioopm_list_create();
    ioopm_list_iterator_t *it = ioopm_list_iterator_create(empty);

    CU_ASSERT_TRUE(ioopm_list_iterator_at_end(it));

    ioopm_list_iterator_destroy(it);
    ioopm_list_destroy(empty);
}

// Checks so the iterator is same as in the list

void test_iterator_current(void)
{
    ioopm_list_t *list = ioopm_list_create();
    ioopm_list_append(list, int_elem(1));

    ioopm_list_iterator_t *it = ioopm_list_iterator_create(list);

    CU_ASSERT_EQUAL(ioopm_list_iterator_current(it).i, 1);

    ioopm_list_iterator_destroy(it);
    ioopm_list_destroy(list);
}

// Checks that the iterator moves forward when called

void test_iterator_advance(void)
{
    ioopm_list_t *list = ioopm_list_create();
    ioopm_list_append(list, int_elem(1));
    ioopm_list_append(list, int_elem(2));

    ioopm_list_iterator_t *it = ioopm_list_iterator_create(list);

    CU_ASSERT_EQUAL(ioopm_list_iterator_current(it).i, 1);

    ioopm_list_iterator_advance(it);

    CU_ASSERT_EQUAL(ioopm_list_iterator_current(it).i, 2);

    ioopm_list_iterator_destroy(it);
    ioopm_list_destroy(list);
}

int main() {
  // First we try to set up CUnit, and exit if we fail
  if (CU_initialize_registry() != CUE_SUCCESS)
    return CU_get_error();

  // We then create an empty test suite and specify the name and
  // the init and cleanup functions
  CU_pSuite my_test_suite = CU_add_suite("My awesome test suite", init_suite, clean_suite);
  CU_pSuite linked_list_suite = CU_add_suite("My linked list test suite", init_suite, clean_suite);

  if (my_test_suite == NULL || linked_list_suite == NULL) {
      // If the test suite could not be added, tear down CUnit and exit
      CU_cleanup_registry();
      return CU_get_error();
  }

  // This is where we add the test functions to our test suite.
  // For each call to CU_add_test we specify the test suite, the
  // name or description of the test, and the function that runs
  // the test in question. If you want to add another test, just
  // copy a line below and change the information
  if (
    (CU_add_test(my_test_suite, "Create destroy test", test_create_destroy) == NULL) ||
    (CU_add_test(my_test_suite, "No key with insert", test_insert_once) == NULL) ||
    (CU_add_test(my_test_suite, "Key exist with insert", test_key_exist) == NULL) ||
    (CU_add_test(my_test_suite, "Remove existing entry", test_remove_exist) == NULL) ||
    (CU_add_test(my_test_suite, "Remove non-existing entry", test_remove_nonexist) == NULL) ||
    (CU_add_test(my_test_suite, "Has a key", test_has_key) == NULL) ||
    (CU_add_test(my_test_suite, "Has one key", test_has_one_key) == NULL) ||
    (CU_add_test(my_test_suite, "Has three keys", test_has_three_keys) == NULL) ||
    (CU_add_test(my_test_suite, "Insert then remove key", test_insert_remove_key) == NULL) ||
    (CU_add_test(my_test_suite, "Insert then remove middle key", test_insert_remove_middle_key) == NULL) ||
    (CU_add_test(my_test_suite, "Empty size", test_size_empty) == NULL) ||
    (CU_add_test(my_test_suite, "Size of one entry", test_size_one) == NULL) ||
    (CU_add_test(my_test_suite, "Multiple entries size", test_size_multiple) == NULL) ||
    (CU_add_test(my_test_suite, "Size of entries after removal", test_size_after_remove) == NULL) ||
    (CU_add_test(my_test_suite, "Hash table is empty", test_hash_table_is_empty) == NULL) ||
    (CU_add_test(my_test_suite, "Iterating with empty hashtable", test_iterator_empty) == NULL) ||
    (CU_add_test(my_test_suite, "Iterating with a hashtable with one entry", test_iterator_one_entry) == NULL) ||
    (CU_add_test(my_test_suite, "Iterating over a iterator with multiple entries", test_iterator_several_entries) == NULL) ||
    (CU_add_test(my_test_suite, "Checking that there's one for every entry", test_iterator_every_entry_once) == NULL) ||
    (CU_add_test(my_test_suite, "Iterating over multiple entries in the same bucket", test_iterator_same_bucket) == NULL) ||
    (CU_add_test(linked_list_suite, "Create linked list", test_list_create) == NULL) ||
    (CU_add_test(linked_list_suite, "Destroy linked list", test_list_destroy) == NULL) ||
    (CU_add_test(linked_list_suite, "Append linked list", test_list_append) == NULL) ||
    (CU_add_test(linked_list_suite, "Get linked list", test_list_get) == NULL) ||
    (CU_add_test(linked_list_suite, "Head of linked list", test_list_head) == NULL) ||
    (CU_add_test(linked_list_suite, "Insert in linked list", test_list_insert) == NULL) ||
    (CU_add_test(linked_list_suite, "Is linked list empty", test_list_empty) == NULL) ||
    (CU_add_test(linked_list_suite, "Last of linked list", test_list_last) == NULL) ||
    (CU_add_test(linked_list_suite, "Remove linked list", test_list_remove) == NULL) ||
    (CU_add_test(linked_list_suite, "Prepend linked list", test_list_prepend) == NULL) ||
    (CU_add_test(linked_list_suite, "Size of linked list", test_list_size) == NULL) ||
    (CU_add_test(linked_list_suite, "Create", test_iterator_create) == NULL) ||
    (CU_add_test(linked_list_suite, "Destroy iterator", test_iterator_destroy) == NULL) ||
    (CU_add_test(linked_list_suite, "Iterator is at the end of the list", test_iterator_at_end) == NULL) ||
    (CU_add_test(linked_list_suite, "Current element of iterator", test_iterator_current) == NULL) ||
    (CU_add_test(linked_list_suite, "Advance in iterator", test_iterator_advance) == NULL) ||
    0 
  )
    {
      // If adding any of the tests fails, we tear down CUnit and exit
      CU_cleanup_registry();
      return CU_get_error();
    }

  // Set the running mode. Use CU_BRM_VERBOSE for maximum output.
  // Use CU_BRM_NORMAL to only print errors and a summary
  CU_basic_set_mode(CU_BRM_VERBOSE);

  // This is where the tests are actually run!
  CU_basic_run_tests();

  // Tear down CUnit before exiting
  CU_cleanup_registry();
  return CU_get_error();
}  