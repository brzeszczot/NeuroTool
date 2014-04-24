#include "mainwindow.h"

// prepare general settings for waisr tab
void MainWindow::prepare_waisr_general_tab()
{
    connect(ui->lineEdit_12, SIGNAL(textChanged(QString)), this, SLOT(waisr_text_changed()));
    connect(ui->lineEdit, SIGNAL(textChanged(QString)), this, SLOT(waisr_text_changed()));
    connect(ui->lineEdit_2, SIGNAL(textChanged(QString)), this, SLOT(waisr_text_changed()));
    connect(ui->lineEdit_3, SIGNAL(textChanged(QString)), this, SLOT(waisr_text_changed()));
    connect(ui->lineEdit_4, SIGNAL(textChanged(QString)), this, SLOT(waisr_text_changed()));
    connect(ui->lineEdit_5, SIGNAL(textChanged(QString)), this, SLOT(waisr_text_changed()));
    connect(ui->lineEdit_6, SIGNAL(textChanged(QString)), this, SLOT(waisr_text_changed()));
    connect(ui->lineEdit_7, SIGNAL(textChanged(QString)), this, SLOT(waisr_text_changed()));
    connect(ui->lineEdit_8, SIGNAL(textChanged(QString)), this, SLOT(waisr_text_changed()));
    connect(ui->lineEdit_9, SIGNAL(textChanged(QString)), this, SLOT(waisr_text_changed()));
    connect(ui->lineEdit_10, SIGNAL(textChanged(QString)), this, SLOT(waisr_text_changed()));
    connect(ui->lineEdit_11, SIGNAL(textChanged(QString)), this, SLOT(waisr_text_changed()));

    ui->lineEdit_12->setValidator(new QIntValidator(0, 200, this));
    ui->lineEdit->setValidator(new QIntValidator(0, 100, this));
    ui->lineEdit_2->setValidator(new QIntValidator(0, 100, this));
    ui->lineEdit_3->setValidator(new QIntValidator(0, 100, this));
    ui->lineEdit_4->setValidator(new QIntValidator(0, 100, this));
    ui->lineEdit_5->setValidator(new QIntValidator(0, 100, this));
    ui->lineEdit_6->setValidator(new QIntValidator(0, 100, this));
    ui->lineEdit_7->setValidator(new QIntValidator(0, 100, this));
    ui->lineEdit_8->setValidator(new QIntValidator(0, 100, this));
    ui->lineEdit_9->setValidator(new QIntValidator(0, 100, this));
    ui->lineEdit_10->setValidator(new QIntValidator(0, 100, this));
    ui->lineEdit_11->setValidator(new QIntValidator(0, 100, this));
}

void MainWindow::waisr_text_changed()
{
    short int wp[WAISR::WP1];
    short int *wpx;

    wp[0] = ui->lineEdit->text().toInt();
    wp[1] = ui->lineEdit_2->text().toInt();
    wp[2] = ui->lineEdit_3->text().toInt();
    wp[3] = ui->lineEdit_4->text().toInt();
    wp[4] = ui->lineEdit_5->text().toInt();
    wp[5] = ui->lineEdit_6->text().toInt();
    wp[6] = ui->lineEdit_7->text().toInt();
    wp[7] = ui->lineEdit_8->text().toInt();
    wp[8] = ui->lineEdit_9->text().toInt();
    wp[9] = ui->lineEdit_10->text().toInt();
    wp[10] = ui->lineEdit_11->text().toInt();

    // return 11 values (wyniki przeliczone)
    wpx = WAISR::Calculate(wp, ui->lineEdit_12->text().toInt());

    ui->label_15->setText(QString::number(wpx[0]));
    ui->label_16->setText(QString::number(wpx[1]));
    ui->label_17->setText(QString::number(wpx[2]));
    ui->label_18->setText(QString::number(wpx[3]));
    ui->label_19->setText(QString::number(wpx[4]));
    ui->label_20->setText(QString::number(wpx[5]));
    ui->label_21->setText(QString::number(wpx[6]));
    ui->label_22->setText(QString::number(wpx[7]));
    ui->label_23->setText(QString::number(wpx[8]));
    ui->label_24->setText(QString::number(wpx[9]));
    ui->label_25->setText(QString::number(wpx[10]));

    // return 6 values (IQ, Wyniki czynnikowe)
    wpx = WAISR::Calculate2(wpx);


    ui->label_33->setText(QString::fromStdString(waisr_check_range(wpx[0])));
    ui->label_34->setText(QString::fromStdString(waisr_check_range(wpx[1])));
    ui->label_35->setText(QString::fromStdString(waisr_check_range(wpx[2])));
    ui->label_26->setText(QString::fromStdString(waisr_check_range(wpx[3])));
    ui->label_27->setText(QString::fromStdString(waisr_check_range(wpx[4])));
    ui->label_29->setText(QString::fromStdString(waisr_check_range(wpx[5])));

    delete[] wpx;
}

std::string MainWindow::waisr_check_range(int value)
{
    if(value < 45)
        return "< 45";
    else if(value >= 45 && value <= 150)
    {
        std::ostringstream ss;
        ss << value;
        return ss.str();
    }
    else
        return "> 150";
}
