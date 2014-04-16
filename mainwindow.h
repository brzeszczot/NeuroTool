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
#include <QtDebug>
//#include <QRegExpValidator>
//#include <QSettings>

#include "boost/regex.hpp"
#include "ui_mainwindow.h"
#include "mmpi2.hpp"

#define MMPI2_RESULT_TAB_MOV    2
const std::string TAB_NAMES[2] = {"MMPI-2", "..."};

namespace Ui
{
    class MainWindow;
}

const boost::regex reg_true("[pP]{1}");

class MainWindow: public QMainWindow
{
    Q_OBJECT
    public:
        // must ovelap with TAB_NAMES array
        enum TABS {MMPI2, EMPTY};
        explicit MainWindow(QWidget *parent = 0);
        ~MainWindow();
    private slots:
        void about();
    private:
        void keyPressEvent(QKeyEvent*);
        void setUpWidgets();
        void createActions();
        void createMenus();
        // mmpi2
        void prepareMMPI2Table();
        void prepareMMPI2ResultTab();
        void event_mmpi2_new(int key);
        void event_mmpi2_set_cell(int row, int column, bool v);
        bool mmpi2_test_completed_check(int column);
        void mmpi2_update_result_tab();

        Ui::MainWindow *ui;
        QAction *act_about;
        QMenu *menu_program;
        MMPI2::Calc *mmpi2;
        boost::cmatch reg_matches;
};

#endif // MAINWINDOW_H
