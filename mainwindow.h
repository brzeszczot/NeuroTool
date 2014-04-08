#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#define TRUE_NAME       "Prawda"
#define FALSE_NAME      "Fałsz"

#include <QMainWindow>
#include <QMessageBox>
#include <QSettings>
#include "boost/regex.hpp"

namespace Ui
{
    class MainWindow;
}

//const boost::regex wyrazenie("[0-9a-z]{1,10}");

class MainWindow: public QMainWindow
{
    Q_OBJECT
    public:
        explicit MainWindow(QWidget *parent = 0);
        ~MainWindow();
    private slots:
        void mmpi2_admin();
        void about();
    private:
        void setUpWidgets();
        void createActions();
        void createMenus();
        Ui::MainWindow *ui;
        QAction *act_mmpi2_patient;
        QAction *act_mmpi2_admin;
        QAction *act_about;
        QMenu *menu_mmpi2;

        //boost::cmatch matches;
};

#endif // MAINWINDOW_H
