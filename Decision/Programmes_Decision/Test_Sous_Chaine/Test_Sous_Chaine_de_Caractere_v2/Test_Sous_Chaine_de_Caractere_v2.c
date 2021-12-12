#include <stdio.h>
#include <string.h>
int extract(int from, int to, char *chaine, char *sousChaine)
{
  int i=0, j=0;
  //récupérer la longueur de la chaîne
  int length = strlen(chaine);
  
  if( from > length || from < 0 ){
    printf("L'index 'from' est invalide\n");
    return 1;
  }
  if( to > length ){
    printf("L'index 'to' est invalide\n");
    return 1;
  }  
  for( i = from, j = 0; i <= to; i++, j++){
    sousChaine[j] = chaine[i];
  }  
  return 0;  
}
int main()
{
  char chaine[100];
  char sousChaine[50];
  int from_1 = 1,to_1 = 2;
  int from_2 = 3,to_2 = 4;
  int from_3 = 5,to_3 = 6;
  
  printf("Entrez une chaîne de caractères: ");
  fgets(chaine,100,stdin);
  // printf("Entrez l'index 'from': ");
  // scanf("%d",&from);
  // printf("Entrez l'index 'to': ");
  // scanf("%d",&to);  
  
  printf("La chaîne de caractères est : %s",chaine);
  
  if( extract(from_1, to_1, chaine, sousChaine) == 0 )
      printf("La sous chaîne de caractères est : %s", sousChaine);
    else
        printf("Erreur!\n");
  
  if( extract(from_2, to_2, chaine, sousChaine) == 0 )
      printf("La sous chaîne de caractères est : %s", sousChaine);
    else
        printf("Erreur!\n");
        
   if( extract(from_3, to_3, chaine, sousChaine) == 0 )
      printf("La sous chaîne de caractères est : %s", sousChaine);
    else
        printf("Erreur!\n");
  return 0;
}
