#include "VideoPlayer.h"


VideoPlayer::VideoPlayer() = default;


void VideoPlayer::initializeVideoCapture() {
    videoCapture.open(videoPaths[videoIndex]);
}


cv::Mat VideoPlayer::getFrame() {
    videoCapture.read(img);
    return img;
}


void VideoPlayer::nextVideo() {
    videoIndex = (videoIndex + 1) % videoPaths.size();
    switchVideo();
}


void VideoPlayer::previousVideo() {
    videoIndex = (videoIndex - 1) % videoPaths.size();
    switchVideo();
}


void VideoPlayer::switchVideo() {
    videoCapture.release();
    videoCapture.open(videoPaths[videoIndex]);
}