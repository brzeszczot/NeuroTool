#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mmpi2.hpp"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setUpWidgets();
    createActions();
    createMenus();
    statusBar()->showMessage(tr("Program gotowy do pracy..."));

    //this->setWindowTitle(QCoreApplication::applicationName());
    // this->setWindowTitle(QString::fromStdString(program_full_name));
    //QSettings settings;
    /*
    std::string str = "alamakota";
    if(regex_match(str.c_str(), matches, wyrazenie))
    {
        ui->pushButton->move(0, 0);
        ui->pushButton->setFixedWidth(300);
        ui->pushButton->setText(QString::fromStdString(str));
    }
    */
}

void MainWindow::mmpi2_admin()
{
    statusBar()->showMessage(tr("MMPI-2 (Szybkie wprowadzanie)"));

    ui->tableWidget->setEnabled(true);
    ui->tableWidget->setVisible(true);
}

void MainWindow::setUpWidgets()
{
    ui->tableWidget->setEnabled(false);
    ui->tableWidget->setVisible(false);
}

void MainWindow::createActions()
{
    act_mmpi2_patient = new QAction(tr("&Rozpocznij test"), this);
    //act_mmpi2_patient->setShortcuts(QKeySequence::Open);
    //act_mmpi2_patient->setStatusTip(tr("Open an existing file"));
    //connect(act_mmpi2_patient, SIGNAL(triggered()), this, SLOT(open()));

    act_mmpi2_admin = new QAction(tr("&Szybkie wprowadzanie"), this);
    connect(act_mmpi2_admin, SIGNAL(triggered()), this, SLOT(mmpi2_admin()));

    act_about = new QAction(tr("&O programie..."), this);
    connect(act_about, SIGNAL(triggered()), this, SLOT(about()));

    // mac osx
    //act_mmpi2_patient->setMenuRole(QAction::PreferencesRole);
}

void MainWindow::createMenus()
{
    menu_mmpi2 = ui->menuBar->addMenu(tr("&MMPI-2"));
    menu_mmpi2->addAction(act_mmpi2_patient);
    menu_mmpi2->addAction(act_mmpi2_admin);

    act_about->setMenuRole(QAction::AboutRole);
    menu_mmpi2->addAction(act_about);
    //menuBar()->addSeparator();
}

void MainWindow::about()
{
   QMessageBox::about(this, tr("O programie..."), tr("brzeszczot@gmail.com"));
}

MainWindow::~MainWindow()
{
    delete ui;
}
