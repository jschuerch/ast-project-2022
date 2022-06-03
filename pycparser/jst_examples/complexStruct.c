#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct node
{
    char buff[8];
    int *p;
};

int main(int arg, char **argv)
{

    struct node *n1 = malloc(sizeof(struct node)); // on heap
    n1->p = malloc(sizeof(int));
    *(n1->p) = 3;
    fgets(n1->buff, sizeof n1->buff + 2, stdin);

    printf("\n");
    printf("Buffer: %s \n", n1->buff);
    printf("Pointer Address: %p \n", (n1->p));
    printf("Pointer Value: %d", *(n1->p));
    printf("\n");
}