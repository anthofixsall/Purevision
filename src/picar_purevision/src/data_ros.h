
#ifndef HEADER_DATA_ROS
#define HEADER_DATA_ROS

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

struct context_data{
  int id;
  int index_thread;
  std::string data;
  char msg[50];
  int flag;
};

/*
 extern std::string direction_ligne ;
 extern std::string type_panneau ;

 extern int flag_direction = 0;
 extern int flag_panneau = 0;
 extern int data ;

 extern pthread_mutex_t mutex_ligne = PTHREAD_MUTEX_INITIALIZER;
 extern pthread_mutex_t mutex_panneau = PTHREAD_MUTEX_INITIALIZER;
 */

//static sem_t sem_panneau;
//static sem_t sem_direction;



#endif