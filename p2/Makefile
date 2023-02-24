CC = gcc
CFLAGS  = -c -Wall -Wshadow -g
DEP = defenv.o
all: defenv clean


defenv: $(DEP)
	$(CC) -g -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) $<

.PHONY: clean
clean:
	rm -f *.o 