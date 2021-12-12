
#include "panneau_video.h"

using namespace cv;
using namespace std;

extern pthread_mutex_t mutex_panneau ;
extern int data_panneau;
extern int flag_panneau;

Mat imgOri, imgGray, imgCanny, imgTraite, imgGauss, imgDilat, imgEro, imgCoupe, imgMasque;
vector<Point> InitPoints, docPoints;

//variables pour traitement HSV
Mat imgHSV, masK ;

//int hmin = 121, smin = 147, vmin = 0;
//int hmax = 179, smax = 255, vmax = 255;

int hmin = 139, smin = 38, vmin = 136;
int hmax = 238, smax = 202, vmax = 255;


//variables pour Traitement RVB
Mat imgCree;
//int iRmin = 205, iRmax = 255, iVmin = 0, iVmax = 155, iBmin = 0, iBmax = 255; 
int iRmin = 196, iRmax = 255, iVmin = 103, iVmax = 202, iBmin = 111, iBmax = 188; 


VideoCapture camera("udpsrc multicast-group=127.0.0.1 auto-multicast=true port=5001 ! application/x-rtp,media=video,payload=26,clock-rate=90000,encoding-name=JPEG ! rtpjpegdepay ! jpegdec ! videoconvert ! appsink", CAP_GSTREAMER); // open the default camera


vector<Point> getContours(Mat imgDilat);
void ModCouleurHSV(int, void*);
void ModCouleurRVB(int, void*);

void *detect_panneau(void *threadid){



    for(;;);
    {

	namedWindow("Trakbar Window panneau", (450, 200));
			/*
    createTrackbar("Red min","Trakbar Window", &iRmin, 255, NULL);
    createTrackbar("Red max","Trakbar Window", &iRmax, 255, NULL);
    createTrackbar("Green min","Trakbar Window", &iVmin, 255, NULL);
    createTrackbar("Green max","Trakbar Window", &iVmax, 255, NULL);
    createTrackbar("Blue min","Trakbar Window", &iBmin, 255, NULL);
    createTrackbar("Blue max","Trakbar Window", &iBmax, 255, NULL);
	createTrackbar("Hue min","Trakbar Window", &hmin, 255, NULL);
    createTrackbar("Hue max","Trakbar Window", &hmax, 255, NULL);
    createTrackbar("Saturation min","Trakbar Window", &smin, 255, NULL);
    createTrackbar("Saturation max","Trakbar Window", &smax, 255, NULL);
    createTrackbar("Value min","Trakbar Window", &vmin, 255, NULL);
    createTrackbar("Value max","Trakbar Window", &vmax, 255, NULL);*/

        camera.read(imgOri);
		if (!camera.isOpened()){
			cerr << "ERROR: Can't initialize camera capture" << endl;
            pthread_exit(NULL);
		}

		camera >> imgOri;
		imgTraite = imgOri;
		
		imshow("Visualisation Image Originale", imgOri);
        ModCouleurHSV(0,0);
		ModCouleurRVB(0,0);

		if (!masK.empty() && !imgCree.empty())
		{
			bitwise_or(imgCree, masK, imgMasque);
			InitPoints = getContours(imgMasque);
			if (InitPoints.size() != 3 && InitPoints.size() != 8)
			{
				fprintf(stderr, "Aucun Panneaux detecté\n");
				pthread_mutex_lock(&mutex_panneau);
                data_panneau = 0;			
                flag_panneau = 0;
                pthread_mutex_unlock(&mutex_panneau);
			}
			else if (InitPoints.size() == 3)
			{
				fprintf(stderr, "Cedez le Passage detecté\n");
				pthread_mutex_lock(&mutex_panneau);
                data_panneau = 1;
                flag_panneau = 0;
                pthread_mutex_unlock(&mutex_panneau);
			}
			else if (InitPoints.size() == 8)
			{
				fprintf(stderr, "Stop detecté\n");
				pthread_mutex_lock(&mutex_panneau);
                data_panneau = 2;
                flag_panneau = 0;
                pthread_mutex_unlock(&mutex_panneau);
			}
		}
    }
    pthread_exit(NULL);
}


void ModCouleurHSV(int, void*)
{
	cvtColor(imgOri, imgHSV, COLOR_BGR2HSV);
	
	//			huge saturatio value
	Scalar lower(hmin, smin, vmin);
	Scalar upper(hmax, smax, vmax);
	
	//     limit (threshold), img dst
	inRange (imgHSV, lower, upper, masK);

	//imshow("Image en HSV", imgHSV);
    imshow("masque HSV", masK);
}

void ModCouleurRVB(int, void*)
{
	unsigned char Rmin, Rmax, Vmin, Vmax, Bmin, Bmax;
	int x,y;

	Rmin = (unsigned char)iRmin;
    Rmax = (unsigned char)iRmax;
    Vmin = (unsigned char)iVmin;
    Vmax = (unsigned char)iVmax;
    Bmin = (unsigned char)iBmin;
    Bmax = (unsigned char)iBmax;

	/* --- Creation de l'image Resultat --- */
    imgCree.create(imgOri.rows, imgOri.cols, CV_8U );
    for(y = 0; y < imgOri.rows; y++)
    {
        for(x = 0; x < imgOri.cols; x++)
        {
            if((imgOri.at<cv::Vec3b>(y,x)[0] >= Bmin) // 0)       //Bmin)
            && (imgOri.at<cv::Vec3b>(y,x)[0] <= Bmax) //100)      //Bmax)
            && (imgOri.at<cv::Vec3b>(y,x)[1] >= Vmin) //0)      //Vmin)
            && (imgOri.at<cv::Vec3b>(y,x)[1] <= Vmax) //10)      //Vmax)
            && (imgOri.at<cv::Vec3b>(y,x)[2] >= Rmin) //90)      //Rmin)
            && (imgOri.at<cv::Vec3b>(y,x)[2] <= Rmax)) //255))    //Rmax))
            imgCree.at<uchar>(y,x) = 255;
            else
            imgCree.at<uchar>(y,x) = 0;
        }
    }
	imshow("masque RVB", imgCree);
}

vector<Point> getContours(Mat imgDilat) 
{
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy; // vector de 4 integ ( (4*valeurs)
	
	//											methode    //  type de aproximation
	findContours(imgDilat, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
	// 			src , contours, tous = -1 , color, thicknes
	//drawContours(img,contours,-1, Scalar(0,0,0), 2); 
    vector<vector<Point>> conPoly(contours.size());  //Vecteur des contours
	vector<Rect> boundRect(contours.size());        // Vecteur pour boites des contours (Rect = Rectangles)
    // Vector de donnees pour les points du plus grand des contours
    vector<Point> GrandP;

    int maxArea = 0;
	// Filtre des contours par aire
	for (int i = 0; i< contours.size(); i++)
	{
		int area = contourArea(contours[i]);
		//cout << area << endl;
			
					
		if (area > 1500 )
		{
			float peri = arcLength(contours[i], true);	
			approxPolyDP(contours[i],conPoly[i], 0.013*peri, true);   
			
			boundRect[i] = boundingRect(conPoly[i]);
			//Conditions pour Panneaux Stop 
            if (area > maxArea && conPoly[i].size() == 8)
            {   

                GrandP = {conPoly[i][0],conPoly[i][1],conPoly[i][2],conPoly[i][3],conPoly[i][4],conPoly[i][5], conPoly[i][6], conPoly[i][7]};
                maxArea = area;

				rectangle(imgOri,boundRect[i].tl(),boundRect[i].br(), Scalar(255,0,255), 2);
				
				Rect mesROI(boundRect[i].x,boundRect[i].y,boundRect[i].width,boundRect[i].height);
                imgCoupe = imgOri(mesROI);
				imshow("Visualisation Image Coupe avant traitement", imgCoupe);
				// identification avec texte
				putText(imgTraite, "Panneau Stop", {boundRect[i].x, boundRect[i].y}, FONT_ITALIC, 0.5, Scalar(0,255,0), 1);
            }
			//Conditions pour Panneaux Cedez le passage 
	    	if (area > maxArea && conPoly[i].size() == 3)
            {   

				GrandP = {conPoly[i][0],conPoly[i][1],conPoly[i][2]};
                maxArea = area;

				rectangle(imgOri,boundRect[i].tl(),boundRect[i].br(), Scalar(255,0,255), 2);
				
				Rect mesROI(boundRect[i].x,boundRect[i].y,boundRect[i].width,boundRect[i].height);
                imgCoupe = imgOri(mesROI);
				imshow("Visualisation Image Coupe avant traitement", imgCoupe);
				// identification avec texte
				putText(imgTraite, "Panneau Ceder Passage", {boundRect[i].x, boundRect[i].y}, FONT_ITALIC, 0.5, Scalar(0,255,0), 1);
            }
				
	   	}
	}
	return GrandP;
} 