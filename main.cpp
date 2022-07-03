#include <iostream>

#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>

#include "Worker1.h"
#include "Worker2.h"

int main() {
    cv::Mat capturedImage, wImage1, wImage2;
    std::mutex imshowMutex;

    cv::VideoCapture capture;

    Worker1 w1(capturedImage, imshowMutex);
    Worker2 w2(capturedImage, imshowMutex);

    capture.open(0, cv::CAP_ANY);

    if (!capture.isOpened()) {
        std::cerr << "ERROR! Unable to open camera\n";
        return -1;
    }

    while(true){
        capture.read(capturedImage);
    }
}
