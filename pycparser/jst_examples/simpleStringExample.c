#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// executing this program with an input of more than 8 characters will result in a crash

void writeToBuffer(char *pw)
{
    char buff[8];
    strcpy(buff, pw);
    printf("%s \n", buff);

    return;
}

int main(int arg, char **argv)
{
    printf("Our input: \n");
    writeToBuffer(argv[1]);
}