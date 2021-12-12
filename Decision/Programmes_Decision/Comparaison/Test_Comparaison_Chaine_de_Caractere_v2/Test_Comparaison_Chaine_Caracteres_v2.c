#include <stdio.h>
#include <string.h>
int main ()
{
  char *str1 = "DROIT";
  char *str2 = "DROIT";
  int ret;

  ret = strncmp(str1, str2,6);

  if(str1 == str2)
  {
    printf("Les chaines ne sont %s et %s sont identiques",str1,str2);
  }
  else
  {
    printf("Les chaines ne sont %s et %s pas identiques",str1,str2);
  }

  return(0);
}
