#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_9_pressed()
{
    ui->stackedWidget->setCurrentIndex(1);
    ui->label_2->setText("Viajando a Estacion 2");
}


void MainWindow::on_pushButton_11_pressed()
{
    ui->stackedWidget->setCurrentIndex(1);
    ui->label_2->setText("Viajando a Estacion 3");
}


void MainWindow::on_pushButton_13_pressed()
{
    ui->stackedWidget->setCurrentIndex(1);
    ui->label_2->setText("Viajando a Estacion 4");
}


void MainWindow::on_pushButton_10_pressed()
{
    ui->stackedWidget->setCurrentIndex(1);
    ui->label_2->setText("Viajando a Estacion 5");
}


void MainWindow::on_pushButton_12_pressed()
{
    ui->stackedWidget->setCurrentIndex(1);
    ui->label_2->setText("Viajando a Estacion 6");
}


void MainWindow::on_pushButton_14_pressed()
{
    ui->stackedWidget->setCurrentIndex(1);
    ui->label_2->setText("Viajando a Estacion 7");
}


void MainWindow::on_pushButton_pressed()
{
    ui->stackedWidget->setCurrentIndex(0);
}
