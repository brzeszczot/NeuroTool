#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setUpWidgets();
    createActions();
    createMenus();
    //statusBar()->showMessage(tr("Program gotowy do pracy..."));
/*
#ifdef QT_DEBUG
  statusBar()->showMessage(tr("DEBUG"));
#else
  statusBar()->showMessage(tr("RELEASE"));
#endif
*/
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

void MainWindow::setUpWidgets()
{
    prepareMMPITable();
}

void MainWindow::prepareMMPITable()
{
    ui->tableWidget->setRowCount(Q_QUESTIONS);
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget->setColumnWidth(0, 30);
//    QRegExp rx("[0-9]");
//    QValidator *validator = new QRegExpValidator(rx, this);

    QTableWidgetItem *newItem;
    //ui->tableWidget->rowCount()
    //mTestTable->removeRow(0);
    //mTestTable->setRowCount(0); // delete all cells automaticly
    for(size_t ii=0; ii<Q_QUESTIONS; ii++)
    {
        //QString::number(ii+1)
        newItem = new QTableWidgetItem(QString::number(ii+1));
        ui->tableWidget->setItem(ii, 0, newItem);
        newItem = new QTableWidgetItem("");
        ui->tableWidget->setItem(ii, 1, newItem);
        newItem = new QTableWidgetItem(QString::fromStdString(MMPI2::questions[ii]));
        ui->tableWidget->setItem(ii, 2, newItem);
/*
QCheckBox* checkBox = new QCheckBox();
ui->tableWidget->setCellWidget(rowCount, column, checkBox);
*/
       // ui->tableWidget->item(ii,1)->setValidator(validator);
        ui->tableWidget->item(ii,0)->setTextAlignment(Qt::AlignCenter);
        ui->tableWidget->item(ii,0)->setFlags(Qt::ItemIsDragEnabled);
        ui->tableWidget->item(ii,2)->setFlags(Qt::ItemIsDragEnabled);
    }
   // QTableWidgetItem *a = ui->tableWidget->item(5,1);
   //int val = a->text().toInt();
}

void MainWindow::createActions()
{
    act_about = new QAction(tr("&O programie..."), this);
    connect(act_about, SIGNAL(triggered()), this, SLOT(about()));

    connect(ui->tableWidget, SIGNAL(cellChanged(int, int)), this, SLOT(event_table_mmpi2_cell_changed(int,int)));
}

void MainWindow::createMenus()
{
    act_about->setMenuRole(QAction::AboutRole);
    menu_program = ui->menuBar->addMenu(tr("&NeuroTool"));
    menu_program->addAction(act_about);
    //menuBar()->addSeparator();
}

void MainWindow::about()
{
    QMessageBox::about(this, tr("O programie..."), tr("brzeszczot@gmail.com"));
}

MainWindow::~MainWindow()
{
    ui->tableWidget->clearContents();
    delete ui;
}

void MainWindow::event_table_mmpi2_cell_changed(int row, int column)
{
    ui->tableWidget->selectionModel()->clearSelection();

    QModelIndex next_cell = ui->tableWidget->model()->index(row+1, column);
    QModelIndex current_cell = ui->tableWidget->model()->index(row, column);

    QTableWidgetItem *selected_item = ui->tableWidget->item(row,column);
    if(regex_match(selected_item->text().toStdString().c_str(), reg_matches, reg_true))
    {
        selected_item->setText(TRUE_NAME);
        selected_item->setBackground(Qt::green);
        ui->tableWidget->selectionModel()->select(next_cell, QItemSelectionModel::Select);
        ui->tableWidget->setCurrentIndex(next_cell);
    }
    else if(regex_match(selected_item->text().toStdString().c_str(), reg_matches, reg_false))
    {
        selected_item->setText(FALSE_NAME);
        selected_item->setBackground(Qt::red);
        ui->tableWidget->selectionModel()->select(next_cell, QItemSelectionModel::Select);
        ui->tableWidget->setCurrentIndex(next_cell);
    }
    else
    {
        ui->tableWidget->selectionModel()->select(current_cell, QItemSelectionModel::Select);
        //ui->tableWidget->setCurrentIndex(current_cell);
        //selected_item->setBackground(Qt::white);
    }
}
