#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#define TRUE_NAME       "Prawda"
#define FALSE_NAME      "Fałsz"

#include <QMainWindow>
#include <QDesktopWidget>
#include <QTableWidget>
#include <QHeaderView>
#include <QMessageBox>
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
        void event_table_mmpi2_cell_changed(int row, int column);
    private:
        void setUpWidgets();
        void createActions();
        void createMenus();
        void prepareMMPITable();
        Ui::MainWindow *ui;
        QAction *act_about;
        QMenu *menu_program;
        boost::cmatch reg_matches;
};

#endif // MAINWINDOW_H
