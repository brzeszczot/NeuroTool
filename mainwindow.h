#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#define TRUE_NAME       "Prawda"
#define FALSE_NAME      "Fałsz"

#include <QMainWindow>
#include <QDesktopWidget>
#include <QTableWidget>
#include <QHeaderView>
#include <QMessageBox>
#include <QKeyEvent>
//#include <QRegExpValidator>
//#include <QSettings>

#include "boost/regex.hpp"
#include "ui_mainwindow.h"
#include "mmpi2.hpp"

namespace Ui
{
    class MainWindow;
}

const boost::regex reg_true("[pP]{1}");
const boost::regex reg_false("[fF]{1}");

class MainWindow: public QMainWindow
{
    Q_OBJECT
    public:
        explicit MainWindow(QWidget *parent = 0);
        ~MainWindow();
    private slots:
        void about();
    private:
        void setUpWidgets();
        void createActions();
        void createMenus();
        void prepareMMPITable();
        void keyPressEvent(QKeyEvent*);
        void event_mmpi2_set_cell(int row, int column, bool v);
        Ui::MainWindow *ui;
        QAction *act_about;
        QMenu *menu_program;
        boost::cmatch reg_matches;
};

#endif // MAINWINDOW_H
