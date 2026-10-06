## README IOOPM Inlupp 1

## Compiling and running

To compile the tests, you need to run (due to the fact that linked_list and hash_table has the same test file):

gcc -Wall -Wextra -g hash_table.c linked_list.c hash_table_tests.c -o hash_table_tests -lcunit

Run:

./hash_table_tests 

The test program runs tests for the hash table, linked list, and their iterators.

Or simply run: 

make tests

If you would like to see memory leaks run: 

make valgrind

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

## Test Coverage

Coverage was measured with gcov

Run the coverage reports with:

make coverage

File 'hash_table.c'
Lines executed:99.03% of 103
Branches executed:100.00% of 36

File 'linked_list.c'
Lines executed:82.35% of 119
Branches executed:95.00% of 40


## Initial Profiling Results

# For each input, what are the top 3 functions?
small.txt: 
advance_iterator_state with 88 calls
cmp_freq_words with 60 calls
ioopm_hash_table_iterator_at_end and skip_sentinel_nodes with 56 calls
10k-words.txt: 
string_eq with 115860 calls
string_hash and string_knr_hash with 20000 calls
find_previous_entry, ioopm_hash_table_insert, ioopm_hash_table_lookup and process_word with 10000 calls
16k-words.txt:
string_eq with 2494074 calls 
cmp_freq_words with 35934 calls
string_hash and string_knr_hash with 33984 calls
1k-long-words.txt: 
string_eq with 3564 calls
string_hash and string_knr_hash with 2000 calls
find_previous_entry, ioopm_hash_table_insert, ioopm_hash_table_lookup and process_word with 1000 calls

# For each input, are the top 3 functions in your code (that you have written), or is it in library functions?
small.txt: 
advance_iterator_state, ioopm_hash_table_iterator_at_end and skip_sentinel_nodes were all written. However, cmp_freq_words was an already provided function.
10k-words.txt: 
string_hash, string_knr_hash were both taken from the course. Meanwhile, string_eq, find_previous_entry, ioopm_hash_table_insert, ioopm_hash_table_lookup and process_word were all written.
16k-words.txt:
cmp_freq_words, string_hash and string_knr_hash were all provided but string_eq was written.
1k-long-words.txt: 
Exactly like 10k-words.txt.

# Are the top 3 functions in your code consistent across the inputs? Why? Why not?
For the biggest functions the results seem to be consistent, the result tends to vary depending on the size of the text file, for example small.txt has iterating through the hashtable as the biggest one due to it making up a bigger part of the program compared to the others. However, looking at the text files with a lot of words you notice that string comparisons and hashes as well as looking up and inserting into the hashtable tend to be relatively consistently the most used ones.

# Is there some kind of trend? (Possibly several)
The bigger the text file the more similar the amount of proportional function calls.

More collisions in the hash table seems to occur more the bigger the file, thereby resulting in more comparisons.

The smaller the text file the more the iterator seems to dominate compared to actual hashes and string comparisons (string_eq).

# Do the results correspond with your expectations?
Yes, somewhat I didn't think it was going to vary as much depending on the size as it did. For example I hadn't even though of the fact that collisions would result in more function calls, the larger the file. I also didn't expect the iterator to be the most called function in small.txt.

# Based on these results, do you see a way to make your program go faster?
Yes, for example it would be wise to reduce the number of collisions in the bigger text files. Could be solved by for example expanding the hash table through more buckets. You could also optimise the program for smaller text files, where the iterator wouldn't be used as much.