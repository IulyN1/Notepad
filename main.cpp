#include "Notepad.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Notepad* ui = new Notepad;
    ui->show();
    return a.exec();
}
