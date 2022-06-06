//
// Created by atlas on 05.06.2022.
//

#ifndef WORKER2_H
#define WORKER2_H

#include <thread>
#include <mutex>
#include <atomic>
#include <ctime>
#include <random>

#include <opencv2/core.hpp>

class Worker2
{
public:
    Worker2();
    cv::Mat run(cv::Mat image);
    void LogitechFrameProcessingMagic();
    void getResult(cv::Mat& result);
private:
    std::thread thread;
    cv::Mat copiedImage;
    cv::Mat displayedImage;
    std::mutex mutex;
    std::atomic_bool isMutexAvailable;
private:
    double calculateMean(cv::Mat& image);
};


#endif //WORKER2_H
