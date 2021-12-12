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
  char sousChaine1[150];
  char sousChaine2[50];
  char sousChaine3[50];
// [XX,CCCC,X.X]
  int from_1 = 1,to_1 = 2;
  int from_2 = 4,to_2 = 7;
  int from_3 = 9,to_3 = 11;
  
  printf("Entrez une chaîne de caractères: ");
  fgets(chaine,100,stdin);
  // printf("Entrez l'index 'from': ");
  // scanf("%d",&from);
  // printf("Entrez l'index 'to': ");
  // scanf("%d",&to);  
  
  printf("La chaîne de caractères est : %s \n",chaine);
  
  if( extract(from_1, to_1, chaine, sousChaine1) == 0 )
      printf("La sous chaîne de caractères est : %s \n", sousChaine1);
      
      // Detection caractère 01
      if('0' && '1')
      {
      printf("Caractère '01' detécté");
      }
    else
        printf("Erreur!\n");
  
  if( extract(from_2, to_2, chaine, sousChaine2) == 0 )
      printf("La sous chaîne de caractères est : %s \n", sousChaine2);
      if('G' && 'A' && 'U' && 'C')
      {
      printf("Caractères 'GAUCH' detécté");
      }
    else
        printf("Erreur!\n");
        
   if( extract(from_3, to_3, chaine, sousChaine3) == 0 )
      printf("La sous chaîne de caractères est : %s \n", sousChaine3);
    else
        printf("Erreur!\n");
  return 0;
}
