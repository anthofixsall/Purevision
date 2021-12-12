

#include "follow_line.h"


using namespace cv;
using namespace std;

using std::cerr;
using std::cout;
using std::endl;

extern std::string direction_ligne;

extern int flag_direction;
extern int data;

extern pthread_mutex_t mutex_ligne;
extern pthread_mutex_t mutex_panneau;


void *detect_ligne(void *threadid)
{

    Mat frame;
    int64 t0 = cv::getTickCount();
    int64 processingTime = 0;
    int iRmin = 0, iRmax = 33, iVmin = 23, iVmax = 57, iBmin = 19, iBmax = 255; //delaration et definition des valeurs de seuils 


    cout << "Opening camera..." << endl; //affichage pur débug 
    //VideoCapture capture(0);
    VideoCapture capture("udpsrc multicast-group=127.0.0.1 auto-multicast=true port=5000 ! application/x-rtp,media=video,payload=26,clock-rate=90000,encoding-name=JPEG ! rtpjpegdepay ! jpegdec ! videoconvert ! appsink",
                         CAP_GSTREAMER); // open the default camera

    if (!capture.isOpened()){ // verfication si le flux vidéo c'est ouvert 
        cerr << "ERROR: Can't initialize camera capture" << endl;
        pthread_exit(NULL);
    }

    //creation d'une fennetre avec des options de seuillages RVB sous la forme de trackbar 
    /*
    namedWindow("Trakbar Window ligne", (450, 200));
    createTrackbar("Red min","Trakbar Window", &iRmin, 255);
    createTrackbar("Red max","Trakbar Window", &iRmax, 255);
    createTrackbar("Green min","Trakbar Window", &iVmin, 255);
    createTrackbar("Green max","Trakbar Window", &iVmax, 255);
    createTrackbar("Blue min","Trakbar Window", &iBmin, 255);
    createTrackbar("Blue max","Trakbar Window", &iBmax, 255);*/

    for (;;) // boucle infinie 
    {
        int index_display = 0;
        capture >> frame; // read the next frame from camera
        if (frame.empty())  //verfication si le flux video n'est pas  vide 
        {
            cerr << "ERROR: Can't grab camera frame." << endl;
            break;
        }

        Mat src, dst, color_dst;

        int64 tp0 = cv::getTickCount();
        int nFrames;

        Mat img_crop;
        //cv::Canny(f rame, processed, 200, 1000, 5);

        //**************** Traitement RVB *****************
        unsigned char Rmin, Rmax, Vmin, Vmax, Bmin, Bmax;
        int x, y;
        Rmin = (unsigned char)iRmin;
        Rmax = (unsigned char)iRmax;
        Vmin = (unsigned char)iVmin;
        Vmax = (unsigned char)iVmax;
        Bmin = (unsigned char)iBmin;
        Bmax = (unsigned char)iBmax;
        //**************** crop ***************************
        /*
        const int cropSize = 256;
        const int offsetW = (frame.cols - cropSize) / 2;
        const int offsetH = (frame.rows - cropSize) / 2;
        const Rect roi(offsetW, offsetH, cropSize, cropSize);
        */
        
        const Rect roi( (frame.rows /4) + 75,  (frame.cols / 2) , (frame.rows / 2)  , frame.cols / 4);
        img_crop = frame(roi).clone();
        //******************* traitement **********************
        Mat canny, gaussian, color_gray, color_rvb;
        Mat masque;

        color_rvb.create(img_crop.rows, img_crop.cols, CV_8U);
        for (y = 0; y < img_crop.rows; y++)
        {
            for (x = 0; x < img_crop.cols; x++)
            {
                if ((img_crop.at<cv::Vec3b>(y, x)[0] >= Bmin) && (img_crop.at<cv::Vec3b>(y, x)[0] <= Bmax) && (img_crop.at<cv::Vec3b>(y, x)[1] >= Vmin) && (img_crop.at<cv::Vec3b>(y, x)[1] <= Vmax) && (img_crop.at<cv::Vec3b>(y, x)[2] >= Rmin) && (img_crop.at<cv::Vec3b>(y, x)[2] <= Rmax))
                {
                    color_rvb.at<uchar>(y, x) = 255;
                }
                else
                {
                    color_rvb.at<uchar>(y, x) = 0;
                }
            }
        }
        //affichage du resultat du masque RVB
        //imshow("Color rvb", color_rvb);

        //conversion de l'image crope (image d'origine sans traitement) en N&B
        cv::cvtColor(img_crop, color_gray, cv::COLOR_BGR2GRAY);
        //Creation  d'un filtre gaussian de voisinage 5X5  avec l'imge en N&B
        cv::GaussianBlur(color_gray, gaussian, Size(5, 5), 0);
        //Creation  d'un filtre canny  de voisinage 5X5  avec l'imge gaussiene
        cv::Canny(gaussian, canny, 85, 85, 3);
       
        //affichage des resultats 
        //imshow("Masque Gaussien + Canny", canny);
        //integration des données trouvé dans le spectre RVB et gaussian dans un masquage
        bitwise_or(color_rvb, gaussian, masque);
        //affichage du masque 
        //imshow("masque ", masque);  //affichage de l'image avec un filtrage RVB  et HSV
        Mat canny_2;
        cv::Canny(masque, canny_2, 85, 85, 3);
        //imshow("canny_2 ", canny_2);
        
        float theta = 0; 
        float rho = 0;
        
        std::vector<cv::Vec4i> linesP;
        /*
        HoughLinesP(canny, linesP, 1, CV_PI / 180, 10, 5, 10); //realisation d'une transformé de Hough

        //HoughLinesP(canny, linesP, 1, CV_PI / 180, 50,0, 0 ); 
        for (size_t i = 0; i < linesP.size(); i++) //balyage des des lignes trouvées 
        {
            Point p1, p2;
            p1 = Point(linesP[i][0], linesP[i][1]);  
            p2 = Point(linesP[i][2], linesP[i][3]);

            line(img_crop, p1, p2, Scalar(0, 0, 255), 2); //affichages des lignes trouvée dans l'image cropé 
            theta += atan2((p2.y - p1.y), (p2.x - p1.x)); //recherche de l'angle theta sur 
            //fprintf(stderr, "theat %f  \n", theta);
           
            //Vec4i l = linesP[i];
            //line( img_crop, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0,0,255), 3, LINE_AA);
        }*/
        
        Mat img_crop_clone = img_crop.clone();
        std::vector<cv::Vec2f> lines; // will hold the results of the detection
        HoughLines(canny, lines, 1, CV_PI/180, 120, 0, 0 ); // runs the actual detection
        // Draw the lines
        for( size_t i = 0; i < lines.size(); i++ )
        {
            rho = lines[i][0], theta = lines[i][1];
            Point pt1, pt2;
            double a = cos(theta), b = sin(theta);
            double x0 = a * rho, y0 = b * rho;
            pt1.x = cvRound(x0 + 1000 *(-b));
            pt1.y = cvRound(y0 + 1000 * (a));
            pt2.x = cvRound(x0 - 1000 * (-b));
            pt2.y = cvRound(y0 - 1000 * (a));
            line( img_crop_clone, pt1, pt2, Scalar(0,0,255), 3, LINE_AA);
            usleep(10000);
            fprintf(stderr, "rho:%f,theta%f  \n",rho, theta);

        }
        processingTime += cv::getTickCount() - tp0; //indice de temps de traitement 
        {
            //float threshold = 6; 
            if ((theta > 0) && (theta < (3.14 / 2)))
            {
                fprintf(stderr, " right \n");
                pthread_mutex_lock(&mutex_ligne);
                direction_ligne = 1;
                flag_direction = 1;
                pthread_mutex_unlock(&mutex_ligne);

            }
            else if ( (theta > (3.14 / 2)) &&(theta < 3.14 ))
            {
                fprintf(stderr, " left \n");
                pthread_mutex_lock(&mutex_ligne);
                direction_ligne = "left";
                flag_direction = 1;
                pthread_mutex_unlock(&mutex_ligne);

            }else{
                direction_ligne = "";
            }
        }

        //namedWindow( "Source", 1 );
        //imshow( "Source", frame );
        //imshow("HoughLinesP", img_crop);
        //imshow("HoughLines", img_crop_clone);

        nFrames++; 
        //option de test pour analyser le fps de traitement 
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

        int key = waitKey(1);
        if (key == 27 /*ESC*/)
            pthread_exit(NULL);
    }
    //std::cout << "Number of captured frames: " << nFrames << endl;
    pthread_exit(NULL);
    //return nFrames > 0 ? 0 : 1;
}