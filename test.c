#include <stdio.h>
#include <string.h>
char *myfunc(char **argv)
{
  char buffer[100];
  strcpy(buffer, "hello");
  return buffer;
}
int main(int argc, char *argv[])
{
  char *s = myfunc(argv);
  printf("%s\n", s);
}