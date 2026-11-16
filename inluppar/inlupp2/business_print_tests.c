#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>

#include "generic_data/common.h"
#include "generic_data/hash_table.h"
#include "generic_data/hash_table_iterator.h"
#include "generic_data/linked_list.h"
#include "generic_data/list_iterator.h"
#include "business.h"
#include "utils.h"


int main(void){
    warehouse_t *wh = create_warehouse();
    add_item(wh, "shurda", "detta är shurda", 9999);
    add_item(wh, "shurda1", "detta är shurda1", 9999);
    add_item(wh, "shurda2", "detta är shurda2", 9999);
    add_item(wh, "shurda3", "detta är shurda3", 9999);
    add_item(wh, "shurda4", "detta är shurda4", 9999);
    add_item(wh, "shurda5", "detta är shurda5", 9999);
    add_item(wh, "shurda6", "detta är shurda6", 9999);

    replenish_stock(wh, "shurda67", "A25", 9);
    replenish_stock(wh, "shurda67", "A26", 10);
    replenish_stock(wh, "shurda67", "A27", 999);
    replenish_stock(wh, "shurda67", "C09", 9);

    list_items(wh);

    show_stock(wh, "shurda67");
}