#include "mainwindow.h"
#include <QApplication>
#include <QDesktopWidget>
#include "qmqtt/qmqtt.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w(new QMQTT::Client());
    w.show();
    w.move ((QApplication::desktop()->width() - w.width())/2,(QApplication::desktop()->height() - w.height())/2);
    w.setFixedSize(800,600);
    return a.exec();
}
