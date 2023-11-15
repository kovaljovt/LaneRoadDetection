#include <iostream>
#include <string>

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QApplication>
#include <QMessageLogger>
#include <QPalette>

#include <opencv2/opencv.hpp>


class UI: public QWidget {
private:
    int windowWidth = 1600;
    int windowHeight = 900;

public:
    UI();

    void startButtonStyle(QPushButton& startButton);
    void stopButtonStyle(QPushButton& stopButton);
    void restartButtonStyle(QPushButton& stopButton);
    void backwardsButtonStyle(QPushButton& backwardsButton);
    void forwardsButtonStyle(QPushButton& forwardsButton);

    void startButtonClick();
    void stopButtonClick();
    void restartButtonClick();
    void forwardsButtonClick();
    void backwardsButtonClick();
};