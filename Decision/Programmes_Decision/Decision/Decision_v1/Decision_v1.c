// Programme Système de Décision + Envoi Commande en fonction des situations rencontrées.

// ---- Situations rencontrées ----
//
// Situation 1 : Aucun Obstacle + Voie Dégagée
// Situation 2 : Détection d'un Feu Rouge
// Situation 3 : Détection Feu Orange
// Situation 4 : Aucun Obstacle + Feu Vert
// Situation 5 : Détection panneau STOP
// Situation 6 : Panneau Cédez le passage
// Situation 7 : Véhicule à l'arrêt devant
// Situation 8 : Voiture devant <30 km/h ou = à 30 km/h
// Situation 9 : Voiture devant entre 31 et 50 km/h
// Situation 10 : Voiture devant entre 51 et 100 km/h
// Situation 11 : Voiture devant supérieure à 101 km/h
// Situation 12 : Détection d'une voture en contre sens
// Situation 13 : Détection voiture garée sur le côté
// Situation 14 : Détection piéton sur troittoir
// Situation 15 : Détection Piéton sur le passage piéton.

// ------ Décision prise ------
//
// Décision 1 : Arrêt
// Décision 2 : Ralentir -5%
// Décision 3 : Maintenir vitesse
// Décision 4 : Accélerer la vitesse
// Décision 5 : Vitesse = 15 km/h
// Décision 6 : Vitesse = 45 km/h
// Décision 7 ! Vitesse = 70 km/h
// Décision 8 : Vitesse = 100 km/h

#include <stdlib.h>
#include <stdio.h>

bool Detection;
bool Véhicule_Contre_sens;
int Decision;

if (Detection == TRUE)
{
    switch (Detection)  
    {
        case 1: // Aucun obstacle + Voie dégagée
            
            // code to be executed if 
            printf("Voie dégagée \n");
            Decision = 3;
            printf("Maintenir la vitesse actuelle \n");

        break;

        case 2: // Détection d'un Feu Rouge
            
            // code to be executed if
            printf("Feu Rouge détecté \n");
            Decision = 1;
            printf("Arrêt du véhicule \n");

        break;
        
        case 3: // Détection d'un Feu Orange
        
            // code to be executed if
            printf("Feu Orange détecté \n");
            Decision = 2;
            printf("Ralentir la vitesse de 5% \n";)

        break;

        case 4: // Voie dégagée + Feu Vert
            
            // code to be executed if
            printf("Feu Vert détecté \n");
            Decision = 3;
            printf("Maintenir la vitesse \n");


        break;

        case 5: // Panneau STOP
        
            // code to be executed if
           printf("Panneau STOP détecté \n");
           Decision = 1;
           printf(" Arrêt du véhicule \n");

        break;

        case 6: // Panneau Cédez le passage
        
            // code to be executed if
            printf("Panneau Cédez le passage détecté \n");

            Decision = 2;
            if(Détection_voiture_côté== TRUE)
            {
                Decision = 1;
                printf("Detection Voiture, Arrêt du véhicule \n");
            }
            else
            {
                Decision = 5;
                printf("Descendre la Vitesse à 15 km/h \n");
            }
        break;

        case 7: // Voiture à l'arrêt devant
        
            // code to be executed if
            printf("Voiture arrêtée détectée \n");
            Decision = 1;
            printf("Arrêt du véhicule \n");

        break;

        case 8: // Véhicule devant <30 km/h ou = 30 km/h
        
            // code to be executed if
            printf("Véhicule inférieur à 30 km/h \n");
            Decision = 5;
            printf("Vitesse 15 km/h \n");

        break;

        case 9: // Voiture devant entre 31 et 50 km/h
        
            // code to be executed if
            printf("Véhicule > 30 km/h \n");
            Decision = 6;
            printf("Augmenter la vitesse jusqu'à 45 km/h \n");

        break;

        case 10: // Voiture devant entre 51 et 100 km/h
        
            // code to be executed if
            printf("Véhicule > 50 km/h \n");
            Decision = 7;
            printf("Augmenter la vitesse jusqu'à 70 km/h \n");

        break;

        case 11: // Voiture devant supérieure à 100 km/h
        
            // code to be executed if
            printf("Véhicule > 100 km/h \n");
            Decision = 8;
            printf("Augmenter laa vitesse jusqu'à 110 km/h \n");

        break;

        case 12: // Détection d'une voture en contre sens
        
            // code to be executed if
            printf("Voiture à contre sens détectée \n");
            Decision = 2;
            printf("Ralentir \n");
            
            if(Vehicule_Contre_sens == TRUE)
                Decision = 1;
                printf("Arrêt du véhicule \n");
            )
        break;

        case 13: // Détection voiture garée sur le côté
        
            // code to be executed if
            printf("Voiture garée détectée \n");
            Decision = 3;
            printf("Maintenir vitesse \n");

        break;

         case 14: // Détection piéton sur troittoir
        
            // code to be executed if
            printf("Piéton sur Troittoir détecté \n");
            Decision = 3;
            printf("Maintenir vitesse \n");

        break;


         case 15: // Détection Piéton sur le passage piéton
        
            // code to be executed if
            printf("Piéton sur passage piéton détecté  \n");
           
            Decision = 5;
            printf("Réduire la vitesse à 15 km/h \n");
            
            Decision = 1;
            printf("Arrêt du véhicule \n");

        break;

        default:
            Decision = 1;
    }
}
