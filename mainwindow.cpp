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




void MainWindow::on_pushButton_clicked()
{
    SecondWindow *secondWindow = new SecondWindow(this);
    secondWindow->show();
    this->hide();
}


void MainWindow::on_pushButton_2_clicked()
{
    ThirdWindow *thirdWindow = new ThirdWindow(this);
    thirdWindow->show();
    this->hide();
}


void MainWindow::on_pushButton_3_clicked()
{
    FourthWindow *fourthWindow = new FourthWindow(this);
    fourthWindow->show();
    this->hide();
}


void MainWindow::on_pushButton_4_clicked()
{
    FifthWindow *fifthWindow = new FifthWindow(this);
    fifthWindow->show();
    this->hide();
}

