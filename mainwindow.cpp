#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFocusPolicy(Qt::StrongFocus);

    setUpWidgets();
    createActions();
    createMenus();

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
    prepare_waisr_general_tab();
}

// prepare all events connections (SIGNAL -> SLOT)
void MainWindow::createActions()
{
    act_about = new QAction(tr("&O programie..."), this);
    connect(act_about, SIGNAL(triggered()), this, SLOT(about()));
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

