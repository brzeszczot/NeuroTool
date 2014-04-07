#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

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

MainWindow::~MainWindow()
{
    delete ui;
}
