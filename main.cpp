#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    //Задать заголовок окна
    w.setWindowTitle("Notepad");
    w.show();
    return a.exec();
}
