#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
The idea is to overwrite the integer such that the division
will lead to a division by 0.

If the user input is not large enough, then the
segmentation fault will not be triggered.
*/

struct myStruct
{
    char buff[8];
    int x;
} myStruct;

int main(int arg, char **argv)
{
    struct myStruct *s1 = malloc(sizeof(struct myStruct)); // on heap
    s1->x = 3;
    fgets(s1->buff, sizeof s1->buff + 10, stdin);

    int y = 6 / s1->x;

    printf("\n");
    printf("Value x: %d \n", s1->x);
    printf("Buffer: %s", s1->buff);
    printf("Value y: %d \n", y);
}