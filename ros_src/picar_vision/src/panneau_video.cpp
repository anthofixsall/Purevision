
#include "panneau_video.h"

using namespace cv;
using namespace std;

extern std::string direction_ligne ;
extern std::string type_panneau ;

extern int flag_direction ;
extern int flag_panneau ;
extern int data ;

extern pthread_mutex_t mutex_ligne ;
extern pthread_mutex_t mutex_panneau ;


Mat imgOri, imgGray, imgCanny, imgTraite, imgGauss, imgDilat, imgEro, imgCoupe;
vector<Point> InitPoints, docPoints;
//VideoCapture camera(4);
VideoCapture camera("udpsrc multicast-group=127.0.0.1 auto-multicast=true port=5001 ! application/x-rtp,media=video,payload=26,clock-rate=90000,encoding-name=JPEG ! rtpjpegdepay ! jpegdec ! videoconvert ! appsink",
            CAP_GSTREAMER); // open the default camera
//VideoCapture camera("-v udpsrc multicast-group=127.0.0.1 auto-multicast=true port=5001 ! application/x-rtp, media=video, clock-rate=90000, payload=96 ! rtpjpegdepay ! jpegdec ! videoconvert ! autovideosink ! appsink", CAP_GSTREAMER); // open the first camera>>>>
   
//variables pour traitement HSV
Mat imgHSV, masK ;
int hmin = 82, smin = 107, vmin = 0;
int hmax = 144, smax = 179, vmax = 255;

Mat preTraitement(Mat img)
{
    cvtColor(img, imgGray, COLOR_BGR2GRAY);
	GaussianBlur(imgGray, imgGauss, Size(3,3),3,0);
	Canny(imgGauss, imgCanny, 25,75);
	
	Mat kernel = getStructuringElement(MORPH_RECT, Size(3,3));
	dilate(imgCanny, imgDilat, kernel);
    //erode(imgDilat, imgEro, kernel);
    return imgDilat;
}

vector<Point> getContours(Mat imgDilat) 
{
	// Liste des points  avec le type de donnee vector<vector<Points
	/*{{Point(20,30), Point(50,60)}, 
	{}, 
	{}}*/
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy; // vector de 4 integ ( (4*valeurs)
	
	//											methode      type de aproximation
	findContours(imgDilat, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
	// 			src , contours, tous = -1 , color, thicknes
	//drawContours(img,contours,-1, Scalar(0,0,0), 2); 
    vector<vector<Point>> conPoly(contours.size());  //Vecteur des contours
	vector<Rect> boundRect(contours.size());        // Vecteur pour boites des contours (Rect = Rectangles)
    // Vector de donnees pour le plus grand des points du contour
    vector<Point> GrandP;

    int maxArea = 0;
	// Filtre des contours par aire
	for (int i = 0; i< contours.size(); i++)
	{
		int area = contourArea(contours[i]);
		//cout << area << endl;
		{
			// arcLength nos da la longueur de los contornos
			//true= para indicar que los contornos son cerrados
			float peri = arcLength(contours[i], true);
			// pour trouver le nombre des cotes (coins =< 4=carre)
			// conpoly = vector pour la comparaison
			//    //true= para indicar cerrado////possible d'utiliser avec entier   	
			approxPolyDP(contours[i],conPoly[i], 0.02*peri, true);   
            
            // Analyse des points pour verification (carre = 4 || octogone = 8)
            // Loop pour enregistrer les points de l'image
			boundRect[i] = boundingRect(conPoly[i]);
            if (area > maxArea && conPoly[i].size() == 8)
            {   
				//drawContours(imgOri,conPoly,i, Scalar(255,0,255), 4);
                GrandP = {conPoly[i][0],conPoly[i][1],conPoly[i][2],conPoly[i][3],conPoly[i][4],conPoly[i][5], conPoly[i][6], conPoly[i][7]};
                maxArea = area;
                for (int j = 0; j < 8 ; j++ )
                {
                    //cout << "L'element '[" << j << "] contient les points" << conPoly[i][j] << endl;
                }
				//Countour du element trouve
				//drawContours(imgOri,conPoly,i, Scalar(255,0,255), 4);
				//rectangle(imgTraite,boundRect[i].tl(),boundRect[i].br(), Scalar(255,0,255), 2);
				
				Rect mesROI(boundRect[i].x,boundRect[i].y,boundRect[i].width,boundRect[i].height);
                imgCoupe = imgOri(mesROI);
				//imshow("Visualisation Image Coupe avant traitement", imgCoupe);
				// identification avec texte
				//putText(imgTraite, "Octogone", {boundRect[i].x, boundRect[i].y}, FONT_ITALIC, 0.5, Scalar(0,255,0), 1);
				
				pthread_mutex_lock(&mutex_panneau);
				type_panneau = "trouve";
				flag_panneau = 1;
				pthread_mutex_unlock(&mutex_panneau);
				//fprintf(stderr, "panneau \n");

            }
				
	   	}
	}
	return GrandP;
} 


void ModCouleurHSV(int, void*)
{
	cvtColor(imgOri, imgHSV, COLOR_BGR2HSV);
	
	//			huge saturatio value
	Scalar lower(hmin, smin, vmin);
	Scalar upper(hmax, smax, vmax);
	
	//     limit (threshold), img dst
	inRange (imgHSV, lower, upper, masK);
	//cout << hmin << ','<< smin << ','<< vmin << ','<< hmax << ','<< smax << ','<< vmax << ','<<endl;
	// Contours (trouver le plus grand aire)
	InitPoints = getContours(masK);
	//imshow("Image en HSV", imgHSV);
    //imshow("Image Filtré", masK);
}



void *detect_panneau(void *threadid){

	/*
    namedWindow("Trakbar Window", (450, 200));
	//HSV ==> Ne fonctione pas avec la fonction findcontours ==> probleme format image non compatible
    createTrackbar("Hue min","Trakbar Window", &hmin, 179);
	createTrackbar("Hue max","Trakbar Window", &hmax, 179);
	
	createTrackbar("Saturation min","Trakbar Window", &smin, 255);
	createTrackbar("Saturation max","Trakbar Window", &smax, 255);
	
	createTrackbar("Value min","Trakbar Window", &vmin, 255);
	createTrackbar("Value min","Trakbar Window", &vmax, 255);
	*/

    while(camera.isOpened())
    {
        camera.read(imgOri);	

        imgTraite = imgOri;

        ModCouleurHSV(0,0);
        //imshow("Visualisation Image Originale", imgOri);
	    if(waitKey(1) == 'q')
        {
            break;
        }
        
    }
    pthread_exit(NULL);
}