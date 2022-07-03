//
// Created by atlas on 05.06.2022.
//

#include "Worker2.h"

Worker2::Worker2(cv::Mat& image, std::mutex& mainMutex) : displayedImage{cv::Mat(640, 480, CV_8UC3, cv::Scalar(0, 0, 0))}
{
    future_ = std::async(std::launch::async, [this, &image, &mainMutex]{
        while(true)
        {
            if(!image.empty())
            {
                this->run(image, mainMutex);
            }
        }
    });
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

void Worker2::run(cv::Mat image, std::mutex& isMutex)
{
    isMutexAvailable = mutex.try_lock();

    if(isMutexAvailable)
    {
        copiedImage = image.clone();
        LogitechFrameProcessingMagic();

        if(isMutex.try_lock())
        {
            cv::imshow( "Worker2", displayedImage);
            cv::waitKey(5);

            isMutex.unlock();
        }
    }
}

double Worker2::calculateMean(cv::Mat &image)
{
    return ((cv::sum(image)[0] / (image.rows * image.cols)) +
            (cv::sum(image)[1] / (image.rows * image.cols)) +
            (cv::sum(image)[2] / (image.rows * image.cols))) / 3;
}