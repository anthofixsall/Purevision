
#include "picar_vision.h"
#include "data_ros.h"


std::string direction_ligne = "";
std::string type_panneau = "";

int flag_direction = 0;
int flag_panneau = 0;
 
int data = 0;

 pthread_mutex_t mutex_ligne = PTHREAD_MUTEX_INITIALIZER;
 pthread_mutex_t mutex_panneau = PTHREAD_MUTEX_INITIALIZER;



int main(int argc, char *argv[]){

    pthread_t threads[3];
    int rc;
    long t;

    //cv::VideoWriter writer;
   //writer.open("-v v4l2src device=/dev/video4 num-buffers=-1 ! video/x-raw, width=640, height=480 ! videoconvert ! jpegenc ! rtpjpegpay ! multiudpsink clients=127.0.0.1:5000,127.0.0.1:5001 auto-multicast=true", 0, (double)30, cv::Size(640, 360), true);
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
    
        rc = pthread_create(&threads[1], NULL, detect_panneau, (void *)4);
        if (rc){
          printf("ERROR; return code from pthread_create() is %d\n", rc);
          exit(-1);
        }
        //direction_ligne = "test";

        rc = pthread_create(&threads[2], NULL, detect_ligne, (void *)4);
        if (rc){
             printf("ERROR; return code from pthread_create() is %d\n", rc);
            exit(-1);
        }

        while(1){

            if(flag_direction == 1){
                pthread_mutex_lock(&mutex_ligne);
                flag_direction = 0;
                pthread_mutex_unlock(&mutex_ligne);
                fprintf(stderr, "nouvelle  direction \n");
            }else if (flag_panneau == 1){
                pthread_mutex_lock(&mutex_panneau);
                flag_panneau = 0;
                pthread_mutex_unlock(&mutex_panneau);
                fprintf(stderr,"panneau detectee \n");
            }else{
                //fprintf(stderr, "nothing \n");
            }
        }
    pthread_exit(NULL);  
}