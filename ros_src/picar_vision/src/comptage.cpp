
#include "stdlib.h"
#include "stdio.h"
#include "time.h"

long long Procedurecomptage(double dtempsfin){
    
    long long index_compte = 0;
    struct timespec ts;
    double dtemps;
    do{
        clock_gettime(CLOCK_REALTIME, &ts);
        dtemps = (double)ts.tv_sec + (double)ts.tv_nsec * 0.000000001; 
        index_compte++;

    }while(dtemps < dtempsfin);
    return index_compte;
}