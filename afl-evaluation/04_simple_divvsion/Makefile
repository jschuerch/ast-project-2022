# Enable debugging and suppress pesky warnings
CFLAGS ?= -g -w

all:    simple_division

clean:
        rm -f simple_division

vulnerable: simple_division.c
        ${CC} ${CFLAGS} simple_division.c -o simple_division
~                                                                    
