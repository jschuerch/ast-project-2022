# Enable debugging and suppress pesky warnings
CFLAGS ?= -g -w

all:	simple_malloc_buggy

clean:
	rm -f simple_malloc_buggy

vulnerable: simple_malloc_buggy.c
	${CC} ${CFLAGS} simple_malloc_buggy.c -o simple_malloc_buggy
