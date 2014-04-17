#include "mainwindow.h"

void MainWindow::prepareMMPI2ResultTab()
{
    // 2 rows indepeendent and rest taken from array dynamicly
    // scales + (trin, vrin)
    ui->tableWidget_2->setRowCount(MMPI2::Q_SCALES + 2);
    ui->tableWidget_2->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget_2->verticalHeader()->setVisible(false);
    ui->tableWidget_2->horizontalHeader()->setVisible(true);

    QTableWidgetItem *newItem;

    // trin row
    newItem = new QTableWidgetItem(QString::fromStdString(MMPI2::trin_name));
    ui->tableWidget_2->setItem(0, 2, newItem);
    ui->tableWidget_2->item(0,2)->setFlags(Qt::ItemIsDragEnabled);
    newItem = new QTableWidgetItem("");
    ui->tableWidget_2->setItem(0, 0, newItem);
    ui->tableWidget_2->item(0,0)->setFlags(Qt::ItemIsDragEnabled);
    ui->tableWidget_2->item(0,0)->setTextAlignment(Qt::AlignCenter);
    newItem = new QTableWidgetItem("");
    ui->tableWidget_2->setItem(0, 1, newItem);
    ui->tableWidget_2->item(0,1)->setFlags(Qt::ItemIsDragEnabled);
    ui->tableWidget_2->item(0,1)->setTextAlignment(Qt::AlignCenter);

    // vrin row
    newItem = new QTableWidgetItem(QString::fromStdString(MMPI2::vrin_name));
    ui->tableWidget_2->setItem(1, 2, newItem);
    ui->tableWidget_2->item(1,2)->setFlags(Qt::ItemIsDragEnabled);
    newItem = new QTableWidgetItem("");
    ui->tableWidget_2->setItem(1, 0, newItem);
    ui->tableWidget_2->item(1,0)->setFlags(Qt::ItemIsDragEnabled);
    ui->tableWidget_2->item(1,0)->setTextAlignment(Qt::AlignCenter);
    newItem = new QTableWidgetItem("");
    ui->tableWidget_2->setItem(1, 1, newItem);
    ui->tableWidget_2->item(1,1)->setFlags(Qt::ItemIsDragEnabled);
    ui->tableWidget_2->item(1,1)->setTextAlignment(Qt::AlignCenter);

    // scales rows
    for(int ii = MMPI2_RESULT_TAB_MOV; ii < MMPI2::Q_SCALES + MMPI2_RESULT_TAB_MOV; ii++)
    {
        newItem = new QTableWidgetItem("");
        ui->tableWidget_2->setItem(ii, 0, newItem);
        ui->tableWidget_2->item(ii,0)->setFlags(Qt::ItemIsDragEnabled);
        ui->tableWidget_2->item(ii,0)->setTextAlignment(Qt::AlignCenter);
        newItem = new QTableWidgetItem("");
        ui->tableWidget_2->setItem(ii, 1, newItem);
        ui->tableWidget_2->item(ii,1)->setFlags(Qt::ItemIsDragEnabled);
        ui->tableWidget_2->item(ii,1)->setTextAlignment(Qt::AlignCenter);
        newItem = new QTableWidgetItem(QString::fromStdString(MMPI2::scales_names[ii - MMPI2_RESULT_TAB_MOV]));
        ui->tableWidget_2->setItem(ii, 2, newItem);
        ui->tableWidget_2->item(ii,2)->setFlags(Qt::ItemIsDragEnabled);
    }
}

void MainWindow::prepareMMPI2Table()
{
    ui->tableWidget->setRowCount(MMPI2::Q_QUESTIONS);
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget->verticalHeader()->setVisible(false);
    ui->tableWidget->horizontalHeader()->setVisible(true);
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

    mmpi2->update();
    mmpi2_update_result_tab();

    if(mmpi2_test_completed_check(column))
    {
        //ui->tabWidget_2->setCurrentIndex(1);

    }
    //qDebug() << m_scales[scale][0][nr] << ", ";
}

void MainWindow::mmpi2_update_result_tab()
{
    QTableWidgetItem *selected_item;

    selected_item = ui->tableWidget_2->item(0, 0);
    selected_item->setText(QString::number(mmpi2->trin_result));
    selected_item = ui->tableWidget_2->item(1, 0);
    selected_item->setText(QString::number(mmpi2->vrin_result));

    for(int row = MMPI2_RESULT_TAB_MOV; row < MMPI2::Q_SCALES + MMPI2_RESULT_TAB_MOV; row++)
    {
        selected_item = ui->tableWidget_2->item(row, 0);
        selected_item->setText(QString::number(mmpi2->scales_result[row - MMPI2_RESULT_TAB_MOV]));
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
            event_mmpi2_set_cell(row, col, false);
        else if(key == Qt::Key_Left)
            event_mmpi2_set_cell(row, col, true);
    }
}
