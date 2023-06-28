#include "thirdwindow.h"
#include "mainwindow.h"
#include "ui_thirdwindow.h"

ThirdWindow::ThirdWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ThirdWindow)
{
    ui->setupUi(this);
}

ThirdWindow::~ThirdWindow()
{
    delete ui;
}

void ThirdWindow::on_pushButton_clicked()
{
    MainWindow * mainWindow = new MainWindow(this);
    mainWindow->show();
    this->hide();
}

