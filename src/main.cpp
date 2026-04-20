#include "mainwindow.h"

#include <QApplication>
#include <QCoreApplication>
#include <QSqlDatabase>
#include <QDebug>
#include <QLibraryInfo>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
