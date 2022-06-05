# Enable debugging and suppress pesky warnings
CFLAGS ?= -g -w

all:    nodeTree_buggy

clean:
        rm -f nodeTree_buggy

vulnerable: nodeTree_buggy.c
        ${CC} ${CFLAGS} nodeTree_buggy.c -o nodeTree_buggy

