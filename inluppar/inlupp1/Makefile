CC = gcc
CFLAGS = -Wall -Wextra -g
CUNIT = -lcunit

PROGRAMS = hash_table_tests freq_count

all: $(PROGRAMS)

hash_table_tests: hash_table.o linked_list.o hash_table_tests.o
	$(CC) $(CFLAGS) $^ -o $@ $(CUNIT)

freq_count: hash_table.o freq_count.o
	$(CC) $(CFLAGS) $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

coverage: CFLAGS += --coverage
coverage: clean hash_table_tests
	./hash_table_tests
	gcov -b hash_table.c linked_list.c

valgrind: hash_table_tests
	valgrind --leak-check=full --track-origins=yes ./hash_table_tests

tests: hash_table_tests
	./hash_table_tests

clean:
	rm -f $(PROGRAMS) *.o *.gcda *.gcno *.gcov

.PHONY: all coverage clean 