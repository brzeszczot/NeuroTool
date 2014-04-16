#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

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
}

void MainWindow::setUpWidgets()
{
    ui->tabWidget->setTabText(0, QString::fromStdString(TAB_NAMES[MMPI2]));
    ui->tabWidget->setTabText(1, QString::fromStdString(TAB_NAMES[EMPTY]));

    prepareMMPI2Table();
    prepareMMPI2ResultTab();
}

void MainWindow::createActions()
{
    act_about = new QAction(tr("&O programie..."), this);
    connect(act_about, SIGNAL(triggered()), this, SLOT(about()));

    //connect(ui->tableWidget, SIGNAL(cellChanged(int, int)), this, SLOT(event_table_mmpi2_cell_changed(int,int)));
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
