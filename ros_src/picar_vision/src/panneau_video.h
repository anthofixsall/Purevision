#ifndef HEADER_PANNEAU_VIDEO
#define HEADER_PANNEAU_VIDEO

#include <stdio.h>
#include <stdlib.h>


#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>  // cv::Canny()
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <vector>
#include <string>
#include <iostream>
#include "data_ros.h"

using namespace cv;
using namespace std;

void *detect_panneau(void *threadid);
   

#endif