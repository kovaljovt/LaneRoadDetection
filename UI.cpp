#include "UI.h"


UI::UI() {
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    QHBoxLayout* buttonLayout = new QHBoxLayout();

    QPushButton* startButton = new QPushButton("Start Button", this);
    QPushButton* stopButton = new QPushButton("Stop Button", this);
    QPushButton* restartButton = new QPushButton("Restart Button", this);

    startButtonStyling(*startButton);
    stopButtonStyling(*stopButton);
    restartButtonStyling(*restartButton);

    connect(startButton, &QPushButton::clicked, this, &UI::startButtonClick);
    connect(stopButton, &QPushButton::clicked, this, &UI::stopButtonClick);
    connect(restartButton, &QPushButton::clicked, this, &UI::restartButtonClick);

    buttonLayout->addWidget(startButton);
    buttonLayout->addWidget(stopButton);
    buttonLayout->addWidget(restartButton);

    mainLayout->addLayout(buttonLayout);

    setWindowTitle("Application");
    setFixedSize(windowWidth, windowHeight);
}


void UI::startButtonStyling(QPushButton& startButton) {

}


void UI::stopButtonStyling(QPushButton& stopButton) {

}


void UI::restartButtonStyling(QPushButton& restartButton) {

}


void UI::startButtonClick() {

}


void UI::stopButtonClick() {

}


void UI::restartButtonClick() {

}