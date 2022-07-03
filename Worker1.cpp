//
// Created by atlas on 05.06.2022.
//

#include "Worker1.h"

Worker1::Worker1(cv::Mat& image, std::mutex& mainMutex) : outputImage{cv::Mat(640, 480, CV_8UC3, cv::Scalar(0, 0, 0))}
{
    previousImage = cv::Mat::zeros(cv::Size(480, 640), CV_8UC3);

    future_ = std::async(std::launch::async, [this, &image, &mainMutex]{
        while(true)
        {
            if(!image.empty())
            {
                cv::Mat grayImage, grayPreviousImage;
                cv::cvtColor(image, grayImage, cv::COLOR_RGB2GRAY);
                cv::cvtColor(previousImage, grayPreviousImage, cv::COLOR_RGB2GRAY);
                cv::absdiff(grayImage, grayPreviousImage, diffImage);

                if(cv::countNonZero(diffImage) != 0)
                {
                    pushFramestoQueue(image);
                    this->run(mainMutex);
                }
            }
            previousImage = image;
        }
    });
}

void Worker1::run(std::mutex& isMutex)
{

    if(frameNumber %2 == 0)
    {
        std::thread task(&Worker1::processImage, this);

        task.join();

        isMutex.lock();

        cv::imshow("Worker1", outputImage);
        cv::waitKey(5);
        isMutex.unlock();
    }
}

void Worker1::pushFramestoQueue(cv::Mat image)
{
    if(this->queue.size() < 10)
    {
        this->queue.push(image);
    }
    else
    {
        this->queue.pop();
        this->queue.push(image);
    }
    frameNumber++;
}

void Worker1::processImage()
{
    cv::Mat temp = this->queue.front();

    if(frameNumber%20 > 0 && frameNumber%20 <= 5)
    {
        cvtColor(temp, temp, cv::COLOR_RGB2GRAY);
    }
    else if(frameNumber%20 > 5 && frameNumber%20 <= 10)
    {
        cv::rotate(temp, temp, cv::ROTATE_90_CLOCKWISE);
        cvtColor(temp, temp, cv::COLOR_RGB2GRAY);
    }
    else if(frameNumber%20 > 10 && frameNumber%20 <= 15)
    {
        cv::rotate(temp, temp, cv::ROTATE_180);
        cvtColor(temp, temp, cv::COLOR_RGB2GRAY);
    }
    else if(frameNumber%20 > 15 || frameNumber%20 == 0)
    {
        cv::rotate(temp, temp, cv::ROTATE_90_COUNTERCLOCKWISE);
        cvtColor(temp, temp, cv::COLOR_RGB2GRAY);
    }
    else
    {
    }

    outputImage = temp;
}