#include <iostream>
#include <string>

#include <opencv2/opencv.hpp>


class VideoPlayer {
private:
    std::vector<std::string> videoPaths;
    int videoIndex;
    cv::VideoCapture videoCapture;
    cv::Mat img;

public:
    explicit VideoPlayer(const std::vector<std::string>& paths)
        : videoPaths(paths), videoIndex(0) {
        initializeVideoCapture();
    }

    void initializeVideoCapture();
    void nextVideo();
    void previousVideo();
    void switchVideo();
    void run();
};