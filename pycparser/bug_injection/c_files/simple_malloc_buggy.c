#include <stdio.h>
#include <stdlib.h>
int main(int argc, char *argv[])
{
  int n;
  int i;
  int *ptr;
  int sum = 0;
  if (argc > 1)
  {
    n = atoi(argv[1]);
    printf("n = %d \n", n);
  }
  else
  {
    n = 10;
  }
  ptr = (int *) malloc(10);
  if (ptr == 0)
  {
    printf("Error! memory not allocated.");
    exit(0);
  }
  int *cur = ptr;
  for (i = 0; i < n; ++i)
  {
    cur += 1;
    *cur = 10;
    sum += *cur;
  }

  printf("Sum = %d \n", sum);
  free(ptr);
  return 0;
}

