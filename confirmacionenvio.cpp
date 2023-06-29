#include "confirmacionenvio.h"
#include "ui_confirmacionenvio.h"

confirmacionEnvio::confirmacionEnvio(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::confirmacionEnvio)
{
    ui->setupUi(this);
}

confirmacionEnvio::~confirmacionEnvio()
{
    delete ui;
}

void confirmacionEnvio::on_pushButton_clicked()
{
    emit botonPresionadoSI();
    this->close();
}


void confirmacionEnvio::on_pushButton_2_clicked()
{
    emit botonPresionadoNO();
    this->close();
}

