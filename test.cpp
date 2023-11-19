#include <iostream>
#include <string>
#include <vector>
#include <opencv2/opencv.hpp>


void moveForward(int& videoIndex,
                 const std::vector<std::string>& videoPaths,
                 cv::VideoCapture& capture) {
    if (videoIndex < videoPaths.size() - 1) {
        videoIndex++;
        capture.open(videoPaths[videoIndex]);
    }
    else {
        std::cerr << "You are at the end!" << '\n';
    }
}


void moveBackwards(int& videoIndex,
                   const std::vector<std::string>& videoPaths,
                   cv::VideoCapture& capture) {
    if (videoIndex > 0) {
        videoIndex--;
        capture.open(videoPaths[videoIndex]);
    } else {
        std::cerr << "You are at the beginning!" << '\n';
    }
}


int test() {
    std::vector<std::string> videoPaths = {
            "/home/tibor/Desktop/LaneRoadDetection/videos/dashcam1.mp4",
            "/home/tibor/Desktop/LaneRoadDetection/videos/dashcam2.mp4",
            "/home/tibor/Desktop/LaneRoadDetection/videos/dashcam3.mp4",
            "/home/tibor/Desktop/LaneRoadDetection/videos/dashcam4.mp4",
            "/home/tibor/Desktop/LaneRoadDetection/videos/dashcam5.mp4",
            "/home/tibor/Desktop/LaneRoadDetection/videos/dashcam6.mp4",
    };

    int videoIndex = 0;
    cv::VideoCapture capture(videoPaths[videoIndex]);
    cv::Mat img;

    while (true) {
        capture.read(img);
        cv::imshow("Video", img);
        auto key = cv::waitKey(30);
        if (key == 27) {
            cv::destroyAllWindows();
            break;
        }
        else if (key == 'b' || key == 'B') {
            moveBackwards(videoIndex, videoPaths, capture);
        }
        else if (key == 'n' || key == 'N') {
            moveForward(videoIndex, videoPaths, capture);
        }
    }

    return 0;
}
