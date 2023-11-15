#include "VideoPlayer.h"


void VideoPlayer::initializeVideoCapture() {
    videoCapture.open(videoPaths[videoIndex]);
}


void VideoPlayer::nextVideo() {
    if (videoIndex == videoPaths.size() - 1) {
        cv::destroyAllWindows();
        return;
    }
    videoIndex++;
    switchVideo();
}


void VideoPlayer::previousVideo() {
    if (videoIndex == 0) {
        cv::destroyAllWindows();
        return;
    }
    videoIndex--;
    switchVideo();
}


void VideoPlayer::switchVideo() {
    videoCapture.release();
    videoCapture.open(videoPaths[videoIndex]);
}


void VideoPlayer::run() {
    while (true) {
        videoCapture.read(img);
        cv::imshow("Video", img);
        auto key = cv::waitKey(30);
        if (key == 27) {
            cv::destroyAllWindows();
            break;
        }
        else if (key == 'n' || key == 'N') {
            nextVideo();
        }
        else if (key == 'b' || key == 'B') {
            previousVideo();
        }
    }
}