//
// Created by atlas on 05.06.2022.
//

#ifndef WORKER1_H
#define WORKER1_H

#include <iostream>
#include <thread>
#include <queue>
#include <future>
#include <atomic>
#include <mutex>

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

class Worker1
{
public:
    Worker1(cv::Mat& image, std::mutex& mainMutex);
    void run(std::mutex& isMutex);
    void pushFramestoQueue(cv::Mat image);

private:
    std::queue<cv::Mat> queue;
    uint frameNumber = 0;
    cv::Mat outputImage;
    std::atomic_bool isMainMutexAvailable;
    std::future<void> future_;
    cv::Mat previousImage;
    cv::Mat diffImage;
private:
    void processImage();
};


#endif //WORKER1_H
