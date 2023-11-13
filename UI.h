#include <iostream>
#include <string>

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QApplication>

#include <opencv2/opencv.hpp>

#include "VideoPlayer.h"


class UI: public QWidget {
private:
    int windowWidth = 1600;
    int windowHeight = 900;

public:
    UI();

    void startButtonStyling(QPushButton& startButton);
    void stopButtonStyling(QPushButton& stopButton);
    void restartButtonStyling(QPushButton& restartButton);

    void startButtonClick();
    void stopButtonClick();
    void restartButtonClick();
};