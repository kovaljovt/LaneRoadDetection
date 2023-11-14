#include "UI.h"


UI::UI() {
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    QHBoxLayout* buttonLayout = new QHBoxLayout();

    QPushButton* startButton = new QPushButton("Start Button", this);
    QPushButton* stopButton = new QPushButton("Stop Button", this);
    QPushButton* restartButton = new QPushButton("Restart Button", this);
    QPushButton* backwardsButton = new QPushButton("Backwards Button", this);
    QPushButton* forwardsButton = new QPushButton("Forwards Button", this);

    startButtonStyle(*startButton);
    stopButtonStyle(*stopButton);
    restartButtonStyle(*restartButton);
    backwardsButtonStyle(*backwardsButton);
    forwardsButtonStyle(*forwardsButton);

    connect(startButton, &QPushButton::clicked, this, &UI::startButtonClick);
    connect(stopButton, &QPushButton::clicked, this, &UI::stopButtonClick);
    connect(restartButton, &QPushButton::clicked, this, &UI::restartButtonClick);
    connect(backwardsButton, &QPushButton::clicked, this, &UI::backwardsButtonClick);
    connect(forwardsButton, &QPushButton::clicked, this, &UI::forwardsButtonClick);

    buttonLayout->addWidget(startButton);
    buttonLayout->addWidget(stopButton);
    buttonLayout->addWidget(restartButton);

    mainLayout->addLayout(buttonLayout);

    setWindowTitle("Application");
    setFixedSize(windowWidth, windowHeight);
}


void UI::startButtonStyle(QPushButton& startButton) {
    startButton.setFocusPolicy(Qt::NoFocus);
    startButton.setStyleSheet(
            "QPushButton {"
               "background-color: #4CAF50;"
               "color: white;"
               "border: 2px solid #4CAF50;"
               "border-radius: 5px;"
               "padding: 5px;"
               "width: 50px;"
               "height: 50px;"
           "}"
   );
}


void UI::stopButtonStyle(QPushButton& stopButton) {
    stopButton.setFocusPolicy(Qt::NoFocus);
    stopButton.setStyleSheet(
            "QPushButton {"
                "background-color: #FF0000;"
                "color: white;"
                "border: 2px solid #FF0000;"
                "border-radius: 5px;"
                "padding: 5px;"
                "width: 50px;"
                "height: 50px;"
            "}"
    );
}


void UI::restartButtonStyle(QPushButton& restartButton) {
    restartButton.setFocusPolicy(Qt::NoFocus);
    restartButton.setStyleSheet(
            "QPushButton {"
                "background-color: #FFA500;"
                "color: white;"
                "border: 2px solid #FFA500;"
                "border-radius: 5px;"
                "padding: 5px;"
                "width: 50px;"
                "height: 50px;"
            "}"
    );
}


void UI::backwardsButtonStyle(QPushButton &backwardsButton) {

}


void UI::forwardsButtonStyle(QPushButton& forwardsButton) {

}


void UI::startButtonClick() {
    // Your start button click logic here
}


void UI::stopButtonClick() {
    // Your stop button click logic here
}


void UI::restartButtonClick() {
    // Your restart button click logic here
}


void UI::backwardsButtonClick() {

}


void UI::forwardsButtonClick() {

}

