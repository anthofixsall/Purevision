#include <opencv2/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <vector>
#include <string>
#include <iostream>

using namespace cv;
using namespace std;
//string imgPath = "/home/pi/Desktop/Codes_PureVision_Debug/imgRes/street_signals_stop.jpg";
Mat imgOri, imgGray, imgCanny, imgTraite, imgGauss, imgDilat, imgEro, imgCoupe, imgMasque;
vector<Point> InitPoints, docPoints;
//VideoCapture camera(0);
 VideoCapture camera("udpsrc multicast-group=127.0.0.1 auto-multicast=true port=5001 ! application/x-rtp,media=video,payload=26,clock-rate=90000,encoding-name=JPEG ! rtpjpegdepay ! jpegdec ! videoconvert ! appsink",
                         CAP_GSTREAMER); // open the default camera


//variables pour traitement HSV
Mat imgHSV, masK ;
int hmin = 121, smin = 25, vmin = 0;
int hmax = 179, smax = 255, vmax = 255;

//variables pour Traitement RVB
Mat imgCree;
int iRmin = 108, iRmax = 157, iVmin = 0, iVmax = 108, iBmin = 58, iBmax = 255; 


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


void ModCouleurHSV(int, void*);
void ModCouleurRVB(int, void*);

int main () 
{
	namedWindow("Trakbar Window", (450, 200));
    createTrackbar("Red min","Trakbar Window", &iRmin, 255);
    createTrackbar("Red max","Trakbar Window", &iRmax, 255);
    createTrackbar("Green min","Trakbar Window", &iVmin, 255);
    createTrackbar("Green max","Trakbar Window", &iVmax, 255);
    createTrackbar("Blue min","Trakbar Window", &iBmin, 255);
    createTrackbar("Blue max","Trakbar Window", &iBmax, 255);

	createTrackbar("Hue min","Trakbar Window", &hmin, 255);
    createTrackbar("Hue max","Trakbar Window", &hmax, 255);
    createTrackbar("Saturation min","Trakbar Window", &smin, 255);
    createTrackbar("Saturation max","Trakbar Window", &smax, 255);
    createTrackbar("Value min","Trakbar Window", &vmin, 255);
    createTrackbar("Value max","Trakbar Window", &vmax, 255);


    while(camera.isOpened())
    {
        camera.read(imgOri);	

        imgTraite = imgOri;

        ModCouleurHSV(0,0);
		ModCouleurRVB(0,0);

		if (!masK.empty() && !imgCree.empty())
		{
			bitwise_or(imgCree, masK, imgMasque);
			InitPoints = getContours(imgMasque);
			if (InitPoints.size() != 3 && InitPoints.size() != 8)
			{
				fprintf(stderr, "Aucun Panneaux detecté\n");
			}
			else if (InitPoints.size() == 3)
			{
				fprintf(stderr, "Cedez le Passage detecté\n");
			}
			else if (InitPoints.size() == 8)
			{
				fprintf(stderr, "Stop detecté\n");
			}
		}
        imshow("Visualisation Image Originale", imgOri);

	    if(waitKey(1) == 'q')
        {
            break;
		}
    }
	return 0;
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
    imshow("origine", imgOri);
}
