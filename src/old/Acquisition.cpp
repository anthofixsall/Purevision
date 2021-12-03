#include "opencv2/opencv.hpp"
using namespace cv;
using namespace std;
int main(int, char**)
{
  VideoCapture cap("udpsrc multicast-group=127.0.0.1 auto-multicast=true port=5000 ! application/x-rtp,media=video,payload=26,clock-rate=90000,encoding-name=JPEG,framerate=30/1 ! rtpjpegdepay ! jpegdec ! videoconvert ! appsink",
            CAP_GSTREAMER); // open the default camera
  if(!cap.isOpened()) // check if we succeeded
    return -1;
  Mat frame;
  namedWindow( "Video", WINDOW_AUTOSIZE );
  int flagFirst = 1;
  for(;;)
  {
    cap >> frame; // get a new frame from camera
    if(flagFirst == 1)
    {
      flagFirst = 0;
      cout << "Taille : "<< frame.cols <<"colonnes x "<< frame.rows <<"Lignes"<<endl;
    }

    imshow("Video", frame);
    if(waitKey(30) >= 0) break;
  }
  // the camera will be deinitialized automatically in VideoCapture destructor
  return 0;
}