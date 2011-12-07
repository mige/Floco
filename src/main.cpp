#include <QtGui/QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    a.setApplicationName("Floco");
    a.setApplicationVersion("1.0alpha");
    a.setOrganizationDomain("cz.nejdr");
    a.setOrganizationName("nejdr.cz");

    MainWindow w;
    w.show();

    return a.exec();
}
