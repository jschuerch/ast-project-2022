
#include <string.h>
#include <stdio.h>

int main(int argc, char* argv[]) {
    int a,b = 0;
            
    FILE *fp = fopen(argv[1], "r");
    fscanf(fp, "%d", &a);
    printf("%d \n", a);
    fscanf(fp, "%d", &b); // leads to error if & is missing and we are reading a number

    printf("%d \n", b);
    fclose(fp);
}