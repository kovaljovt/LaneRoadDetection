#include "VideoPlayer.h"

int main(int argc, char** argv) {
//    QApplication application(argc, argv);
//    UI ui;
//    ui.show();
//
//    return QApplication::exec();

    std::vector<std::string> videoPaths = {
            "/home/tibor/Desktop/LaneRoadDetection/videos/dashcam1.mp4",
            "/home/tibor/Desktop/LaneRoadDetection/videos/dashcam1.mp4",
            "/home/tibor/Desktop/LaneRoadDetection/videos/dashcam1.mp4",
            "/home/tibor/Desktop/LaneRoadDetection/videos/dashcam1.mp4",
            "/home/tibor/Desktop/LaneRoadDetection/videos/dashcam1.mp4",
            "/home/tibor/Desktop/LaneRoadDetection/videos/dashcam1.mp4",
    };

    VideoPlayer player(videoPaths);

    player.run();

    return 0;
}
