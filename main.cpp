#include <iostream>

#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>

#include "Worker1.h"
#include "Worker2.h"

int main() {
    cv::Mat capturedImage, wImage1, wImage2;

    cv::VideoCapture capture;

    Worker1 w1;
    Worker2 w2;

    cv::namedWindow("Worker1", cv::WINDOW_AUTOSIZE);
    cv::namedWindow("Worker2", cv::WINDOW_AUTOSIZE);

    capture.open(0, cv::CAP_ANY);

    if (!capture.isOpened()) {
        std::cerr << "ERROR! Unable to open camera\n";
        return -1;
    }
    int count = 0;
    while(true){
        capture.read(capturedImage);
        count++;

        w1.pushFramestoQueue(capturedImage);
        wImage1 = w1.run();

        w2.run(capturedImage);
        w2.getResult(wImage2);

        cv::imshow("Worker1", wImage1);
        cv::imshow("Worker2", wImage2);

        char c=(char)cv::waitKey(25);
        if(c==27) //press ESC to shutdown
        {
            break;
        }
    }
}
