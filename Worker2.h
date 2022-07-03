//
// Created by atlas on 05.06.2022.
//

#ifndef WORKER2_H
#define WORKER2_H

#include <iostream>
#include <thread>
#include <mutex>
#include <atomic>
#include <ctime>
#include <random>
#include <future>

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>

class Worker2
{
public:
    Worker2(cv::Mat& image, std::mutex& mainMutex);
    void run(cv::Mat image, std::mutex& isMutex);
    void LogitechFrameProcessingMagic();
private:
    std::thread thread;
    cv::Mat copiedImage;
    cv::Mat displayedImage;
    std::mutex mutex;
    std::atomic_bool isMutexAvailable, isMainMutexAvailable;
    std::future<void> future_;
private:
    double calculateMean(cv::Mat& image);
};


#endif //WORKER2_H
