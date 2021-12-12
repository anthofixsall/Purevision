## Table of Contents


1. [Comparaison] 		(#comparaison)
2. [Decision] 			(#decision)
3. [New Programme Decision] 	(#new-programme-decision)
4. [Test Chaine de caractères] 	(#test-chaine-de-caractere)
5. [Test Sous Chaine]		(#test-sous-chaine)
6. [Interface sous QT]		(#interface-sous-qt)
7. [Interface en Java Swing]	(#interface-en-java-swing)

--------------------------------------------------------------------------------------------
## Comparaison 

*** The Program ***

-   Ce programme permet de comparer deux chaines de caractères afin de savoir si ces deux chaînes sont identiques ou non/
-   Vous pouvez mettre un autre mot dans le champs char*str2 "DROIT" pour comparer deux mots Non-dentiques
 

*** Localisation ***

>> Decision >> Programmes_Decision >> Comparaison >> Test_Comparaison_Chaine_de_Caractere_v2


*** Compilation ***

>> gcc-o Test_Comparaison_Chaine_de_Caractere_v2 Test_Comparaison_Chaine_de_Caractere_v2.c
   
puis : 

./Test_Comparaison_Chaine_de_Caractere_v2.c


-------------------------------------------------------------------------------------------

## Decision

*** The Program ***

-   Les programmes de se répertoire forment les premiers essais du programme de prise de Décision.
    Vous pouvez voir les différentes évolutions de développement du programme grâce aux versions.
-   La tentative d'un programme de décision finale qui n'a pas abouti car des erreurs étaient persistantes.
-   La tentative d'un programme de test débouchant sur les 3 commmandes : AVAN, STOP, RECU.
 

*** Localisation ***

>> Decision >> Programmes_Decision >> Decision


---------------------------------------------------------------------------------------------

## New Programme Decision

*** The Program ***

-   Il s'agit d'une nouvelle version plus simple affichant l'ordre souhaité en fonction des paramètres entrants:
    ici avec un exemple comprenant les 6 case et leur actions associées

    Cas rencontrés : stop / cedez / interdit / feu_vert / feu_orange / feu_rouge
    Actions associées : AVANCER, STOPPER,

*** Localisation ***

>> Decision >> Programmes_Decision >> New_Programme_Decision>> "decision_v2"


*** Compilation ***

>> gcc-o decision_v2 decision_v2.c
   
puis : 

./decision_v2.c


-----------------------------------------------------------------------------------------------


## Test Chaine de caractères

*** The Program ***

-   Les différentes versions nous permette de tester le parsing de chaine de caractères avec différents 
    type de données inscrites dans celle-ci : 

    Version 1 : uniquement des caractères
    Version 2 : Caractères + chiffres (séparation par espaces)
    Version 3 : Caractères + chiffres avec séparation par virgules
    Version 4 : Caractères + chiffres avec séparation par guillemets "" ou crochets []
    Version 5 : Trame type avec séparation par virgule, espace ou crochets

*** Localisation ***

>> Decision >> Programmes_Decision >> Test_Chaine_De_Caracteres >> Test_chaine_de_caractere_vX


*** Compilation *** (remplacer X par la version souhaitée (v2 à v5)

>> gcc-o Test_Chaine_de_Caractere_vX Test_Chaine_de_Caractere_vX.c
   
puis : 

./Test_Chaine_de_Caractere_vX.c

ENTRER VOTRE CHAINE DE CARACTÈRE : [ YYYYYY ]


-------------------------------------------------------------------------------------------------

## Test Sous Chaine de caractères

*** The Program ***

-   Les différentes versions nous permette de tester le parsing de sous-chaine de caractères avec différentes longueurs de chaîne 
    et différentes réponses à l'utilisateur
- Un soucis est detecté sur le dernier caractère lorsque la trame se finit par le chiffre "4" ou "5", cela affiche un "I" ou un "]".

*** Localisation ***

>> Decision >> Programmes_Decision >> Test_Sous_Chaine >> Test_sous_chaine_de_caractere_vX


*** Compilation *** (remplacer X par la version souhaitée (v1 à v5)

>> gcc-o Test_Sous_Chaine_de_Caractere_vX Test_Sous_Chaine_de_Caractere_vX.c
   
puis : 

./Test_Sous_Chaine_de_Caractere_vX.c

ENTRER VOTRE CHAINE DE CARACTÈRE : [ YYYYYYYY ]


-------------------------------------------------------------------------------------------------------------------------------
********************************************************************************************************************************
--------------------------------------------------------------------------------------------------------------------------------

## Interface sous QT

// Avoir QT 5.15.0 sous windows avec compilateur MinGW_64_bits (version 8.1.0)


*** The Program ***

- Ce dossier répertorie mes différents essais afin de produire une interface homme machine (IHM).

*** Localisation ***

>> Decision >> Interface_Utilisateur >> QT >> Fichier originaux >> test_fenetre_ui
>> Decision >> Interface_Utilisateur >> QT >> Fichier originaux >> test_ui (fonctionne, voir résultats dans dossier "Résultats_test_ui")
>> Decision >> Interface_Utilisateur >> QT >> Fichier originaux >> Toplevel : affiche une fenêtre vide

- une seconde idée était de s'inspirer de l'exemple "QMediaPlayer" disponible dans les "Examples" de QT.


*** Execution ***

>> [double-clic] sur le fichier avec l'extension QT Project File >> Compilation et Run (Flèche Verte) dans le logiciel
   

-----------------------------------------------------------------------------------------------------------------------------------------------

## interface sous Eclipse en JAVA SWING


*** Au préalable *** 

// Avoir télécharger le logiciel Eclipse (version 21-06)


*** Execution du programme ***

// Ouvrir le projet du repertoire JAVA SWING avec Eclipse >> Executer le programme (RUN)

Programme "demoswing" : >> Decision >> Interface_Utilisateur >> Java Swing >> demoswing
Programme "testui" : 	>> Decision >> Interface_Utilisateur >> Java Swing >> testui

