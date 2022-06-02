int main(int argc, char *argv[])
{
  int a = 0;
  {
    int block_a = a + 9;
  }
  if (a == 0)
  {
    int if_a = 10;
  }
  else
  {
    int else_a = 123;
  }
  for (int i = 0; i < a; i++)
  {
    a += 1;
  }

}

