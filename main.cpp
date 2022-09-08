/****************************************************************************
 *
 * @author Dilshod Mukhtarov <dilshodm(at)gmail.com>
 * Sep 2022
 *
 ****************************************************************************/

#include "mainwindow.h"
#include "version.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QCoreApplication::setApplicationName("TimezonesDisplay");
    QCoreApplication::setApplicationVersion(getVersion());

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
