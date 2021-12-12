// Programme Système de Décision + Envoi Commande en fonction des situations rencontrées.

// ---- Situations rencontrées ----
//
// Trame [XX,droite,Phi]
//
// Argument 1 : [ARG1 / XX / XX] = Type de detection
// -----------------------------
// [01 = Ligne
// [02 = Panneau
// [03 = Pieton ou animaux
// [04 = Feu de signalisation
// 
// Argument 2 : [XX / ARG2 / XX} = Précision
//-------------------------------
// [GAUC = detection à gauche
// [DROI = detection à droite
// [STOP = Panneau Stop
// [CDLP = Panneau Cedez le passage
// [TROT = Piéton Troittoir
// [PASG = Piéton sur Passage Piéton
// [ANIM = Animaux
//
//  Argument 3 : [xx / xx / ARG3] = Angle
// --------------------------------
// [0.1 = 10°
// [0.2 = 20°
// [0.3 = 30°
// [0.4 = 40°
// [0.5 = 50°
// [0.6 = 60°
// [0.7 = 70°
// [0.8 = 80°
// [0.9 = 90°
// [1.0 = 100°
//

// Reception de la trame
// XX
// XX
//
// Decodage de la trame
// 	Décodage Argument 1
// 
//
//
//
//
// Situation 1 : Aucun Obstacle + Voie Dégagée			// Clear_Road
// Situation 2 : Détection d'un Feu Rouge			// Red_Fire
// Situation 3 : Détection Feu Orange				// Orange_Fire
// Situation 4 : Aucun Obstacle + Feu Vert			// Clear_Road + Green_Fire
// Situation 5 : Détection panneau STOP			// STOP_Panel
// Situation 6 : Panneau Cédez le passage			// Give Way
// Situation 7 : Véhicule à l'arrêt devant			// Stationary_Vehicle
// Situation 8 : Voiture devant <30 km/h ou = à 30 km/h 	// Vehicle_in_Front_Less_than_30_km/h
// Situation 9 : Voiture devant entre 31 et 50 km/h	 	// Vehicule_in_Front_between_31_and_50_km/h
// Situation 10 : Voiture devant entre 51 et 100 km/h		// Vehicule_in_Front_between_51_and_100_km/h
// Situation 11 : Voiture devant supérieure à 101 km/h 	// Vehicule_in_Front_More_than_101_km/h
// Situation 12 : Détection d'une voture en contre sens	// Vehicule_Against_the_Current
// Situation 13 : Détection voiture garée sur le côté		// Stationary_Vehicule_on_the_side
// Situation 14 : Détection piéton sur troittoir		// Pedestrian_on_Sidewalk
// Situation 15 : Détection Piéton sur le passage piéton.	// Pedestrian_on_Crossing

// ------ Décision prise ------
//
// Décision 1 : Arrêt			// Stop
// Décision 2 : Ralentir -5%		// Kick_Back
// Décision 3 : Maintenir vitesse	// Maintain_Speed
// Décision 4 : Accélerer la vitesse	// Speed_Up
// Décision 5 : Vitesse = 15 km/h	// Speed_15_km/h
// Décision 6 : Vitesse = 45 km/h	// Speed_45_km/h
// Décision 7 ! Vitesse = 70 km/h	// Speed_70_km/h
// Décision 8 : Vitesse = 100 km/h	// Speed_100_km/h

#include <stdlib.h>
#include <stdio.h>

int Detection;
int Véhicule_Contre_sens;
int Decision;

if (Detection == !0)
{
    switch (Detection)  
    {
        case 1: // Aucun obstacle + Voie dégagée
            
            // code to be executed if 
            printf("Clear_Road \n");
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
            if(Détection_voiture_côté== !0)
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
            
            if(Vehicule_Contre_sens == !0)
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








// transmission pour Howard : "int decision = 1,2,3,4,5,6,7,8";


// Trame de donnée  ex : [1,droite,0.7] --> Signifie (Ligne détectée / commande droite avec un angle de 0.7)
// Donc envoyer à Howard : Maintenir vitesse et tourner à droite de 7°


// Version_2

