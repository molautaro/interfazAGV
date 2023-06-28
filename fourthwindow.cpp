#include "fourthwindow.h"
#include "mainwindow.h"
#include "ui_fourthwindow.h"

FourthWindow::FourthWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FourthWindow)
{
    ui->setupUi(this);
}

FourthWindow::~FourthWindow()
{
    delete ui;
}

void FourthWindow::on_pushButton_clicked()
{
    MainWindow * mainWindow = new MainWindow(this);
    mainWindow->show();
    this->hide();
}

