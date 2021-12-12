/* -----------------------------------------------------*/
/* Fichier  : Detection_Stop.cpp                        */
/* Role     : Detection par traitement d'image          */
/* @Auteur  : Nelson Grullon Rosario                    */
/*          : Projet detecttion Panneux Signalisation   */
/* -----------------------------------------------------*/

#include <stdio.h>
#include <iostream>
#include <string>
#include "opencv2/core/core.hpp"
#include <opencv2/imgproc/imgproc.hpp>
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/calib3d/calib3d.hpp"
#include "opencv2/xfeatures2d/nonfree.hpp"
#include "opencv2/xfeatures2d.hpp"


using namespace cv;
using namespace std;
using namespace xfeatures2d;

string imgPath = "/home/ness/Downloads/images_test/stop_3.jpg";
//string stream = "udpsrc auto-multicast=true port=5000 ! application/x-rtp,media=video,payload=26,clock-rate=90000,encoding-name=JPEG,framerate=30/1 ! rtpjpegdepay ! jpegdec ! videoconvert ! appsink";

string pathComp = "/home/ness/Downloads/images_test/Stop_signal_base.jpg";

Mat imgOri, imgHSV, imgMasque, imgObjet, imgComp, imgCree, imgGray, imgCanny, imgTraite, imgGauss, imgDilat, imgEro, imgCoupe, imgReduced, imgLarged, imgFeu;
vector<Point> InitPoints;

vector<vector<Point>> contours;
vector<Vec4i> hierarchy;  

//vector<Point> pointsContour; 		// Vector de donnees pour le plus grand des points du contour

/*int hmin = 80, smin = 175, vmin = 113;
int hmax = 179, smax = 255, vmax = 255;
/*int hmin = 70, smin = 177, vmin = 118;
int hmax = 178, smax = 255, vmax = 138;*/
/*int hmin = 90, smin = 175, vmin = 113;
int hmax = 179, smax = 255, vmax = 255;*/
int hmin = 0, smin = 150, vmin = 163;
int hmax = 179, smax = 252, vmax = 255;
bool detect_etat = false;

VideoCapture camera(2);


int main ()
{   
    camera.set(CAP_PROP_FRAME_WIDTH, 640);
    camera.set(CAP_PROP_FRAME_HEIGHT, 480);

    imgComp = imread(pathComp);
    resize(imgComp,imgComp, Size(), 0.5, 0.5);

    while (camera.isOpened())
    {

        camera.read(imgOri);

        //Creation de masque par filtrage HSV
        cvtColor(imgOri, imgHSV, COLOR_BGR2HSV);

        //			huge saturatio value
        Scalar minTh(hmin, smin, vmin);
        Scalar maxTh(hmax, smax, vmax);
        //     limit (threshold), img dst
        inRange(imgHSV, minTh, maxTh, imgMasque); //application d'un masque et la sortie d'une imaga avec le filtre appliqué

        Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3)); //creation d'une matrice 3x3 de type morpholgie
        imshow("masque HSV", imgMasque);

        //dilate(imgMasque, imgMasque, kernel, Point(),3);
        //erode(imgMasque, imgMasque, kernel, Point(), 2);
        //imshow("masque apres dilate + ero HSV", imgMasque);

        //Creation de masque par filtrage RVB
        int iRmin = 85, iRmax = 255, iVmin = 0, iVmax = 30, iBmin = 5, iBmax = 30; // Rouge
        unsigned char Rmin, Rmax, Vmin, Vmax, Bmin, Bmax;
        int x, y;

        Rmin = (unsigned char)iRmin;
        Rmax = (unsigned char)iRmax;
        Vmin = (unsigned char)iVmin;
        Vmax = (unsigned char)iVmax;
        Bmin = (unsigned char)iBmin;
        Bmax = (unsigned char)iBmax;

        /* --- Creation de l'image Resultat 
    par balayage et comparaison des files et colones de l'image --- */
        imgCree.create(imgOri.rows, imgOri.cols, CV_8U);
        for (y = 0; y < imgOri.rows; y++)
        {
            for (x = 0; x < imgOri.cols; x++)
            {
                if ((imgOri.at<cv::Vec3b>(y, x)[0] >= Bmin) && (imgOri.at<cv::Vec3b>(y, x)[0] <= Bmax) && (imgOri.at<cv::Vec3b>(y, x)[1] >= Vmin) && (imgOri.at<cv::Vec3b>(y, x)[1] <= Vmax) && (imgOri.at<cv::Vec3b>(y, x)[2] >= Rmin) && (imgOri.at<cv::Vec3b>(y, x)[2] <= Rmax))
                {
                    imgCree.at<uchar>(y, x) = 255;
                }
                else
                {
                    imgCree.at<uchar>(y, x) = 0;
                }
            }
        }
  
        imshow("masque RVB", imgCree); //affichage de l'image avec un filtrage RVB
        //dilate(imgCree, imgCree, kernel, Point(),3);
        //erode(imgCree, imgCree, kernel, Point(), 2);
        //imshow("masque apres dilate + ero RVB", imgCree);

        // Creation d'une masque a partir des masques RVB et HSV
        Mat or_result;
        bitwise_or(imgCree, imgMasque, or_result);
        //imshow("masque avant dilate + ero", or_result); //affichage de l'image avec un filtrage RVB  et HSV

        erode(or_result, or_result, kernel, Point(), 1.73);
        dilate(or_result, or_result, kernel, Point(),2.2);
        //imshow("Masque final  erode et dilate HSV + RVB", or_result);

        int maxAire = 0;
        findContours(or_result, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE); // recherche de contours avec la methode  approximation et de chainage simple

        vector<vector<Point>> conPoly(contours.size()); //Vecteur des contours
        vector<Rect> boundRect(contours.size());        // Vecteur pour boites des contours (Rect = Rectangles)

        for (int i = 0; i < contours.size(); i++) //balayage des coutours
        {
            int aire = contourArea(contours[i]);       // recupairation de l'air du contour
            float peri = arcLength(contours[i], true); //recuperation du perimetre
            //fprintf(stderr, "L'aire du contour est : %d \n", aire);

            if (aire > 1500)
            {
                //cout << "Longueur perimetre : " << peri << endl;
                //fprintf(stderr, "L'aire du contour est : %d \n", aire);

                approxPolyDP(contours[i], conPoly[i], 0.0125 * peri, true); //appro de poly à partir d'un coeff

                boundRect[i] = boundingRect(conPoly[i]);      //declaration des boite englobande pour les contours trouvés
                if (aire > maxAire && conPoly[i].size() == 8) // de test de recherche de 8 points
                {
                    detect_etat = false;
                    //pointsContour = {conPoly[i][0],conPoly[i][1],conPoly[i][2],conPoly[i][3],conPoly[i][4],conPoly[i][5], conPoly[i][6], conPoly[i][7]};
                    maxAire = aire; // mise à jour des contours,

                    Ptr<Feature2D> detector = xfeatures2d::SURF::create(); //detecteur des points equivalents
                    vector<KeyPoint> keypoints_objet, keypoints_comp;      //stockage des points d'interets
                    Mat descripteur_Comp, descripteur_Objet;               //stockage des points d'interets
                    FlannBasedMatcher matcher;                             //detection des points d'interets
                    vector<DMatch> matches;                                //detection des points d'interets
                    vector<DMatch> good_matches;                           //detection des points d'interets qui ont le plus d'importance

                    Rect mesROI(boundRect[i].x, boundRect[i].y, boundRect[i].width, boundRect[i].height); //creation d'un rectangle pour le stockage des regions d'interets
                    imgObjet = imgOri(mesROI);                                                            //découpe des regions d'interets
                    imshow("decoupe ", imgObjet);                                                         //affichage des regions d'interets (debug)

                    detector->detect(imgComp, keypoints_comp);                       //premiere phase de detection des points d'interets de l'image de comparaison
                    detector->detect(imgObjet, keypoints_objet);                     //premiere phase de detection des region d'interets de l'image de comparaison
                    detector->compute(imgComp, keypoints_comp, descripteur_Comp);    //deuxieme phase creation d'un descripteur des points d'interets
                    detector->compute(imgObjet, keypoints_objet, descripteur_Objet); //deuxieme phase creation d'un descripteur des regions d'interets
                    //drawKeypoints(imgObjet, keypoints_objet,imgOri, Scalar (255,0,0));
                    //imshow("descripteur_Comp ", descripteur_Comp);

                    matcher.match(descripteur_Comp, descripteur_Objet, matches); //comparaison des points d'interets avec les regions d'interets
                    double max_dist = 0, min_dist = 100;                         // ordre de gradeur de distance en pixels
                    //-- Calcul de distance  min et max entre les keypoints
                    for (int i = 0; i < descripteur_Comp.rows; i++) // balyage des points d'interets trouvés par le match
                    {
                        //fprintf(stderr, "--matches : %f \n", matches[i]);

                        double dist = matches[i].distance; // recuperation des distances entre chaques points par rapport à un point
                        //fprintf(stderr, "--matches dist : %f \n", dist);
                        if (dist < min_dist) //comparaison de distance en pixel entre deux points
                        {
                            min_dist = dist; // mise à jour de distance la plus courte
                        }
                        if (dist > max_dist)
                        {
                            max_dist = dist; //mise à jour de la distance la longue
                        }
                    }
                    for (int i = 0; i < descripteur_Objet.rows; i++) //balaygae de l'image pour déterminer les élements imporants
                    {
                        if (matches[i].distance < (1.35* min_dist)) //un facteur 2 permet un gain de perfomance sur la qualité de la capture des points
                        {
                            good_matches.push_back(matches[i]); //recuperation des bons points trvoués
                            //fprintf(stderr, "--Element Ok : %f \n", good_matches[i].distance);
                        }
                    }
                    //fprintf(stderr, "bon points : %ld \n", good_matches.size()); //affichage des points (debug)
                    int count_matches = 0;
                    int cont_ok = 0;
                    Mat img_matches;
                    // Verification du nombre des points trouvés
                    for (int i = 0; i < good_matches.size(); i++)
                    {
                        count_matches++;
                    }

                    if (count_matches <= 10) //object trouvé
                    {
                        cont_ok = i;
                        detect_etat = true;
    
                        drawMatches(imgComp, keypoints_comp, imgObjet, keypoints_objet,
                        good_matches, img_matches, Scalar::all(-1), Scalar::all(-1), vector<char>(), DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS); //debug
                    }
                    else
                    {
                        detect_etat = false;
                    }

                    if ((detect_etat == true))
                    {
                        fprintf(stderr, "L'aire du contour est : %d \n", aire);
                        fprintf(stderr, "--Signal Trouvé\n");
                        rectangle(imgOri, boundRect[i].tl(), boundRect[i].br(), Scalar(255, 0, 255), 2); //ajout d'un rectangle sur l'object trouvé dans l'image
                        putText(imgOri, "Panneau Stop", {boundRect[i].x, boundRect[i].y}, FONT_ITALIC, 1, Scalar(0, 255, 0), 2);
                        imshow("Detection des Objets par comparaison ", img_matches);
                    }


                }
            }
        }

        imshow("Detection Panneau Stop ", imgOri);

        if (waitKey(1) == 'q')
        {
            break;
        }
    }
}
