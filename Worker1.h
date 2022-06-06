//
// Created by atlas on 05.06.2022.
//

#ifndef WORKER1_H
#define WORKER1_H

#include <thread>
#include <queue>

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

class Worker1
{
public:
    Worker1();
    cv::Mat run();
    void pushFramestoQueue(cv::Mat image);

private:
    std::queue<cv::Mat> queue;
    uint frameNumber = 0;
    cv::Mat outputImage;

private:
    void processImage();
};


#endif //WORKER1_H
