#include <iostream>
#include <fstream>
#include <opencv2/opencv.hpp>
#include <opencv2/dnn.hpp>
#include <opencv2/dnn/all_layers.hpp>

using namespace std;
using namespace cv;
using namespace dnn;


int main(int, char**) {
    std::vector<std::string> class_names;
    ifstream ifs(string("../../../input/object_detection_classes_coco.txt").c_str());
    string line;
    while (getline(ifs, line))
    {
        class_names.push_back(line);
    }  
    
    // load the neural network model
    auto model = readNet("../../../input/frozen_inference_graph.pb", 
                        "../../../input/ssd_mobilenet_v2_coco_2018_03_29.pbtxt.txt", 
                        "TensorFlow");

    // capture the video
    VideoCapture cap("../../../input/video_1.mp4");

    // get the video frames' width and height for proper saving of videos
    // int frame_width = static_cast<int>(cap.get(3));
    //int frame_height = static_cast<int>(cap.get(4));
    // create the `VideoWriter()` object
    //VideoWriter out("../../../outputs/video_result.avi", VideoWriter::fourcc('M', 'J', 'P', 'G'), 30, Size(frame_width, frame_height));

    while (cap.isOpened()) {
        Mat image, img_crop;
        bool isSuccess = cap.read(image);

        if (! isSuccess) break;
        
        const int cropSize = 256;
        const int offsetW = (image.cols - cropSize) / 8;
        const int offsetH = (image.rows - cropSize) / 8;

        const Rect roi(offsetW, offsetH, cropSize, cropSize);
        img_crop = image(roi).clone();

       //int image_height = image.cols;
       //int image_width = image.rows;
       int image_width = img_crop.rows;
       int image_height = img_crop.cols;


        //create blob from image
        Mat blob = blobFromImage(img_crop, 1.0, Size(300, 300), Scalar(127.5, 127.5, 127.5), 
                                true, false);
        //create blob from image
        model.setInput(blob);
        //forward pass through the model to carry out the detection
        Mat output = model.forward();
        
        Mat detectionMat(output.size[2], output.size[3], CV_32F, output.ptr<float>());
        
        for (int i = 0; i < detectionMat.rows; i++){
            int class_id = detectionMat.at<float>(i, 1);
            float confidence = detectionMat.at<float>(i, 2);

            // Check if the detection is of good quality
            if (confidence > 0.3){
                int box_x = static_cast<int>(detectionMat.at<float>(i, 3) * img_crop.cols);
                int box_y = static_cast<int>(detectionMat.at<float>(i, 4) * img_crop.rows);
                int box_width = static_cast<int>(detectionMat.at<float>(i, 5) * img_crop.cols - box_x);
                int box_height = static_cast<int>(detectionMat.at<float>(i, 6) * img_crop.rows - box_y);
                rectangle(img_crop, Point(box_x, box_y), Point(box_x+box_width, box_y+box_height), Scalar(255,255,255), 2);
                putText(img_crop, class_names[class_id-1].c_str(), Point(box_x, box_y-5), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0,255,255), 1);
            }
        }
        imshow("image", img_crop);
       // out.write(img_crop);
        int k = waitKey(10);
        if (k == 113){
            break;
        }
    }
cap.release();
destroyAllWindows();
}
