#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
Creates a binary tree with a lot of pointers.

The idea is to overwrite one of the pointers via a
buffer-overflow to cause a segmentation fault.
*/

struct node;

struct node
{
  char buff[50];
  struct node *left;
  struct node *right;
  struct node *p;
};

int main(int arg, char **argv)
{
  int depth = 0;
  int count = 1;
  struct node *c = malloc(sizeof(struct node));
  *c->buff = 'L';
  while (count < 62)
  {
    if ((depth == 5) || (((*c->buff) != 'L') && ((*c->buff) != 'R')))
    {
      --depth;
      c = (*c).p;
    }
    else
    {
      if ((*c->buff) == 'L')
      {
        *c->buff = 'R';
        (*c).left = malloc(sizeof(struct node));
        (*(*c).left).p = c;
        if (count == 27)
        {
          fgets(c->buff, (sizeof(c->buff)) + 100, stdin);
        }
        c = (*c).left;
        *c->buff = 'L';
        ++depth;
        ++count;
      }
      else if ((*c->buff) == 'R')
      {
        *c->buff = 'X';
        (*c).right = malloc(sizeof(struct node));
        (*(*c).right).p = c;
        if (count == 27)
        {
          fgets(c->buff, (sizeof(c->buff)) + 100, stdin);
        }
        c = (*c).right;
        *c->buff = 'L';
        ++depth;
        ++count;
      }
    }
  }

  printf("\n");
  printf("success\n");
  printf("\n");
}
