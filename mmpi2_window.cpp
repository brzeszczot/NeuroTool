#include "mainwindow.h"

// prepare general settings for mmpi2 tab
void MainWindow::prepare_mmpi2_general_tab()
{
    connect(ui->tabWidget_2, SIGNAL(currentChanged(int)), this, SLOT(mmpi2_tab_was_changed()));
    connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(mmpi2_test_true_button_pressed()));
    connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(mmpi2_test_false_button_pressed()));
    connect(ui->pushButton_5, SIGNAL(clicked()), this, SLOT(mmpi2_test_next_button_pressed()));

    ui->pushButton_3->setText(TRUE_NAME);
    ui->pushButton_4->setText(FALSE_NAME);
    mmpi2_current_test_question = 0;

    prepareMMPI2Table();
    prepareMMPI2ResultTab();
}

// prepare table with calculated results
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

// prepare table with inputs data
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

// one of table cell was selected (set TRUE or FALSE depends on user selection "bool v")
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

    // calculate data and update result table
    mmpi2->update();
    mmpi2_update_result_tab();

    /*
    if(mmpi2_test_completed_check(column))
        ui->tabWidget_2->setCurrentIndex(1);
    */
}

// reset colour and text for all cells in main inputs table
void MainWindow::mmpi2_reset_table()
{
    ui->tableWidget->selectionModel()->clearSelection();
    for(int row = 0; row < ui->tableWidget->rowCount(); row++)
    {
        QTableWidgetItem *selected_item = ui->tableWidget->item(row, 1);
        selected_item->setText("");
        selected_item->setBackground(Qt::white);
    }
}

// update data inside results table depends on MMPI-2 calculated data
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

// check if user provide all TRUE / FALSE values into input table
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

// check which one buton was pressed (left arrow/right arrow)
void MainWindow::event_mmpi2_new(int key)
{
    // handle events on mmpi2 table (Right key = true, Left key = false)
    if(ui->tabWidget_2->currentIndex() == 0)
    {
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

    // handle events on mmpi2 test
    if(ui->tabWidget_2->currentIndex() == 2)
    {
        if(key == Qt::Key_Period && ui->pushButton_4->isEnabled())
            mmpi2_test_false_button_pressed();
        else if(key == Qt::Key_Comma && ui->pushButton_3->isEnabled())
            mmpi2_test_true_button_pressed();
        else if(key == Qt::Key_Space && ui->pushButton_5->isEnabled())
            mmpi2_test_next_button_pressed();
    }
}

// user changed tab - if "new test" tab was selected ask question "start test or not"
void MainWindow::mmpi2_tab_was_changed()
{
    if(ui->tabWidget_2->currentIndex() == 2)
    {
        // set widgets for test
        mmpi2_set_question_and_statusbar();
        ui->pushButton_3->setEnabled(true);
        ui->pushButton_4->setEnabled(true);
        ui->pushButton_5->setEnabled(false);
        ui->pushButton_3->setStyleSheet("font: none; text-decoration: none;");
        ui->pushButton_4->setStyleSheet("font: none; text-decoration: none;");

        // ask question
        QMessageBox box;
        box.addButton(QMessageBox::Yes);
        box.addButton(QMessageBox::No);
        if(mmpi2_current_test_question > 0)
        {
            box.addButton(QMessageBox::Ok);
            box.button(QMessageBox::Ok)->setText("Kontynuuj test");
        }
        box.setText("Czy chcesz rozpocząć nowy test?");
        box.button(QMessageBox::Yes)->setText("Tak");
        box.button(QMessageBox::No)->setText("Nie");
        int reply = box.exec();       

        // handle question
        if (reply == QMessageBox::Yes)
        {
            mmpi2_current_test_question = 0;    // (0) set question number one (for debug set 565)
            mmpi2->reset_arrays();
            mmpi2_update_result_tab();
            mmpi2_reset_table();
            mmpi2_set_question_and_statusbar();
        }
        else if (reply == QMessageBox::No)
            ui->tabWidget_2->setCurrentIndex(0);

        // update progressbar
        ui->progressBar->setValue(floor((mmpi2_current_test_question * 100) / MMPI2::Q_QUESTIONS));
    }
}

// true button pressed
void MainWindow::mmpi2_test_true_button_pressed()
{
    mmpi2->raw_answers[mmpi2_current_test_question] = true;
    ui->pushButton_3->setStyleSheet("font: bold; text-decoration: underline;");
    ui->pushButton_4->setStyleSheet("font: none; text-decoration: none;");
    ui->pushButton_5->setEnabled(true);
    statusBar()->showMessage(tr("Wybrano: PRAWDA"));
}

// false button pressed
void MainWindow::mmpi2_test_false_button_pressed()
{
    mmpi2->raw_answers[mmpi2_current_test_question] = false;
    ui->pushButton_4->setStyleSheet("font: bold; text-decoration: underline;");
    ui->pushButton_3->setStyleSheet("font: none; text-decoration: none;");
    ui->pushButton_5->setEnabled(true);
    statusBar()->showMessage(tr("Wybrano: FAŁSZ"));
}

// next question button pressed
void MainWindow::mmpi2_test_next_button_pressed()
{
    // update calculations
    mmpi2->update();
    mmpi2_update_result_tab();

    // update main input tab (colour and text)
    QTableWidgetItem *selected_item = ui->tableWidget->item(mmpi2_current_test_question, 1);
    if(mmpi2->raw_answers[mmpi2_current_test_question])
    {
        selected_item->setText(TRUE_NAME);
        selected_item->setBackground(Qt::green);
    }
    else
    {
        selected_item->setText(FALSE_NAME);
        selected_item->setBackground(Qt::red);
    }

    // select next question
    if(mmpi2_current_test_question < MMPI2::Q_QUESTIONS)
        mmpi2_current_test_question++;

    // update progressbar
    ui->progressBar->setValue(floor((mmpi2_current_test_question * 100) / MMPI2::Q_QUESTIONS));

    // if test ends - move to results tab
    if(mmpi2_current_test_question >= MMPI2::Q_QUESTIONS)
    {
        ui->label->setText("Koniec testu. Dziękuję.");
        statusBar()->showMessage("");
        ui->pushButton_3->setEnabled(false);
        ui->pushButton_4->setEnabled(false);
        mmpi2_current_test_question = 0;
    }
    else
        mmpi2_set_question_and_statusbar();

    ui->pushButton_3->setStyleSheet("font: none; text-decoration: none;");
    ui->pushButton_4->setStyleSheet("font: none; text-decoration: none;");
    ui->pushButton_5->setEnabled(false);
}

// set statusbar and proper question
void MainWindow::mmpi2_set_question_and_statusbar()
{
    statusBar()->showMessage("Pytanie nr " + QString::number(mmpi2_current_test_question + 1) + " z " + QString::number(MMPI2::Q_QUESTIONS));
    ui->label->setText(QString::number(mmpi2_current_test_question + 1) + ". " + QString::fromStdString(MMPI2::questions[mmpi2_current_test_question]));
}
