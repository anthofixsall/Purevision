#include <stdio.h>
#include <string.h>

int main()
{
  char str[] = "[01,GAUC,0.7]";
  int len = strlen(str);
  char d[] = " "",""[""]";

  char *p = strtok(str, d);

  while(p != NULL)
  {
    printf("'%s'\n", p);
    p = strtok(NULL, d);
  }
  printf("\n");
  return 0;
}
