#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setUpWidgets();
    createActions();
    createMenus();
    statusBar()->showMessage(tr("Program gotowy do pracy..."));
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

void MainWindow::mmpi2_admin()
{
    statusBar()->showMessage(tr("MMPI-2 (szybkie wprowadzanie)"));

    //ui->tableWidget->setEnabled(true);
    //ui->tableWidget->setVisible(true);
}

void MainWindow::setUpWidgets()
{
    prepareMMPITable();
}

void MainWindow::prepareMMPITable()
{
    ui->tableWidget->setRowCount(Q_QUESTIONS);

//    QRegExp rx("[0-9]");
//    QValidator *validator = new QRegExpValidator(rx, this);

    QTableWidgetItem *newItem;
    for(size_t ii=0; ii<Q_QUESTIONS; ii++)
    {
        //QString::number(ii+1)
        newItem = new QTableWidgetItem("");
        ui->tableWidget->setItem(ii, 0, newItem);
        newItem = new QTableWidgetItem("QString::number(ii+1)");
        ui->tableWidget->item(ii,1)->setFlags(NULL);

        //ui->tableWidget->item(ii,1)->setValidator(validator);

        ui->tableWidget->setItem(ii, 1, newItem);
    }
/*
    QTableWidgetItem *a = tableWidgetMMPI->item(5,0);
   int val = a->text().toInt();
*/
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
    delete ui;
}
