#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setUpWidgets();
    createActions();
    createMenus();

    mmpi2 = new MMPI2::Calc();

    //statusBar()->showMessage(tr("Program gotowy do pracy..."));
/*
#ifdef QT_DEBUG
  statusBar()->showMessage(tr("DEBUG"));
#else
  statusBar()->showMessage(tr("RELEASE"));
#endif
*/
/*
if(regex_match(selected_item->text().toStdString().c_str(), reg_matches, reg_true))
*/
    // this->setWindowTitle(QString::fromStdString(program_full_name));
    //QSettings settings;
}

void MainWindow::setUpWidgets()
{
    prepareMMPI2Table();
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
    // handle events on mmpi2 table (Right key = true, Left key = false)
    int row, col;
    col = ui->tableWidget->selectionModel()->currentIndex().column();
    row = ui->tableWidget->selectionModel()->currentIndex().row();
    if(row >= 0 && col >= 0)
    {
        if(event->key() == Qt::Key_Right)
            event_mmpi2_set_cell(row, col, true);
        else if(event->key() == Qt::Key_Left)
            event_mmpi2_set_cell(row, col, false);
    }
}

MainWindow::~MainWindow()
{
    ui->tableWidget->clearContents();
    delete ui;
}
