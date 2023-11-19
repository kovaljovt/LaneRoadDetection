#include "VideoPlayer.h"


int main() {
    VideoPlayer player;
    player.initializeVideoCapture();
    player.run();

    return 0;
}