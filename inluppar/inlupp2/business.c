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


struct shelf {
    char* place;
    int stock; 
};


struct merch {
    char* name;
    char* desc;
    int price;
    ioopm_list_t *locations;
};
struct cart {
    int id;
    ioopm_hash_table_t *items;
};
//A cart is a merch-> quantity hash table. In the linked list, each element is a cart which has its id and then the cart.

struct warehouse {
    ioopm_hash_table_t *ht_merch;
    ioopm_hash_table_t *ht_identifier;
    ioopm_hash_table_t *ht_cart;
    ioopm_list_t *carts;
    int carts_amount;
};

static bool eq_function(elem_t a, elem_t b)
{
  return strcmp(a.s, b.s) == 0;
}

static size_t hash_function(elem_t key)
{
  const char *str = key.s;
  size_t result = 0;
  while (*str != '\0')
  {
    result = result * 31 + ((unsigned char)*str);
    str++;
  }
  return result;
}

static shelf_t *create_shelf(char *storage, int stock){
    shelf_t *new_shelf = calloc(sizeof(shelf_t), 1);
    new_shelf->place = strdup(storage);
    new_shelf->stock = stock;
    return new_shelf;
}

void create_cart(warehouse_t *wh) {
    cart_t *new = calloc(sizeof(cart_t), 1);
    new->items = ioopm_hash_table_create(hash_function, eq_function);
    new->id = wh->carts_amount + 1;
    ioopm_list_append(wh->carts, ptr_elem(new));
    wh->carts_amount++;
    return;
}

//HAS REPSONSIBILITY FOR ALMOST ALL MERCH AND HASHTABLES AND STUFF
warehouse_t *create_warehouse(){
    warehouse_t *new = calloc(sizeof(warehouse_t), 1);
    new->ht_identifier = ioopm_hash_table_create(hash_function, eq_function);
    new->ht_merch = ioopm_hash_table_create(hash_function, eq_function);
    new->ht_cart = ioopm_hash_table_create(hash_function, eq_function);
    new->carts = ioopm_list_create();
    return new;
}

static void free_all_locations(ioopm_list_t *locations){
    ioopm_list_iterator_t *iter = ioopm_list_iterator_create(locations);

    while(!ioopm_list_iterator_at_end(iter)){
        shelf_t *current_shelf = ioopm_list_iterator_current(iter).p;
        free(current_shelf->place);
        free(current_shelf);
        ioopm_list_iterator_advance(iter);
    }   
    ioopm_list_destroy(locations);
    ioopm_list_iterator_destroy(iter);
}

static void free_merch(merch_t *merch_to_remove){
        free_all_locations(merch_to_remove->locations);
        free(merch_to_remove->name);
        free(merch_to_remove->desc);
        free(merch_to_remove);
}

static void free_all_merch(ioopm_hash_table_t *ht){
    ioopm_hash_table_iterator_t *merch_iter = ioopm_hash_table_iterator_create(ht);
    elem_t found_merch;
    while(!ioopm_hash_table_iterator_at_end(merch_iter)){
        found_merch = ioopm_hash_table_iterator_current_value(merch_iter);
        merch_t *current_merch = found_merch.p;
        free_merch(current_merch);
        ioopm_hash_table_iterator_advance(merch_iter);
    }
    ioopm_hash_table_iterator_destroy(merch_iter);
    
    return;
}

static void free_all_carts(ioopm_list_t *carts){
    ioopm_list_iterator_t *iter = ioopm_list_iterator_create(carts);
    while(!ioopm_list_iterator_at_end(iter)){
        cart_t *current_cart = ioopm_list_iterator_current(iter).p;
        ioopm_hash_table_destroy(current_cart->items);
        free(current_cart);
        ioopm_list_iterator_advance(iter);
    }
    ioopm_list_iterator_destroy(iter);
    ioopm_list_destroy(carts);

}

static merch_t *make_item(char *name, char *desc, int price){
    merch_t *new_merch = calloc(1, sizeof(merch_t));
    new_merch->name = strdup(name);
    new_merch->desc = strdup(desc);
    new_merch->price = price;
    new_merch->locations = ioopm_list_create();

    return new_merch;
}



void destroy_warehouse(warehouse_t *wh){
    free_all_merch(wh->ht_merch);    
    ioopm_hash_table_destroy(wh->ht_identifier);
    ioopm_hash_table_destroy(wh->ht_merch);
    free_all_carts(wh->carts);
    ioopm_hash_table_destroy(wh->ht_cart);

    free(wh);
}

bool add_item(warehouse_t *wh, char *name, char *desc, int price) {;
    elem_t result;
    
    if (ioopm_hash_table_lookup(wh->ht_merch, string_elem(name), &result)) {
        return false;
    }
    else {
        merch_t *new_merch = make_item(name, desc, price);
        ioopm_hash_table_insert(wh->ht_merch, string_elem(new_merch->name), ptr_elem(new_merch));
        return true;
    }
}

//UI



//UI
void list_items(warehouse_t *wh) {

    ioopm_hash_table_iterator_t *iter = ioopm_hash_table_iterator_create(wh->ht_merch);
    bool stop = false;
    
    do
    {
    for (int i = 1; i <= 20; i++) {
        if (ioopm_hash_table_iterator_at_end(iter)) {
            printf("Last item reached\n");
            return;
        }
        else {
        printf("%d. %s\n", i, ioopm_hash_table_iterator_current_key(iter).s);
        ioopm_hash_table_iterator_advance(iter);
        }
    }
    char *input = ask_question_string("Type N or n to return to main menu, otherwise enter");
    stop = (input[0] == 'N' || input[0] == 'n');
    free(input);
    
    } while (!stop);
    ioopm_hash_table_iterator_destroy(iter);
    return;
}


bool remove_item(warehouse_t *wh, char *remove) {
    elem_t result;
    if (ioopm_hash_table_lookup(wh->ht_merch, string_elem(remove), &result)) {
        merch_t *merch = result.p; 
        ioopm_list_iterator_t *shelf_iter = ioopm_list_iterator_create(merch->locations);

        while(!ioopm_list_iterator_at_end(shelf_iter)){
            shelf_t *current = ioopm_list_iterator_current(shelf_iter).p;
            elem_t ignore;
            ioopm_hash_table_remove(wh->ht_identifier, string_elem(current->place), &ignore);
            free(current->place);
            free(current);
            ioopm_list_iterator_advance(shelf_iter);
        }
        ioopm_list_iterator_destroy(shelf_iter);
        ioopm_hash_table_remove(wh->ht_merch, string_elem(remove), &result);
        free_merch(merch);
        return true;
    }
    else {
        return false;
    }
}

static void change_location_name(warehouse_t *wh, merch_t *merch) {
    ioopm_list_iterator_t *list_iter = ioopm_list_iterator_create(merch->locations);
    while(!ioopm_list_iterator_at_end(list_iter)){
        shelf_t *current = ioopm_list_iterator_current(list_iter).p;
        ioopm_hash_table_insert(wh->ht_identifier, string_elem(current->place), string_elem(merch->name));
        ioopm_list_iterator_advance(list_iter);
    }
    ioopm_list_iterator_destroy(list_iter);
}

//Ändrad så den inte tar någon input utan det görs genom UI
//Frigör gamla namn och beskrivning, gör kopia av sträng den fått in så warehouse har ansvar att frigöra
//problem med två kopior, det måste fixas men apllar inte nu
bool edit_merch(warehouse_t *wh, char *old_name, char *new_name, char *new_desc, int new_price) {
    elem_t result;
    elem_t ignore;
    if (ioopm_hash_table_lookup(wh->ht_merch, string_elem(old_name), &result)) {
        merch_t *merch = result.p; 
        if (!ioopm_hash_table_lookup(wh->ht_merch, string_elem(new_name), &result) || strcmp(old_name, new_name) == 0) {
            ioopm_hash_table_remove(wh->ht_merch, string_elem(old_name), &ignore);
            char *previous_name = merch->name;
            char *previous_desc = merch->desc;
            merch->name = strdup(new_name);
            merch->desc = strdup(new_desc);
            merch->price = new_price;
            change_location_name(wh, merch);
            ioopm_hash_table_insert(wh->ht_merch, string_elem(merch->name), ptr_elem(merch));
            free(previous_name);
            free(previous_desc);
            return true;
        }
        else {
            return false;
        }
    }
    return false;
}


//Gives ownership of the sorted list to the caller, only responsible for freeing copied
//The caller should not free the shelves since they still belong to the warehouse, only the list
static ioopm_list_t *sort_list(ioopm_list_t *locations){
    ioopm_list_t *copy = ioopm_list_create();

    for(size_t i = 0; i < ioopm_list_size(locations); i ++){
        elem_t element;
        ioopm_list_get(locations, i, &element);
        ioopm_list_append(copy, element);
    }

    ioopm_list_t *sorted_locations = ioopm_list_create();
    size_t first_list_size = ioopm_list_size(copy); 
    for(size_t i = 0; i < first_list_size; i++){
        size_t shelf_to_remove = 0;
        elem_t smallest;
        ioopm_list_get(copy, shelf_to_remove, &smallest);
        shelf_t *smallest_ascii = smallest.p;
        for(size_t j = 1; j < ioopm_list_size(copy); j ++){
            elem_t compare;
            ioopm_list_get(copy, j, &compare);
            shelf_t *compare_ascii = compare.p;

            if(strcmp(compare_ascii->place, smallest_ascii->place) < 0){
                smallest_ascii = compare_ascii;
                shelf_to_remove = j;
            }
        }
        elem_t ignore;
        ioopm_list_append(sorted_locations, ptr_elem(smallest_ascii));
        ioopm_list_remove(copy, shelf_to_remove, &ignore);
    }
    ioopm_list_destroy(copy);
    return sorted_locations;
}




void show_stock(warehouse_t *wh, char* merch_name) {
    elem_t result; 
    if (ioopm_hash_table_lookup(wh->ht_merch, string_elem(merch_name), &result)) {
        merch_t *merch = result.p; 
        ioopm_list_t *sorted_list = sort_list(merch->locations);
        ioopm_list_iterator_t *iter = ioopm_list_iterator_create(sorted_list); 
        while (!ioopm_list_iterator_at_end(iter)) {
            shelf_t *shelf = ioopm_list_iterator_current(iter).p;
            printf("Location: %s, stock: %d\n", shelf->place, shelf->stock);
            ioopm_list_iterator_advance(iter);
        }
        return;
    }
    else {
        printf("Stock doesn't exist");
    }
}

bool replenish_stock(warehouse_t *wh, char *merch_name, char* storage_id, int stock_increase){
    if(stock_increase <= 0) return false;
    
    //Huvud if satsen är om produkten ens finns, om inte så är det över
    //Sedan kollar jag om platsen finns i location_ht, om platsen finns och varan finns kan jag börja jobba
    // (först säkerställa så att de matchar namnet jag fått in och den i locations_ht).
    //Sedan kan jag helt enkelt börja jobba i linkade listan och öka värdet med vad som ska ökas.

    //nästa fall är om det som den sparar i ht_locations inte stämmer med ht_merch
    //Sista fall är om varan finns men varuplatsen finns inte, då måste en ny skapas och den platsen samt
    //stocken appendas i listan. (säkerställ i listan bara att platsen faktiskt inte finns)
    elem_t merch_exists;
    elem_t found_merch_elem;
    if(!ioopm_hash_table_lookup(wh->ht_merch, string_elem(merch_name), &merch_exists))
    {
        return false;
    }  //finns ens vara
    else if(ioopm_hash_table_lookup(wh->ht_identifier, string_elem(storage_id), &found_merch_elem)) { // Vara finns men finns platsen
        char *found_merch = found_merch_elem.s;
        //Detta är vad själva merchen heter
        if(strcmp(found_merch, merch_name) != 0) return false;
        
        elem_t locations_elem;
        if(ioopm_hash_table_lookup(wh->ht_merch, string_elem(found_merch), &locations_elem)){//Den sagda varan som ska sparas på plats, spara dens lista.
            merch_t *locations_merch = locations_elem.p;
            ioopm_list_t *locations_list = locations_merch->locations;

            ioopm_list_iterator_t *list_iter = ioopm_list_iterator_create(locations_list);
            while(!ioopm_list_iterator_at_end(list_iter)){
                elem_t current_iter = ioopm_list_iterator_current(list_iter);
                shelf_t *current_shelf = current_iter.p;
                if(strcmp(current_shelf->place, storage_id) == 0){
                    current_shelf->stock += stock_increase;
                    ioopm_list_iterator_destroy(list_iter);            
                    return true;
                }
            ioopm_list_iterator_advance(list_iter);
        }
        ioopm_list_iterator_destroy(list_iter);
        return false;
    }
    return false;

    }
    //I detta fall finns inte platsen med i lista, varan finns dock, därför måste en ny plats skapas och den sedan appendas i rätt lista
    merch_t *found_merch = merch_exists.p;
    ioopm_list_t *locations = found_merch->locations;
    shelf_t *new_shelf = create_shelf(storage_id, stock_increase);
    ioopm_list_append(locations, ptr_elem(new_shelf));
    ioopm_hash_table_insert(wh->ht_identifier, string_elem(new_shelf->place), string_elem(found_merch->name));
    return true;
}


static bool find_cart(warehouse_t *wh, int cart_id, cart_t **result){
    ioopm_list_t *list = wh->carts;
    ioopm_list_iterator_t *iter = ioopm_list_iterator_create(list);
    while (!ioopm_list_iterator_at_end(iter)) {
        elem_t cart = ioopm_list_iterator_current(iter);
        cart_t *current_cart = cart.p;
        if (current_cart->id == cart_id) {
            *result = current_cart;
            ioopm_list_iterator_destroy(iter);
            return true;
        }
        else{
            ioopm_list_iterator_advance(iter);
        }
    }
    ioopm_list_iterator_destroy(iter);
    return false;
}

bool remove_cart(warehouse_t *wh, int id) {
    ioopm_list_t *list = wh->carts;
    elem_t to_remove;
    int counter = 0;
    ioopm_list_iterator_t *iter = ioopm_list_iterator_create(list);
    while (!ioopm_list_iterator_at_end(iter)) {
        elem_t cart = ioopm_list_iterator_current(iter);
        cart_t *current_cart = cart.p;
        if (current_cart->id == id) {
            ioopm_list_remove(list, counter, &to_remove);
            ioopm_hash_table_destroy(current_cart->items);
            free(current_cart);
            free(iter);
            wh->carts_amount--;
            return true;
        }
        else {
            ioopm_list_iterator_advance(iter);
            counter++;
        }
    }
    free(iter);
    return false;
}

static int total_stock_for_item(warehouse_t *wh, elem_t merch_name){
    int total = 0;
    elem_t result;
    ioopm_hash_table_lookup(wh->ht_merch, merch_name, &result);
    merch_t *found_merch = result.p;
    ioopm_list_iterator_t *iter = ioopm_list_iterator_create(found_merch->locations);
    while(!ioopm_list_iterator_at_end(iter)){
        shelf_t *current_stock = ioopm_list_iterator_current(iter).p;
        total += current_stock->stock;
        ioopm_list_iterator_advance(iter);
    }
    ioopm_list_iterator_destroy(iter);
    return total;
}
    
bool add_to_cart(warehouse_t *wh, elem_t key, elem_t quantity, int id) {
    elem_t ignore;
    cart_t *current_cart;

    if(!ioopm_hash_table_lookup(wh->ht_merch, key, &ignore)) return false;
    if(!find_cart(wh, id, &current_cart)) return false;


    ioopm_list_t *carts = wh->carts;
    int counter = 0;
    ioopm_list_iterator_t *cart_iter = ioopm_list_iterator_create(carts);

    while (!ioopm_list_iterator_at_end(cart_iter)) {
        elem_t cart_pointer = ioopm_list_iterator_current(cart_iter);
        cart_t *cart = cart_pointer.p;
        ioopm_hash_table_t *current_cart = cart->items;
        if (ioopm_hash_table_has_key(current_cart, key)) {
            elem_t amount;
            ioopm_hash_table_lookup(current_cart, key, &amount);
            counter = counter + amount.i;
            ioopm_list_iterator_advance(cart_iter);
        }
        else {
        ioopm_list_iterator_advance(cart_iter);
        }
    }
    ioopm_list_iterator_destroy(cart_iter);

    int total_stock = total_stock_for_item(wh, key);
    int cart_max_amount = total_stock - counter;
    if (counter < total_stock && quantity.i <= cart_max_amount && quantity.i > 0) {
                
        ioopm_hash_table_t *items_in_cart = current_cart->items;
        elem_t amount_of_item;
        if (ioopm_hash_table_lookup(items_in_cart, key, &amount_of_item)) {
            amount_of_item.i += quantity.i;
              //Här bör vi kanske lägga till någon slags reserverad mängd så vi kan hålla koll
            ioopm_hash_table_insert(items_in_cart, key, amount_of_item);
            return true;
        }
        else {
            ioopm_hash_table_insert(items_in_cart, key, quantity);
            return true;
        }
    }
    else {
        printf("Quantity is too high or other carts have already reserved requested items, max allowed is : %d", total_stock);
        return false;
    }
}


int calculate_cost(warehouse_t *wh, int cart_id){
    int cost = 0;
    cart_t *cart;
    if (find_cart(wh, cart_id, &cart)){ 
        ioopm_hash_table_iterator_t *hash_iter = ioopm_hash_table_iterator_create(cart->items);
        while(!ioopm_hash_table_iterator_at_end(hash_iter)){
            char *key = ioopm_hash_table_iterator_current_key(hash_iter).s;
            elem_t found;
            ioopm_hash_table_lookup(wh->ht_merch, string_elem(key), &found);
            merch_t *merch = found.p;
        cost += merch->price * ioopm_hash_table_iterator_current_value(hash_iter).i;
        ioopm_hash_table_iterator_advance(hash_iter);
    }
    ioopm_hash_table_iterator_destroy(hash_iter);
    return cost;
    }
    return -1;
}


bool remove_from_cart(warehouse_t *wh, int cart_id, char *merch_name, int amount){
    cart_t *cart;
    elem_t found;
    if(find_cart(wh, cart_id, &cart)){
        if(ioopm_hash_table_lookup(cart->items, string_elem(merch_name), &found)){
            if(found.i >= amount){
                found.i -= amount;
                //VI bör kanske ge tbx till det reserverade beloppet?
                ioopm_hash_table_insert(cart->items, string_elem(merch_name), int_elem(found.i));
                if(found.i == 0){
                    ioopm_hash_table_remove(cart->items, string_elem(merch_name), &found);
                }
                return true;
            }
            return false;
        }
        return false;
    }
    return false;
}