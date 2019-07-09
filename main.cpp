#include "mainwindow.h"
#include <QApplication>
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    //w.setWindowState(w.windowState() ^ Qt::WindowFullScreen);
    //w.showFullScreen();
    w.update();
    w.show();


    int largeurEcran = QApplication::desktop()->width();
    int hauteurEcran = QApplication::desktop()->height();

    cout << largeurEcran << "  " <<hauteurEcran << endl;


    return a.exec();
}
