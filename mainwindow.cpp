#include "mainwindow.h"
#include "confirmacionenvio.h"
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


void MainWindow::mostrarConfirmacionEnvio() {
    confirmacionEnvio* ventanaEmergente = new confirmacionEnvio(this);
    connect(ventanaEmergente, &confirmacionEnvio::botonPresionadoSI, this, &MainWindow::manejarBotonPresionadoSI);
    connect(ventanaEmergente, &confirmacionEnvio::botonPresionadoNO, this, &MainWindow::manejarBotonPresionadoNO);
    ventanaEmergente->setAttribute(Qt::WA_DeleteOnClose);
    ventanaEmergente->setModal(true);
    ventanaEmergente->show();
}

void MainWindow::on_BotonEst2_pressed()
{
    estacion = "2";
    mostrarConfirmacionEnvio();

}

void MainWindow::manejarBotonPresionadoSI() //CUANDO TOCA BOTON SI - EN LA VENTANA EMERGENTE
{
    // Escribe aquí el código que se debe ejecutar cuando se hace clic en el botón.
    ui->stackedWidget->setCurrentIndex(1);
    ui->label_2->setText("Viajando a Estacion " + estacion);
}

void MainWindow::manejarBotonPresionadoNO() //CUANDO TOCA BOTON NO - EN LA VENTANA EMERGENTE
{
    // Escribe aquí el código que se debe ejecutar cuando se hace clic en el botón.
    //ui->stackedWidget->setCurrentIndex(1);
    //ui->label_2->setText("NO ESTOY Viajando a Estacion " + estacion);
}


void MainWindow::on_BotonEst3_pressed()
{
    estacion = "3";
    mostrarConfirmacionEnvio();
}


void MainWindow::on_pushButton_13_pressed()
{
    estacion = "4";
    mostrarConfirmacionEnvio();
}


void MainWindow::on_pushButton_10_pressed()
{
    estacion = "5";
    mostrarConfirmacionEnvio();
}


void MainWindow::on_pushButton_12_pressed()
{
    estacion = "6";
    mostrarConfirmacionEnvio();
}


void MainWindow::on_pushButton_14_pressed()
{
    estacion = "7";
    mostrarConfirmacionEnvio();
}


void MainWindow::on_pushButton_pressed()
{
    ui->stackedWidget->setCurrentIndex(0);

}

void MainWindow::on_pushButton_2_pressed()
{
   ui->stackedWidget->setCurrentIndex(2);
}


void MainWindow::on_BotonVuelta_pressed()
{
   ui->stackedWidget->setCurrentIndex(1);
   ui->label_2->setText("Volviendo a Estacion 1");
}



