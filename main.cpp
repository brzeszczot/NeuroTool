#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setOrganizationName("Brzeszczot");
    a.setApplicationName("NeuroTool");
    a.setApplicationVersion("0.1");
    MainWindow w;
    w.show();

    return a.exec();
}
