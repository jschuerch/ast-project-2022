// code adapted from https://www.programiz.com/c-programming/c-dynamic-memory-allocation

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  int n, i, *ptr, sum = 0;

  if (argc > 1) {
    n = atoi(argv[1]);
    printf("n = %d \n", n);
  } else {
    n = 10;
  }

  ptr = (int*) malloc(n * sizeof(int));
 
  // if memory cannot be allocated
  if(ptr == NULL) {
    printf("Error! memory not allocated.");
    exit(0);
  }

  int *cur = ptr;
  for(i = 0; i < n; ++i) {
    cur += 1;
    *cur = 10;
    sum += *(cur);
  }

  printf("Sum = %d \n", sum);
  
  // deallocating the memory
  free(ptr);

  return 0;
}