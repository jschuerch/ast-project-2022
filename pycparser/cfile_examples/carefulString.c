
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// executing this program will not lead in a crash no matter the size of the input, because wi always cap at the max size of 8

void writeToBuffer()
{
    char buff[8];
    fgets(buff, sizeof buff, stdin);
    printf("%s \n", buff);

    return;
}

int main(int arg, char **argv)
{
    printf("Our input: \n");
    writeToBuffer();
}