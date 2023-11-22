#pragma once

#include <iostream>
#include <string>

#include <opencv2/opencv.hpp>


class VideoPlayer {
private:
    std::vector<std::string> videoPaths = {
            "/home/tibor/Desktop/LaneRoadDetection/videos/dashcam1.mp4",
            "/home/tibor/Desktop/LaneRoadDetection/videos/dashcam2.mp4",
            "/home/tibor/Desktop/LaneRoadDetection/videos/dashcam3.mp4",
            "/home/tibor/Desktop/LaneRoadDetection/videos/dashcam4.mp4",
            "/home/tibor/Desktop/LaneRoadDetection/videos/dashcam5.mp4",
            "/home/tibor/Desktop/LaneRoadDetection/videos/dashcam6.mp4",
    };

    int videoIndex = 0;
    cv::VideoCapture videoCapture;
    cv::Mat img;

public:
    VideoPlayer();

    void initializeVideoCapture();
    cv::Mat getFrame();
    void nextVideo();
    void previousVideo();
    void switchVideo();
};