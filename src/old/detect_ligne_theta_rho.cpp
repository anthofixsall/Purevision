#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>  // cv::Canny()
#include <iostream>

using namespace cv;
using std::cout; using std::cerr; using std::endl;

int main(int, char**)
{
    Mat frame;
    cout << "Opening camera..." << endl;
    VideoCapture capture(0); // open the first camera>>>>

    if (!capture.isOpened())
    {
        cerr << "ERROR: Can't initialize camera capture" << endl;
        return 1;
    }

    capture.set(CAP_PROP_FPS,30);
    capture.set(CAP_PROP_FRAME_WIDTH, 640);
    capture.set(CAP_PROP_FRAME_HEIGHT, 480);

    cout << "Frame width: " << capture.get(CAP_PROP_FRAME_WIDTH) << endl;
    cout << "     height: " << capture.get(CAP_PROP_FRAME_HEIGHT) << endl;
    cout << "Capturing FPS: " << capture.get(CAP_PROP_FPS) << endl;

    cout << endl << "Press 'ESC' to quit, 'space' to toggle frame processing" << endl;
    cout << endl << "Start grabbing..." << endl;

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
            cout << "Frames captured: " << cv::format("%5lld", (long long int)nFrames)
                 << "    Average FPS: " << cv::format("%9.1f", (double)getTickFrequency() * N / (t1 - t0))
                 << "    Average time per frame: " << cv::format("%9.2f ms", (double)(t1 - t0) * 1000.0f / (N * getTickFrequency()))
                 << "    Average processing time: " << cv::format("%9.2f ms", (double)(processingTime) * 1000.0f / (N * getTickFrequency()))
                 << std::endl;
            t0 = t1;
            processingTime = 0;
        }
        if (!enableProcessing)
        {
            imshow("Frame", frame);
        }
        else
        {
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

            cv::cvtColor(frame, color_gray, cv::COLOR_BGR2GRAY);
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

                //line(frame, p1, p2, Scalar(0,0,255), 2);
                //theta += atan2((p2.y - p1.y), (p2.x - p1.x));
                //fprintf(stderr, "theat %f  \n", theta);
                
                float rho = lines[i][0], theta = lines[i][1];
                Point pt1, pt2;
                double a = cos(theta), b = sin(theta);
                double x0 = a*rho, y0 = b*rho;
                pt1.x = cvRound(x0 + 1000*(-b));
                pt1.y = cvRound(y0 + 1000*(a));
                pt2.x = cvRound(x0 - 1000*(-b));
                pt2.y = cvRound(y0 - 1000*(a));
                //line( img_crop, pt1, pt2, Scalar(0,0,255), 3, LINE_AA);
                line(img_crop, pt1, pt2, Scalar(0,0,255), 2);
                printf("rho:%f|theta:%f \n",theta, rho);

            }
            {
                float threshold = 6;
                if(theta > threshold){
                    fprintf(stderr, " left \n");

                }else if(theta <threshold){
                    fprintf(stderr, " right \n");
                }else if( abs(theta) < threshold){
                    fprintf(stderr, " straight \n");
                }

            }
            namedWindow( "Source", 1 );
            imshow( "Source", frame );


            imshow("croped", img_crop);
        }
        int key = waitKey(1);
        if (key == 27/*ESC*/)
            break;
        if (key == 32/*SPACE*/)
        {
            enableProcessing = !enableProcessing;
            cout << "Enable frame processing ('space' key): " << enableProcessing << endl;
        }
    }
    std::cout << "Number of captured frames: " << nFrames << endl;
    return nFrames > 0 ? 0 : 1;
}
