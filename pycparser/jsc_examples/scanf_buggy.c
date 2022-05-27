#include <string.h>
#include <stdio.h>
int main(int argc, char *argv[])
{
  int a;
  int b = 0;
  FILE *fp = fopen(argv[1], "r");
  fscanf(fp, "%d", a);
  printf("%d \n", a);
  fscanf(fp, "%d", b);
  printf("%d \n", b);
  fclose(fp);
}

