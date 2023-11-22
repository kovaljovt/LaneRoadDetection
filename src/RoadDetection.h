#pragma once

#include <iostream>
#include <string>
#include <cmath>

#include <opencv2/opencv.hpp>


class RoadDetection {
public:
    cv::Mat applyGrayscale(cv::Mat& source);
    cv::Mat applyGaussianBlur(cv::Mat& source);
    cv::Mat applyCanny(cv::Mat& source);
    cv::Mat filterColors(cv::Mat& source, bool isDayTime);

    bool isDayTime(cv::Mat& source);

    cv::Mat regionOfInterest(cv::Mat& source);
    cv::Mat drawLanes(cv::Mat& source, std::vector<cv::Vec4i> lines);
    std::vector<cv::Vec4i> houghLines(cv::Mat& canny, cv::Mat& source, bool drawHough);
};