

#ifndef HEADER_FOLLOW_LINE
#define HEADER_FOLLOW_LINE


#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>  // cv::Canny()
#include <iostream>

#include "comptage.h"
#include "data_ros.h"


void *detect_ligne(void *threadid);
   

#endif