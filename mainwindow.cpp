#include "mainwindow.h"
#include "secondwindow.h"
#include "thirdwindow.h"
#include "fourthwindow.h"
#include "fifthwindow.h"
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
}


void MainWindow::on_pushButton_11_pressed()
{
    ui->stackedWidget->setCurrentIndex(1);
}


void MainWindow::on_pushButton_13_pressed()
{
    ui->stackedWidget->setCurrentIndex(1);
}


void MainWindow::on_pushButton_10_pressed()
{
    ui->stackedWidget->setCurrentIndex(1);
}


void MainWindow::on_pushButton_12_pressed()
{
    ui->stackedWidget->setCurrentIndex(1);
}


void MainWindow::on_pushButton_14_pressed()
{
    ui->stackedWidget->setCurrentIndex(1);
}


void MainWindow::on_pushButton_pressed()
{
    ui->stackedWidget->setCurrentIndex(0);

}

