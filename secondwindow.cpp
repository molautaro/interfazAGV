#include "secondwindow.h"
#include "mainwindow.h"
#include "./ui_secondwindow.h"

SecondWindow::SecondWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SecondWindow)
{
    ui->setupUi(this);
}

SecondWindow::~SecondWindow()
{
    delete ui;
}

void SecondWindow::on_pushButton_3_clicked()
{
    MainWindow * mainWindow = new MainWindow(this);
    mainWindow->show();
    this->hide();
}

