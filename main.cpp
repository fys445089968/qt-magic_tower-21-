#include "mainwindow.h"
#include "storewindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    w.GameStart();
    w.show();

   return a.exec();
}



