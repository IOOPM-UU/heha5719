#include <CUnit/Basic.h>
#include "generic_data/linked_list.h"
#include "generic_data/list_iterator.h"
#include "generic_data/hash_table.h"
#include "generic_data/hash_table_iterator.h"
#include "generic_data/common.h"
#include "utils.h"
#include "business.h"

int init_suite(void)
{
  // Change this function if you want to do something *before* you
  // run a test suite
  return 0;
}

int clean_suite(void)
{
  // Change this function if you want to do something *after* you
  // run a test suite
  return 0;
}

// These are example test functions. You should replace them with
// functions of your own.

void test_correct_shelf(void){
  CU_ASSERT_FALSE(correct_shelf("a12"));
  CU_ASSERT_TRUE(correct_shelf("A12"));
  CU_ASSERT_FALSE(correct_shelf("Aa12"));
  CU_ASSERT_FALSE(correct_shelf("Ab2"));
  CU_ASSERT_FALSE(correct_shelf("A2"));
  CU_ASSERT_FALSE(correct_shelf("ABB2"));
  CU_ASSERT_TRUE(correct_shelf("Q00"));
}

void test_add(void){
  warehouse_t *wh = create_warehouse();
  CU_ASSERT_TRUE(add_item(wh, "gas", "bra gerjer", 1000));
  CU_ASSERT_FALSE(add_item(wh, "gas", "bra gerjer", 1000));
  CU_ASSERT_TRUE(add_item(wh, "gasssy", "bra gerjer", 1000));
  CU_ASSERT_TRUE(add_item(wh, "shurda", "bra gerjer", 1000));
  CU_ASSERT_TRUE(add_item(wh, "shurda2", "bra gerjer", 1000));
  CU_ASSERT_FALSE(add_item(wh, "shurda2", "bra gerjer", 1000));

  destroy_warehouse(wh);
}


void test_remove(void){
  warehouse_t *wh = create_warehouse();
  add_item(wh, "shurda", "anis da don", 1500);
  add_item(wh, "shurda2", "anis da don", 1500);
  add_item(wh, "shurda3", "anis da don", 1500);
  add_item(wh, "shurda4", "anis da don", 1500);

  CU_ASSERT_TRUE(remove_item(wh, "shurda"));
  CU_ASSERT_TRUE(add_item(wh, "shurda", "anis da don", 1500));
  CU_ASSERT_TRUE(remove_item(wh, "shurda"));
  CU_ASSERT_TRUE(remove_item(wh, "shurda2"));
  CU_ASSERT_TRUE(remove_item(wh, "shurda3"));
  CU_ASSERT_TRUE(remove_item(wh, "shurda4"));
  CU_ASSERT_FALSE(remove_item(wh, "shurda"));
  CU_ASSERT_FALSE(remove_item(wh, "yiipppsias"));


  destroy_warehouse(wh);
}

void test_edit(void){
  warehouse_t *wh = create_warehouse();

  CU_ASSERT_TRUE(add_item(wh, "shurda", "detta är shurda", 1000));
  CU_ASSERT_TRUE(add_item(wh, "shurda2", "detta är shurda2", 1000));
  CU_ASSERT_TRUE(add_item(wh, "shurda3", "detta är shurda3", 1000));
  CU_ASSERT_TRUE(add_item(wh, "shurda4", "detta är shurda4", 1000));

  CU_ASSERT_FALSE(edit_merch(wh, "sha", "sa", "as", 1000));
  CU_ASSERT_TRUE(edit_merch(wh, "shurda", "shurda55", "nya shurda", 50000));
  CU_ASSERT_FALSE(add_item(wh, "shurda55", "hasas", 1000));
  CU_ASSERT_TRUE(edit_merch(wh, "shurda55", "kslkso", "nya shurdasasas", 5002200));

  CU_ASSERT_TRUE(remove_item(wh, "kslkso"));
  destroy_warehouse(wh);

}

void test_replenish(void){
  warehouse_t *wh = create_warehouse();

  CU_ASSERT_TRUE(add_item(wh, "shurda", "detta är shurda", 1000));
  CU_ASSERT_TRUE(add_item(wh, "shurda2", "detta är shurda2", 1000));
  CU_ASSERT_TRUE(add_item(wh, "shurda3", "detta är shurda3", 1000));
  CU_ASSERT_TRUE(add_item(wh, "shurda4", "detta är shurda4", 1000));
  CU_ASSERT_TRUE(add_item(wh, "shurda67", "detta är shurda67", 1000));

  CU_ASSERT_FALSE(replenish_stock(wh, "shurda", "A25", 0));
  CU_ASSERT_TRUE(replenish_stock(wh, "shurda", "A25", 5));
  CU_ASSERT_FALSE(replenish_stock(wh, "shurda68", "A23", 3));

  CU_ASSERT_TRUE(replenish_stock(wh, "shurda", "A26", 120));
  CU_ASSERT_TRUE(replenish_stock(wh, "shurda", "A26", 120));

  CU_ASSERT_TRUE(replenish_stock(wh, "shurda67", "B01", 8));
  CU_ASSERT_TRUE(replenish_stock(wh, "shurda67", "B02", 100));
  CU_ASSERT_TRUE(replenish_stock(wh, "shurda67", "B04", 84));
  CU_ASSERT_TRUE(replenish_stock(wh, "shurda67", "D50", 85));
  CU_ASSERT_TRUE(replenish_stock(wh, "shurda67", "B05", 84));
  CU_ASSERT_TRUE(replenish_stock(wh, "shurda67", "B05", 2));

  


  destroy_warehouse(wh);
}

void create_and_destroy_cart(void){
  warehouse_t *wh = create_warehouse();
  create_cart(wh);
  destroy_warehouse(wh);
}

void test_add_to_cart(void){
  warehouse_t *wh = create_warehouse();

  CU_ASSERT_TRUE(add_item(wh, "shurda", "detta är shurda", 1000));
  CU_ASSERT_TRUE(add_item(wh, "shurda2", "detta är shurda2", 1000));
  CU_ASSERT_TRUE(add_item(wh, "shurda3", "detta är shurda3", 1000));
  CU_ASSERT_TRUE(add_item(wh, "shurda4", "detta är shurda4", 1000));
  CU_ASSERT_TRUE(add_item(wh, "shurda67", "detta är shurda67", 1000));
  replenish_stock(wh, "shurda", "A25", 10);

  create_cart(wh);
  CU_ASSERT_TRUE(add_to_cart(wh, string_elem("shurda"), int_elem(2), 1));
  CU_ASSERT_FALSE(add_to_cart(wh, string_elem("shurda"), int_elem(9), 1));

  CU_ASSERT_EQUAL(calculate_cost(wh, 1), 2000);

  destroy_warehouse(wh);
}

int main()
{
  // First we try to set up CUnit, and exit if we fail
  if (CU_initialize_registry() != CUE_SUCCESS)
    return CU_get_error();

  // We then create an empty test suite and specify the name and
  // the init and cleanup functions
  CU_pSuite my_test_suite = CU_add_suite("My awesome test suite", init_suite, clean_suite);
  if (my_test_suite == NULL)
  {
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
      (CU_add_test(my_test_suite, "A simple create and check value", test_correct_shelf) == NULL) ||
      (CU_add_test(my_test_suite, "test_add", test_add) == NULL) ||
      (CU_add_test(my_test_suite, "test_remove", test_remove) == NULL) ||
      (CU_add_test(my_test_suite, "test_edit", test_edit) == NULL) ||
      (CU_add_test(my_test_suite, "test_replenish", test_replenish) == NULL) ||
      (CU_add_test(my_test_suite, "create_and_destroy_cart", create_and_destroy_cart) == NULL) ||
      (CU_add_test(my_test_suite, "test_add_to_cart", test_add_to_cart) == NULL) ||
      0)
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