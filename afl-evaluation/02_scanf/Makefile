# Enable debugging and suppress pesky warnings
CFLAGS ?= -g -w

all:	scanf_buggy

clean:
	rm -f scanf_buggy

vulnerable: scanf_buggy.c
	${CC} ${CFLAGS} scanf_buggy.c -o scanf_buggy
