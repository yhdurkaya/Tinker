//
// Created by atlas on 05.06.2022.
//

#include "Worker1.h"

Worker1::Worker1() : outputImage{cv::Mat(640, 480, CV_8UC3, cv::Scalar(0, 0, 0))}
{

}

cv::Mat Worker1::run()
{
    if(frameNumber %2 == 0){
        std::thread task(&Worker1::processImage, this);

        task.join();
    }

    return outputImage;
}

void Worker1::pushFramestoQueue(cv::Mat image)
{
    if(this->queue.size() < 10){
        this->queue.push(image);
    }
    else{
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