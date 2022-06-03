#include <stdio.h>
#include <stdlib.h>
int main(int argc, char *argv[])
{
  int n;
  int i;
  int *ptr;
  int sum = 0;
  scanf("%d", &n);
  printf("n = %d \n", n);
  if (n == 123456789)
  {
    ptr = malloc(10);
  }
  else
  {
    ptr = malloc(n * (sizeof(int)));
  }
  if (n == 123456789)
  {
    ptr = malloc(10);
  }
  else
  {
    ptr = (int *) malloc(n * (sizeof(int)));
  }
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

