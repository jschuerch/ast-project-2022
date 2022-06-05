#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct myStruct
{
    char buff[8];
    int x;
} myStruct;

int main(int arg, char **argv)
{
    struct myStruct *s1 = malloc(sizeof(struct myStruct)); // on heap
    s1->x = 3;
    fgets(s1->buff, sizeof s1->buff, stdin);

    int y = 6 / s1->x;

    printf("\n");
    printf("Value x: %d \n", s1->x);
    printf("Buffer: %s", s1->buff);
    printf("Value y: %d \n", y);
}