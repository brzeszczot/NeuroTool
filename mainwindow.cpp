#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFocusPolicy(Qt::StrongFocus);

    setUpWidgets();
    createActions();
    createMenus();

    // waisr stuff....
    short int wp[WAISR::WP1] = {10,15,3,34,11,7,27,7,23,34,12};
    short int *wpx;
    // return 11 values
    wpx = WAISR::Calculate(wp,30);
    // return 6 values
    wpx = WAISR::Calculate2(wpx);
    //qDebug() << wpx[0] << ", ";

    //statusBar()->showMessage(tr("Program gotowy do pracy..."));
    //if(regex_match(selected_item->text().toStdString().c_str(), reg_matches, reg_true))
    // this->setWindowTitle(QString::fromStdString(program_full_name));
    //QSettings settings;
    /*
    #ifdef QT_DEBUG
      statusBar()->showMessage(tr("DEBUG"));
    #else
      statusBar()->showMessage(tr("RELEASE"));
    #endif
    */
    /*
    #ifdef Q_OS_MAC
       this->setWindowIcon(QIcon("ico.icns"));
    #endif
    */
}

// prepare all widgets
void MainWindow::setUpWidgets()
{
    ui->tabWidget->setTabText(0, QString::fromStdString(TAB_NAMES[MMPI2]));
    ui->tabWidget->setTabText(1, QString::fromStdString(TAB_NAMES[WAISR]));

    prepare_mmpi2_general_tab();
}

// prepare all events connections (SIGNAL -> SLOT)
void MainWindow::createActions()
{
    act_about = new QAction(tr("&O programie..."), this);
    connect(act_about, SIGNAL(triggered()), this, SLOT(about()));

    connect(ui->tabWidget_2, SIGNAL(currentChanged(int)), this, SLOT(mmpi2_tab_was_changed()));
    connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(mmpi2_test_true_button_pressed()));
    connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(mmpi2_test_false_button_pressed()));
    connect(ui->pushButton_5, SIGNAL(clicked()), this, SLOT(mmpi2_test_next_button_pressed()));
}

// create menu
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

// handle key events
void MainWindow::keyPressEvent(QKeyEvent *event)
{
    switch(ui->tabWidget->currentIndex())
    {
        case MMPI2: event_mmpi2_new(event->key()); break;
    }
}

MainWindow::~MainWindow()
{
    ui->tableWidget->clearContents();
    delete ui;
}
