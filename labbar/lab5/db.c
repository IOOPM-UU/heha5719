#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include "utils.h"

typedef struct item item_t;

struct item {
    char *namn;
    char *beskrivning;
    int pris;
    char *lagerhylla;
};

void print_item (item_t *itemet) {
    int KR = (itemet->pris)/100;
    int mini = (itemet->pris)%100;
    printf("Name : %s\nBeskrivning : %s\nPris : %d.%d SEK\nLagerhylla : %s\n", itemet->namn, itemet->beskrivning,
           KR, mini, itemet->lagerhylla);
}

item_t make_item (char *namnet, char *beskrivningen, int priset, char* lagerhyllan) {
    item_t nytt_item = {.namn = namnet, .beskrivning = beskrivningen, .pris = priset, .lagerhylla = lagerhyllan};
    return nytt_item;
}

item_t input_item () {
    char *namnet = ask_question_string("Skriv ett namn: ");
    char *beskrivningen = ask_question_string("Skriv en beskrivning: ");
    int talet = ask_question_int("Skriv ett pris: ");
    char *lagerhyllan = ask_question_shelf("Skriv in en hylla: ");
    return make_item(namnet, beskrivningen, talet, lagerhyllan);
}


char *magick (char *array1[], char *array2[], char *array3[], int array_size) {
    char buf[255];
    int index = random() % array_size; 
    strcpy(buf, array1[index]);
    int counter = strlen(array1[index]);
    buf[counter] = '-';
    counter++; 
    int index2 = random() % array_size; 
    strcpy(buf + counter, array2[index2]);
    counter += strlen(array2[index2]);
    buf[counter] = ' ';
    counter++;
    int index3 = random() % array_size; 
    strcpy(buf + counter, array3[index3]);
    counter += strlen(array3[index3]);
    counter++;
    buf[counter] = '\0';
    return strdup(buf);
}

void list_db(item_t *items, int no_items) {
    for (int i = 0; i < no_items; i++) {
        printf("%d : %s\n", i, items[i].namn);
    }
}

void edit_db(item_t *items, int no_items) {
    list_db(items, no_items);
    int numret = ask_question_int("Vilket item ska editeras?");
    if (numret < no_items && numret >= 0) {
    items[numret] = input_item();
    list_db(items, no_items);
    }
    else {
      printf("Måste vara mellan 0-%d\n", no_items);
    }
}

void print_menu() {
    fprintf(stdout, "[L]ägga till en vara\n[T]a bort en vara\n[R]edigera en vara\nÅn[g]ra senaste ändringen\nLista [h]ela varukatalogen\n[A]vsluta\n");
}

bool is_menu(char *str) { 
    if (strcmp(str, "L") == 0 || strcmp(str, "l") == 0 || strcmp(str, "R") == 0 || strcmp(str, "r") == 0 || strcmp(str, "T") == 0 || strcmp(str, "t") == 0) {
      return true;
    }
    else if (strcmp(str, "G") == 0 || strcmp(str, "g") == 0 || strcmp(str, "H") == 0 || strcmp(str, "h") == 0 || strcmp(str, "A") == 0 || strcmp(str, "a") == 0) {
      return true;
    }
    else {
      return false;
    }
}

char ask_question_menu(char *question) {
    while (true) {
        char *string = ask_question(question, is_menu, (convert_func *)strdup).string_value;
        char c = string[0];
        c = toupper(c);
        if (c == 'L' || c == 'T' || c == 'R' || c == 'G' || c == 'H' || c == 'A') {
            return c;
        }
    }
}

void add_item_to_db(item_t *items, int *no_items) {
    item_t nytt_item = input_item();
    items[*no_items] = nytt_item;
    (*no_items)++;

}

void remove_item_from_db(item_t *items, int *no_items) {
    list_db(items, *no_items);
    int numret = ask_question_int("Vilket item ska tas bort?");
    if (numret < *no_items && numret >= 0) {
        while (numret != *no_items - 1) {
            items[numret] = items[numret + 1];
            numret++;
        }
        (*no_items)--;
    }
    else {
        printf("Måste vara mellan 0-%d\n", *no_items - 1);
    }
}

int event_loop(item_t *items, int *no_items, char *question) {
    while (true) {
    char svaret = ask_question_menu(question);
    if (svaret == 'L') {
        add_item_to_db(items, no_items);
    }
    else if (svaret == 'T') {
        remove_item_from_db(items, no_items);
    }
    else if (svaret == 'R') {
        edit_db(items, *no_items);
    }
    else if (svaret == 'H') {
        list_db(items, *no_items);
    }
    else if (svaret == 'G') {
        printf("Not yet implemented!\n");
    }
    else if (svaret == 'A') {
        return 0;
    }
}
}



int main(int argc, char *argv[])
{
  char *array1[] = {"Hejsan", "Tjena", "Yo"}; // TODO: Lägg till!
  char *array2[] = {"Lena", "Olivia", "Bertil"}; // TODO: Lägg till!
  char *array3[] = {"Hjälp", "Spring", "Skynda"}; // TODO: Lägg till!

  if (argc < 2)
  {
    printf("Usage: %s number\n", argv[0]);
  }
  else
  {
    item_t db[16]; // Array med plats för 16 varor
    int db_siz = 0; // Antalet varor i arrayen just nu

    int items = atoi(argv[1]); // Antalet varor som skall skapas

    if (items > 0 && items <= 16)
    {
      for (int i = 0; i < items; ++i)
      {
        // Läs in en vara, lägg till den i arrayen, öka storleksräknaren
        item_t item = input_item();
        db[db_siz] = item;
        ++db_siz;
      }
    }
    else
    {
      puts("Sorry, must have [1-16] items in database.");
      return 1; // Avslutar programmet!
    }

    for (int i = db_siz; i < 16; ++i)
      {
        char *name = magick(array1, array2, array3, 3); // TODO: Lägg till storlek
        char *desc = magick(array1, array2, array3, 3); // TODO: Lägg till storlek
        int price = random() % 200000;
        char shelf[] = { random() % ('Z'-'A') + 'A',
                         random() % 10 + '0',
                         random() % 10 + '0',
                         '\0' };
        item_t item = make_item(name, desc, price, strdup(shelf));

        db[db_siz] = item;
        ++db_siz;
      }
      event_loop(db, &db_siz, "[L]ägga till en vara\n[T]a bort en vara\n[R]edigera en vara\nÅn[g]ra senaste ändringen\nLista [h]ela varukatalogen\n[A]vsluta");
  }
  return 0;
}

/* remove_item_from_db
    remove_item_from_db(db, db_siz);
    db_siz--;
    list_db(db, db_siz);
*/

/* edit_db
   edit_db(db, db_siz);
*/

/* list_db
   list_db(db, db_siz);
*/
/*.  Magick lägg till längst ner
     for (int i = 0; i < db_siz; ++i)
     {
       print_item(&db[i]);
     }
*/ 
/*  input_item
    item_t item = input_item();
    print_item(&item);
*/
/*  make_item
    item_t nya_itemet = make_item("Dator", "Stor", 320, "B21");
    print_item(&nya_itemet);
*/
/*  print_item
    item_t föremål = {.namn = "Henrik", .beskrivning = "Snygg", .pris = 110, .lagerhylla = "A25"};
    print_item(&föremål);
*/