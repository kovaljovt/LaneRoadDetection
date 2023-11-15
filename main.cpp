#include "UI.h"


int main(int argc, char** argv) {
    QApplication application(argc, argv);
    UI ui;
    ui.show();

    return QApplication::exec();
}
