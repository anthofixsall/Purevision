
#include "picar_vision.h"
#include "data_ros.h"
#include <opencv2/videoio.hpp>

using namespace cv;
using namespace std;


std::string type_panneau;
std::string direction_ligne;
int flag_panneau;
int flag_direction;
int data = 0;

 pthread_mutex_t mutex_ligne = PTHREAD_MUTEX_INITIALIZER;
 pthread_mutex_t mutex_panneau = PTHREAD_MUTEX_INITIALIZER;


int main(int argc, char *argv[]){

    pthread_t threads[3];
    int rc;
    long t;

    struct  context_data *data_panneau;
    struct  context_data *data_ligne;
    
   //VideoWriter send("appsrc device=/dev/video0 num-buffers=-1 ! video/x-raw, width=300, height=300, framerate=20/1 ! videoconvert ! jpegenc ! rtpjpegpay  ! multiudpsink clients=127.0.0.1:5000,127.0.0.1:5001 auto-multicast=true",0,30,Size(640, 480), true);

    if(pthread_mutex_init(&mutex_panneau, NULL) != 0){
         fprintf(stderr,"\n mutex init panneau failed\n");
    }
    if(pthread_mutex_init(&mutex_ligne, NULL) != 0){
         fprintf(stderr,"\n mutex init ligne failed\n");
    }

        rc = pthread_create(&threads[0], NULL, PrintHello, (void *)1);
        if (rc){
            printf("ERROR; return code from pthread_create() is %d\n", rc);
            exit(-1);
            }
    
        rc = pthread_create(&threads[1], NULL, detect_panneau, (void *)(&data_panneau));
        if (rc){
          printf("ERROR; return code from pthread_create() is %d\n", rc);
          exit(-1);
        }
        //direction_ligne = "test";

        rc = pthread_create(&threads[2], NULL, detect_ligne, (void *)(&data_ligne));
        if (rc){
             printf("ERROR; return code from pthread_create() is %d\n", rc);
            exit(-1);
        }

        while(1){

            if(flag_direction == 1){
                pthread_mutex_lock(&mutex_ligne);
                flag_direction  = 0;
                pthread_mutex_unlock(&mutex_ligne);
                fprintf(stderr, "direction:%s\n", direction_ligne.c_str());
            }else if (flag_panneau == 1){
                pthread_mutex_lock(&mutex_panneau);
                flag_panneau = 0;
                pthread_mutex_unlock(&mutex_panneau);
                fprintf(stderr,"panneau detectee:%s\n", type_panneau.c_str());
            }else{
                //fprintf(stderr, "nothing \n");
            }
        }
    pthread_exit(NULL);  
}