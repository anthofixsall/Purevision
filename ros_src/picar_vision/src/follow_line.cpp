

#include "follow_line.h"

using namespace cv;
using std::cout; using std::cerr; using std::endl;

extern std::string direction_ligne ;
extern std::string type_panneau ;

extern int flag_direction ;
extern int flag_panneau ;
extern int data ;

extern pthread_mutex_t mutex_ligne ;
extern pthread_mutex_t mutex_panneau ;


void *PrintHello(void *threadid){
   long tid;
   double  temp;
   double dtemps;
   tid = (long)threadid;
   struct  timespec ts;
    clock_gettime(CLOCK_REALTIME, &ts);
    dtemps = (double)ts.tv_sec + (double)ts.tv_nsec * 0.000000001;
    printf("Hello World! It's me, thread #%ld!\n", tid);
    while(1){
        dtemps += 2.0;
        temp = Procedurecomptage(dtemps);
        printf("It's me, thread  after 2 s #%ld!\n", tid);
    }
   pthread_exit(NULL);
}

void *detect_ligne(void *threadid){

    Mat frame;
    cout << "Opening camera..." << endl;
    //VideoCapture capture(0);
      VideoCapture capture("udpsrc multicast-group=127.0.0.1 auto-multicast=true port=5000 ! application/x-rtp,media=video,payload=26,clock-rate=90000,encoding-name=JPEG ! rtpjpegdepay ! jpegdec ! videoconvert ! appsink",
            CAP_GSTREAMER); // open the default camera
    //VideoCapture capture("-v udpsrc multicast-group=127.0.0.1 auto-multicast=true port=5000 ! application/x-rtp, media=video, clock-rate=90000, payload=96 ! rtpjpegdepay ! jpegdec ! videoconvert ! autovideosink ! appsink", CAP_GSTREAMER); // open the first camera>>>>
    //VideoCapture cap("udpsrc uri=udp://127.0.1.1:5000 auto-multicast=true ! application/x-rtp, media=video, encoding-name=H264 ! rtpjitterbuffer latency=300 ! rtph264depay ! decodebin ! videoconvert ! video/x-raw, format=BGR ! appsink", cv::CAP_GSTREAMER);
     //VideoCapture capture("udpsrc port=5000 ! application/x-rtp,media=video,payload=26,clock-rate=90000,encoding-name=JPEG ! rtpjpegdepay ! jpegdec ! videoconvert ! appsink",CAP_GSTREAMER);
    if (!capture.isOpened())
    {
        cerr << "ERROR: Can't initialize camera capture" << endl;
        pthread_exit(NULL);
    }
    /*
    capture.set(CAP_PROP_FPS,30);
    capture.set(CAP_PROP_FRAME_WIDTH, 640);
    capture.set(CAP_PROP_FRAME_HEIGHT, 480);*/

    /*
    cout << "Frame width: " << capture.get(CAP_PROP_FRAME_WIDTH) << endl;
    cout << "     height: " << capture.get(CAP_PROP_FRAME_HEIGHT) << endl;
    cout << "Capturing FPS: " << capture.get(CAP_PROP_FPS) << endl;

    cout << endl << "Press 'ESC' to quit, 'space' to toggle frame processing" << endl;
    cout << endl << "Start grabbing..." << endl;
    */

    size_t nFrames = 0;
    bool enableProcessing = false;
    int64 t0 = cv::getTickCount();
    int64 processingTime = 0;
    for (;;)
    {
        capture >> frame; // read the next frame from camera
        if (frame.empty())
        {
            cerr << "ERROR: Can't grab camera frame." << endl;
            break;
        }
        nFrames++;
        if (nFrames % 10 == 0)
        {
            const int N = 10;
            int64 t1 = cv::getTickCount();
           // cout << "Frames captured: " << cv::format("%5lld", (long long int)nFrames)
            //     << "    Average FPS: " << cv::format("%9.1f", (double)getTickFrequency() * N / (t1 - t0))
             //    << "    Average time per frame: " << cv::format("%9.2f ms", (double)(t1 - t0) * 1000.0f / (N * getTickFrequency()))
             //    << "    Average processing time: " << cv::format("%9.2f ms", (double)(processingTime) * 1000.0f / (N * getTickFrequency()))
              //   << std::endl;
            t0 = t1;
            processingTime = 0;
        }

        Mat src, dst, color_dst;
        std::vector<cv::Vec4i> lines;
        int64 tp0 = cv::getTickCount();

        Mat img_crop;
        //cv::Canny(f rame, processed, 200, 1000, 5);

        //**************** crop ***************************
        const int cropSize = 256;
        const int offsetW = (frame.cols - cropSize) / 2;
        const int offsetH = (frame.rows - cropSize) / 2;

        const Rect roi(offsetW, offsetH, cropSize, cropSize);
        img_crop = frame(roi).clone();

        //******************* traitement **********************
        Mat canny, gaussian, color_gray;

        cv::cvtColor(img_crop, color_gray, cv::COLOR_BGR2GRAY);
        cv::GaussianBlur(color_gray, gaussian, Size(5, 5), 0);
        cv::Canny(gaussian, canny, 85, 85, 3);
        
        processingTime += cv::getTickCount() - tp0;

        HoughLinesP(canny, lines, 1, CV_PI/180, 10, 5, 10);
        float theta = 0;
        for( size_t i = 0; i < lines.size(); i++ )
        {
            Point p1, p2;
            p1 = Point(lines[i][0], lines[i][1]);
            p2 = Point(lines[i][2], lines[i][3]);

            line(img_crop, p1, p2, Scalar(0,0,255), 2);
            theta += atan2((p2.y - p1.y), (p2.x - p1.x));
            //fprintf(stderr, "theat %f  \n", theta);
        }
        {
            float threshold = 6;
            if(theta > threshold){
                //fprintf(stderr, " left \n");
                pthread_mutex_lock(&mutex_ligne);
                direction_ligne = "left";
                flag_direction = 1;
                pthread_mutex_unlock(&mutex_ligne);
            }else if(theta <threshold){
                //fprintf(stderr, " right \n");
                pthread_mutex_lock(&mutex_ligne);
                direction_ligne = "right";
                flag_direction = 1;
                pthread_mutex_unlock(&mutex_ligne);
            }else if( abs(theta) < threshold){
                //fprintf(stderr, " straight \n");
                pthread_mutex_lock(&mutex_ligne);
                direction_ligne = "straight";
                flag_direction = 1;
                pthread_mutex_unlock(&mutex_ligne);
            }
        }
        //namedWindow( "Source", 1 );
        //imshow( "Source", frame );
        //imshow("croped", img_crop);
        
        int key = waitKey(1);
        if (key == 27/*ESC*/)
            pthread_exit(NULL);
    }
    //std::cout << "Number of captured frames: " << nFrames << endl;
    pthread_exit(NULL);
    //return nFrames > 0 ? 0 : 1;

}