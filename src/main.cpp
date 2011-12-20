#include <QtGui/QApplication>
#include <QTextCodec>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    a.setApplicationName("Floco");
    a.setApplicationVersion("1.0alpha");
    a.setOrganizationDomain("cz.nejdr");
    a.setOrganizationName("nejdr.cz");

    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));

    MainWindow w;
    w.show();

    return a.exec();
}
