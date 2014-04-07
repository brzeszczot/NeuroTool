#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "boost/regex.hpp"

namespace Ui
{
    class MainWindow;
}

//const boost::regex wyrazenie("[0-9a-z]{1,10}");

class MainWindow : public QMainWindow
{
    Q_OBJECT
    public:
        explicit MainWindow(QWidget *parent = 0);
        ~MainWindow();
    private:
        Ui::MainWindow *ui;
        //boost::cmatch matches;
};

#endif // MAINWINDOW_H
