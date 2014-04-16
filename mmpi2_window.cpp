#include "mainwindow.h"

void MainWindow::prepareMMPI2ResultTab()
{
                                         // scales + (trin, vrin)
    ui->tableWidget_2->setRowCount(MMPI2::Q_SCALES + 2);
    ui->tableWidget_2->horizontalHeader()->setStretchLastSection(true);

    int ii;
    QTableWidgetItem *newItem;
    for(ii = 0; ii < MMPI2::Q_SCALES; ii++)
    {
        newItem = new QTableWidgetItem(QString::fromStdString(MMPI2::scales_names[ii]));
        ui->tableWidget_2->setItem(ii, 1, newItem);

   //     ui->tableWidget_2->item(ii,0)->setTextAlignment(Qt::AlignCenter);
        ui->tableWidget_2->item(ii,1)->setFlags(Qt::ItemIsDragEnabled);
    }

    newItem = new QTableWidgetItem(QString::fromStdString(MMPI2::trin_name));
    ui->tableWidget_2->setItem(ii, 1, newItem);
    ui->tableWidget_2->item(ii,1)->setFlags(Qt::ItemIsDragEnabled);
    ii++;
    newItem = new QTableWidgetItem(QString::fromStdString(MMPI2::vrin_name));
    ui->tableWidget_2->setItem(ii, 1, newItem);
    ui->tableWidget_2->item(ii,1)->setFlags(Qt::ItemIsDragEnabled);
}

void MainWindow::prepareMMPI2Table()
{
    ui->tableWidget->setRowCount(MMPI2::Q_QUESTIONS);
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget->setColumnWidth(0, 50);
//    QRegExp rx("[0-9]");
//    QValidator *validator = new QRegExpValidator(rx, this);

    QTableWidgetItem *newItem;
    //ui->tableWidget->rowCount()
    //mTestTable->removeRow(0);
    //mTestTable->setRowCount(0); // delete all cells automaticly
    for(size_t ii=0; ii<MMPI2::Q_QUESTIONS; ii++)
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
        ui->tableWidget->item(ii,1)->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsUserCheckable);
        ui->tableWidget->item(ii,2)->setFlags(Qt::ItemIsDragEnabled);
    }
   // QTableWidgetItem *a = ui->tableWidget->item(5,1);
   //int val = a->text().toInt();

    // create object MMPI-2 calculator
    mmpi2 = new MMPI2::Calc();
}

void MainWindow::event_mmpi2_set_cell(int row, int column, bool v)
{
    mmpi2->raw_answers[row] = v;

    ui->tableWidget->selectionModel()->clearSelection();
    QModelIndex next_cell = ui->tableWidget->model()->index(row+1, column);
    QTableWidgetItem *selected_item = ui->tableWidget->item(row,column);

    if(v)
    {
        selected_item->setText(TRUE_NAME);
        selected_item->setBackground(Qt::green);
        ui->tableWidget->selectionModel()->select(next_cell, QItemSelectionModel::Select);
        ui->tableWidget->setCurrentIndex(next_cell);
    }
    else
    {
        selected_item->setText(FALSE_NAME);
        selected_item->setBackground(Qt::red);
        ui->tableWidget->selectionModel()->select(next_cell, QItemSelectionModel::Select);
        ui->tableWidget->setCurrentIndex(next_cell);
    }

    if(mmpi2_test_completed_check(column))
    {
        //ui->tabWidget_2->setCurrentIndex(1);

    }
}

bool MainWindow::mmpi2_test_completed_check(int column)
{
    int cc = 0;
    for(int row = 0; row<ui->tableWidget->rowCount(); row++)
    {
        QTableWidgetItem *selected_item = ui->tableWidget->item(row, column);
        if(selected_item->text().toStdString().length() > 0)
            cc++;
    }
    if(cc == MMPI2::Q_QUESTIONS)
        return true;

    return false;
}

void MainWindow::event_mmpi2_new(int key)
{
    // handle events on mmpi2 table (Right key = true, Left key = false)
    int row, col;
    col = ui->tableWidget->selectionModel()->currentIndex().column();
    row = ui->tableWidget->selectionModel()->currentIndex().row();
    if(row >= 0 && col >= 0)
    {
        if(key == Qt::Key_Right)
            event_mmpi2_set_cell(row, col, true);
        else if(key == Qt::Key_Left)
            event_mmpi2_set_cell(row, col, false);
    }
}
