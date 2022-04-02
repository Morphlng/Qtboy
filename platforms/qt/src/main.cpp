#include "mainwindow.h"
#include <QApplication>
#include <iostream>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QCoreApplication::setOrganizationName("David Tran");
    QCoreApplication::setApplicationName("Qtboy");
    QCoreApplication::setApplicationVersion(QT_VERSION_STR);

    MainWindow mainWin(nullptr, "QtBoy");
    mainWin.show();
    return app.exec();
}
