## README IOOPM Inlupp 1

## Compiling and running

To compile the tests, you need to run (due to the fact that linked_list and hash_table has the same test file):

gcc -Wall -Wextra -g hash_table.c linked_list.c hash_table_tests.c -o hash_table_tests -lcunit

Run:

./hash_table_tests

The test program runs tests for the hash table, linked list, and their iterators.

## Freq Count Compiling and running

Freq count can be compiled with:

gcc -Wall -Wextra -g hash_table.c freq_count.c -o freq_count

Run it with:

./freq_count test.txt

The program reads words from the text file and counts how many times each word occurs.

## Design decisions
Sentinel nodes are used as the first node for the buckets.
The hash table does not free the data stored in its keys or values when it is destroyed, only the structs.
Hash table iterators should not be used after the underlying hash table has been modified.
Hash table lookup and remove return both a boolean and a value.
The hash table uses No_Buckets which in this case is 17.
The hash table uses function pointers for hashing and key equality, so different types of keys can be used.
Collisions are handled using linked lists.
The linked list keeps track of both the first and last element to make append and prepend efficient.
Invalid list operations print an error message and return an empty elem_t when necessary.
Iterators are separate structs and do not own the data structure they iterate over.