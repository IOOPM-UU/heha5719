CFLAGS = -g -Wall -Wextra -Wpedantic 
.PHONY = clean

GENERIC = hash_table.o linked_list.o

hash_table.o: generic_data/hash_table.c generic_data/hash_table.h
	gcc $(CFLAGS) -c $< -o $@

linked_list.o: generic_data/linked_list.c generic_data/linked_list.h 
	gcc $(CFLAGS) -c $< -o $@

business.o: business.c business.h
	gcc $(CFLAGS) -c $< -o $@

utils.o: utils.c utils.h
	gcc $(CFLAGS) -c $< -o $@

ui.o: ui.c ui.h
	gcc $(CFLAGS) -c $< -o $@

tests: business.o utils.o business_test.c $(GENERIC)
	gcc $(CFLAGS) $^ -o $@ -lcunit

memtest: tests
	valgrind --leak-check=full ./tests

print: $(GENERIC) business.o utils.o business_print_tests.c
	gcc $(CFLAGS) $^ -o $@

event_loop: $(GENERIC) business.o utils.o ui.o event_loop.c
	gcc $(CFLAGS) $^ -o $@

clean:
	rm -f *.o tests test a.out event_loop