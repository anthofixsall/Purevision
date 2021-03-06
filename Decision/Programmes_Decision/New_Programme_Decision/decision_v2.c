#include "stdio.h"
#include "stdlib.h"
#include "string.h"

int pasing_data(char *to_treat, char *to_send);
int send_order(char *data);


// message envoyee depuis le code de vision 
char *panneau[] = {"stop", "cedez", "interdit", 
                  "feu_vert", "feu_orange", "feu_rouge"};

int main (void){
    
    int index;
    char *msg = (char *)malloc(100 * sizeof(char*));
    for(index = 0; index < 6; index++){
        pasing_data(panneau[index], msg);
        fprintf(stderr,"panneau:%s -> decision:%s \n", panneau[index], msg);
    }
    return 0;
}

int pasing_data(char *to_treat, char *to_send){

    char *decision_avance = "AVAN";
    char *decision_stop = "STOP";
    char *decision_rec = "RECU";

    if (strcmp(to_treat, "stop") == 0){ //la fonction renvoie 0 si il trouve la tram suivante dans le char 
        strcpy(to_send, decision_stop); // copie  decision_stop dans to_send
    } else if ( strcmp(to_treat, "cedez") == 0){
        strcpy(to_send, decision_stop); 
    }else if ( strcmp(to_treat, "interdit") == 0){
        strcpy(to_send, decision_stop);
    }else if ( strcmp(to_treat, "feu_vert") == 0){
        strcpy(to_send, decision_avance);
    }else if ( strcmp(to_treat, "feu_orange") == 0){
        strcpy(to_send, decision_stop);
    }else if ( strcmp(to_treat, "feu_rouge") == 0){
        strcpy(to_send, decision_stop);
    }else{ 
        //todo 
    }
}
