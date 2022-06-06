//
// Created by atlas on 05.06.2022.
//

#include "Worker2.h"

Worker2::Worker2() : displayedImage{cv::Mat(640, 480, CV_8UC3, cv::Scalar(0, 0, 0))}
{

}

void Worker2::LogitechFrameProcessingMagic()
{
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<int> dist6(500,750); // distribution in range [1, 6]

    std::this_thread::sleep_for(std::chrono::milliseconds(dist6(rng)));

    cv::Mat croppedImage = copiedImage(cv::Rect(0, 0, copiedImage.rows/2, copiedImage.cols/2));

    double mean = calculateMean(croppedImage);

    if(mean > 122.0)
    {
        cv::flip(copiedImage, displayedImage, 0);
    }
    else
    {
        displayedImage = copiedImage;
    }

    mutex.unlock();
}

cv::Mat Worker2::run(cv::Mat image)
{
    isMutexAvailable = mutex.try_lock();

    if(isMutexAvailable)
    {
        copiedImage = image.clone();
        std::thread logitechThread(&Worker2::LogitechFrameProcessingMagic, this);
        logitechThread.detach();
    }

}

void Worker2::getResult(cv::Mat& result)
{
    result = displayedImage;
}

double Worker2::calculateMean(cv::Mat &image)
{
    return ((cv::sum(image)[0] / (image.rows * image.cols)) +
            (cv::sum(image)[1] / (image.rows * image.cols)) +
            (cv::sum(image)[2] / (image.rows * image.cols))) / 3;
}