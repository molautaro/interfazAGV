#include "fifthwindow.h"
#include "mainwindow.h"
#include "ui_fifthwindow.h"

FifthWindow::FifthWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FifthWindow)
{
    ui->setupUi(this);
}

FifthWindow::~FifthWindow()
{
    delete ui;
}

void FifthWindow::on_pushButton_clicked()
{
    MainWindow * mainWindow = new MainWindow(this);
    mainWindow->show();
    this->hide();
}

