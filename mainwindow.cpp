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


void MainWindow::on_pushButton_3_clicked()
{
    SecondWindow *secondWindow = new SecondWindow(this);
    secondWindow->show();
    this->hide();

}

