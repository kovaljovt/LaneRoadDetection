#include <opencv2/opencv.hpp>


int main() {
    cv::Mat image = cv::imread("/home/tibor/Desktop/LaneRoadDetection/lenna.png");
    cv::imshow("Image", image);
    cv::waitKey();
    return 0;
}