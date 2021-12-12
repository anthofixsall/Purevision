// Decision Globale 

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Variable d'extraction de données de la chaine de caracteres

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


// TEST AVEC UNE CHAINE TYPE UNIQUEMENT EN "INT"  :  1 / 10 / 100 
// Argument 1 : [ARG1 / XX / XX] = Type de detection
// -----------------------------
  char str01[] = " "; // Ligne
 
  
// Argument 2 : [XX / ARG2 / XX} = Précision
//-------------------------------
  char strGAUC[] = "10"; // detection à gauche
  
  
// Argument 3 : [xx / xx / ARG3] = Angle
// --------------------------------
  
 char str10[] = "100";  // 0.1 = 10°
  


// ORDRE 
/*
char *strAVANC = strAVANC;  // Avancer
char *strSTOPP = strSTOPP;  // La voiture doit s'arrêter
char *strRECUL = strRECUL;  // Reculer
*/

// TRAME TYPE
// [XX,CCCC,X.X]

// Creation des sous-chaines de parsing
  char chaine[150];
  char sousChaine1[50];
  char sousChaine2[50];
  char sousChaine3[50];
  
  char strArg1[50] = "";
  char strArg2[50] = "";
  char strArg3[50] = "";
  
// Delimitation des sous-chaines
  int from_1 = 1, to_1 = 2;
  int from_2 = 4, to_2 = 7;
  int from_3 = 9, to_3 = 11;
  
  printf("Entrez une chaîne de caractères: ");
  fgets(chaine, 100, stdin);
  
  // printf("Entrez l'index 'from': ");
  // scanf("%d",&from);
  // printf("Entrez l'index 'to': ");
  // scanf("%d",&to);  
  
  printf("La chaîne de caractères est : %s \n", chaine);

// *********************************************************************************


  // Detection de l'argument 1
  
  if( extract(from_1, to_1, chaine, sousChaine1) == 0 )
      printf("La sous chaîne de caractères est : %s \n", sousChaine1);
      sousChaine1 = strArg1;
      
      if(strArg1 == str01 )
      {
        printf("Caractere '01' detecte \n");
        printf("Ligne \n");
      }
    else
    {
        printf("Erreur!\n");
     }   
// ***********************************************************************************      
    // Detection de l'argument 2
    
  if( extract(from_2, to_2, chaine, sousChaine2) == 0 )
      {
        printf("La sous chaîne de caractères est : %s \n", sousChaine2);
        sousChaine2 = strArg2;
        
        if(strArg2 == str)
        {
          printf("Caracteres 'GAUCH' detécté \n");
          printf("GAUCHE \n");
        }
      }
   else
    {
        printf("Erreur!\n");
    }   
 // ***********************************************************************************   
    // Detection de l'argument 3
       
   if( extract(from_3, to_3, chaine, sousChaine3) == 0 )
      {
      	printf("La sous chaîne de caractères est : %s \n", sousChaine3);
      	sousChaine3 = *strArg3;
      	
      	if(*strArg3 == 10) //
      	{
      	  printf("Angle 10° detecte \n");
          printf("Tourner de 10° \n");
        }
      }
      
    else
        {
        printf("Erreur!\n");
        }
  return 0;
}
