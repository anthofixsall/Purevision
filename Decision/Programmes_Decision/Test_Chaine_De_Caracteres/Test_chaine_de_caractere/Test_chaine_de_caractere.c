#include <stdio.h>
#include <string.h>

int main()
{
  char str[] = "Hello Welcome to WayToLearnX best online learning platform";
  int len = strlen(str);
  char d[] = " ";

  char *p = strtok(str, d);

  while(p != NULL)
  {
    printf("'%s'\n", p);
    p = strtok(NULL, d);
  }
  printf("\n");
  return 0;
}
