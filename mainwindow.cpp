#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    pl = new ProgramLogic;

    // set spinBoxes parameters
    ui->spinBox_max_url->setMaximum(10000);
    ui->spinBox_number_scan_theads->setMaximum(1000);
    ui->spinBox_number_dewnload_threads->setMaximum(1000);

    ui->spinBox_max_url->setValue(10);
    ui->spinBox_number_scan_theads->setValue(2);
    ui->spinBox_number_dewnload_threads->setValue(1);

    // set text clases patameters
    ui->lineEdit_url->setText("https://curl.haxx.se/libcurl/");
    ui->plainTextEdit_search_text->document()->setPlainText("is");

    // connect signals to slots
    connect(ui->pushButton_start, SIGNAL (clicked()), this, SLOT (start()));
    connect(ui->pushButton_pause, SIGNAL (clicked()), this, SLOT (pause()));
    connect(ui->pushButton_stop, SIGNAL (clicked()), this, SLOT (stop()) );
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::start()
{
    QString text = ui->plainTextEdit_search_text->toPlainText();
    QString url = ui->lineEdit_url->text();

    pl->set_research_text(text.toLocal8Bit().constData());
    pl->set_start_url(url.toLocal8Bit().constData());

    pl->set_number_threads_scan(ui->spinBox_number_scan_theads->value());
    pl->set_number_threads_download(ui->spinBox_number_dewnload_threads->value());
    pl->set_maximun_scan_url(ui->spinBox_max_url->value());

    pl->start();
}





