CC ?= gcc
CFLAGS ?= -Wall -O0

EXEC = test

all: $(EXEC)

test: test.o hashset.o
	$(CC) $(CFLAGS) test.o hashset.o -o $@

test.o: test.cc
	$(CC) $(CFLAGS) -c test.cc -o $@

hashset.o: hashset.cc
	$(CC) $(CFLAGS) -c hashset.cc -o $@

clean:
	rm -f *.o test

.PHONY: clean

