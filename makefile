CFLAGS = -std=c99 -pedantic -Wall
CC = gcc

all: test_getbytes test_bits2ull test_bits2ll

bandb.o: bandb.c
	$(CC) $(CFLAGS) -c bandb.c

test_getbytes.o: test_getbytes.c
	$(CC) $(CFLAGS) -c test_getbytes.c -o test_getbytes.o

test_getbytes: bandb.o test_getbytes.o
	$(CC) $(CFLAGS) test_getbytes.o bandb.o -o test_getbytes

test_bits2ull.o: test_bits2ull.c
	$(CC) $(CFLAGS) -c test_bits2ull.c -o test_bits2ull.o

test_bits2ull: bandb.o test_bits2ull.o
	$(CC) $(CFLAGS) test_bits2ull.o bandb.o -o test_bits2ull

test_bits2ll.o: test_bits2ll.c
	$(CC) $(CFLAGS) -c test_bits2ll.c -o test_bits2ll.o

test_bits2ll: bandb.o test_bits2ll.o
	$(CC) $(CFLAGS) test_bits2ll.o bandb.o -o test_bits2ll

clean:
	rm *.o test_getbytes test_bits2ull test_bits2ll
