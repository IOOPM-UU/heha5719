#include <CUnit/Basic.h>
#include "hash_table.h"

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
    ioopm_hash_table_t *ht = ioopm_hash_table_create();
    CU_ASSERT_PTR_NOT_NULL(ht);
    ioopm_hash_table_destroy(ht);
}

// If succesfully inserted should return true.

void test_insert_once() {
  // create new hash table
  ioopm_hash_table_t *ht = ioopm_hash_table_create();

  char *key = "abc";
  int value = 123;

  // check that key is not in ht
  int result = 0;
  CU_ASSERT_FALSE(ioopm_hash_table_lookup(ht, key, &result));
  CU_ASSERT_EQUAL(result, 0);

  // insert key-value pair and check that the mapping exists
  ioopm_hash_table_insert(ht, key, value);
  CU_ASSERT_TRUE(ioopm_hash_table_lookup(ht, key, &result));
  CU_ASSERT_EQUAL(result, value);

  // destroy hash table
  ioopm_hash_table_destroy(ht);
}

void test_key_exist() {
  ioopm_hash_table_t *ht = ioopm_hash_table_create();
  // Create and insert one value
  char *key = "abc";
  int result = 0; 
  int value1 = 123;
  ioopm_hash_table_insert(ht, key, value1);
  CU_ASSERT_TRUE(ioopm_hash_table_lookup(ht, key, &result));
  CU_ASSERT_EQUAL(result, value1);

  // Test replacing the first value with another
  int value2 = 321;
  ioopm_hash_table_insert(ht, key, value2);
  CU_ASSERT_TRUE(ioopm_hash_table_lookup(ht, key, &result));
  CU_ASSERT_EQUAL(result, value2);

  ioopm_hash_table_destroy(ht);
}

//remove existing value

//remove non existing value

void test_remove_exist() {
  // Inserta en entry
  ioopm_hash_table_t *ht = ioopm_hash_table_create();
  char *key = "abcde";
  int value = 324;
  int result = 0;
  ioopm_hash_table_insert(ht, key, value);
  CU_ASSERT_TRUE(ioopm_hash_table_lookup(ht, key, &result));
  CU_ASSERT_EQUAL(result, value);
  // Ta bort och kolla att nyckeln ej finns i hash-tablet längre
  ioopm_hash_table_remove(ht, key, &result);
  CU_ASSERT_FALSE(ioopm_hash_table_lookup(ht, key, &result));

  ioopm_hash_table_destroy(ht);
}

void test_remove_nonexist() {
  // Skapa key och hashtable
  ioopm_hash_table_t *ht = ioopm_hash_table_create();
  char *key = "abcde";
  int result = 0;
  CU_ASSERT_FALSE(ioopm_hash_table_remove(ht, key, &result));

  ioopm_hash_table_destroy(ht);
}

//Create a hash table and check if it has some key k (it shouldn’t).


void test_has_key() {
  ioopm_hash_table_t *ht = ioopm_hash_table_create();
  char *key = "abcde";
  CU_ASSERT_FALSE(ioopm_hash_table_has_key(ht, key));

  ioopm_hash_table_destroy(ht);
}

//Create a hash table and insert some key k. Check if it has the key k (it should). Also check if it has some other key k2 (it shouldn’t).


void test_has_one_key() {
  ioopm_hash_table_t *ht = ioopm_hash_table_create();
  char *key = "abcde";
  char *key2 = "kdfkkd";
  int value = 1;
  ioopm_hash_table_insert(ht, key, value);
  CU_ASSERT_TRUE(ioopm_hash_table_has_key(ht, key));
  CU_ASSERT_FALSE(ioopm_hash_table_has_key(ht, key2));

  ioopm_hash_table_destroy(ht);
}

//Create a hash table and insert keys k1, k2 and k3. Check if all three keys are present (they should be). Also check if it has some other key k4 (it shouldn’t).

void test_has_three_keys() {
  ioopm_hash_table_t *ht = ioopm_hash_table_create();
  char *key = "abcde";
  char *key2 = "kdfkkd";
  char *key3 = "ndvndnv";
  char *key4 = "xzzxxxx";
  int value = 1;
  int value2 = 2;
  int value3 = 3;
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
  ioopm_hash_table_t *ht = ioopm_hash_table_create();
  char *key = "abc"; 
  int value = 1;
  int result = 0;
  ioopm_hash_table_insert(ht, key, value);
  ioopm_hash_table_remove(ht, key, &result);
  CU_ASSERT_FALSE(ioopm_hash_table_has_key(ht, key));

  ioopm_hash_table_destroy(ht);
}

//Create a hash table and insert keys k1, k2 and k3. Remove key k2. Check if it has keys k1 and k3 (it should). Check if it has key k2 (it shouldn’t).

void test_insert_remove_middle_key() {
  ioopm_hash_table_t *ht = ioopm_hash_table_create();
  char *key = "abcde";
  char *key2 = "kdfkkd";
  char *key3 = "ndvndnv";
  int value = 1;
  int value2 = 2;
  int value3 = 3;
  int result = 0;
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
  ioopm_hash_table_t *ht = ioopm_hash_table_create();
  CU_ASSERT_EQUAL(ioopm_hash_table_size(ht), 0);
  ioopm_hash_table_destroy(ht);
}


//Size of hash table with one insert

void test_size_one(void)
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create();
  char *key = "abc";
  int value = 2;

  ioopm_hash_table_insert(ht, key, value);

  CU_ASSERT_EQUAL(ioopm_hash_table_size(ht), 1);

  ioopm_hash_table_destroy(ht);
}


//Size of hash table with multiple inserts

void test_size_multiple(void)
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create();
  char *key = "abcde";
  char *key2 = "kdfkkd";
  char *key3 = "ndvndnv";
  int value = 1;
  int value2 = 2;
  int value3 = 3;

  ioopm_hash_table_insert(ht, key, value);
  ioopm_hash_table_insert(ht, key2, value2);
  ioopm_hash_table_insert(ht, key3, value3);

  CU_ASSERT_EQUAL(ioopm_hash_table_size(ht), 3);

  ioopm_hash_table_destroy(ht);
}


//Removing an element after multiple insertions to check size

void test_size_after_remove(void)
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create();
  char *key = "abcde";
  char *key2 = "kdfkkd";
  char *key3 = "ndvndnv";
  int value = 1;
  int value2 = 2;
  int value3 = 3;
  int result = 0;
  ioopm_hash_table_insert(ht, key, value);
  ioopm_hash_table_insert(ht, key2, value2);
  ioopm_hash_table_insert(ht, key3, value3);
  //Remove one insert
  ioopm_hash_table_remove(ht, key2, &result);
  CU_ASSERT_EQUAL(ioopm_hash_table_size(ht), 2);

  ioopm_hash_table_destroy(ht);
}

void test_hash_table_is_empty(void) 
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create();
  CU_ASSERT_TRUE(ioopm_hash_table_is_empty(ht));
}






int main() {
  // First we try to set up CUnit, and exit if we fail
  if (CU_initialize_registry() != CUE_SUCCESS)
    return CU_get_error();

  // We then create an empty test suite and specify the name and
  // the init and cleanup functions
  CU_pSuite my_test_suite = CU_add_suite("My awesome test suite", init_suite, clean_suite);
  if (my_test_suite == NULL) {
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