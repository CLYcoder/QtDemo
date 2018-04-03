#include "mainwindow.h"

#include <QApplication>
#include <QCoreApplication>
#include <VLCQtCore/Common.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QCoreApplication::setApplicationName("VLC player");

    //VlcCommon::setPluginPath(a.applicationDirPath()+"/plugins");

    MainWindow w;
    w.show();

    return a.exec();
}
