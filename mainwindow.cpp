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

void MainWindow::on_BotonEst2_released()
{
    estacion = "2";
    mostrarConfirmacionEnvio();

}

void MainWindow::manejarBotonPresionadoSI() //CUANDO TOCA BOTON SI - EN LA VENTANA EMERGENTE
{
    // Escribe aquí el código que se debe ejecutar cuando se hace clic en el botón.
    ui->stackedWidget->setCurrentIndex(pantallaViaje);
    ui->label_2->setText("Viajando a Estacion " + estacion);
}

void MainWindow::manejarBotonPresionadoNO() //CUANDO TOCA BOTON NO - EN LA VENTANA EMERGENTE
{
    // Escribe aquí el código que se debe ejecutar cuando se hace clic en el botón.
    //ui->stackedWidget->setCurrentIndex(1);
    //ui->label_2->setText("NO ESTOY Viajando a Estacion " + estacion);
}


void MainWindow::on_BotonEst3_released()
{
    estacion = "3";
    mostrarConfirmacionEnvio();
}


void MainWindow::on_BotonEst4_released()
{
    estacion = "4";
    mostrarConfirmacionEnvio();
}


void MainWindow::on_BotonEst5_released()
{
    estacion = "5";
    mostrarConfirmacionEnvio();
}


void MainWindow::on_BotonEst6_released()
{
    estacion = "6";
    mostrarConfirmacionEnvio();
}


void MainWindow::on_BotonEst7_released()
{
    estacion = "7";
    mostrarConfirmacionEnvio();
}


void MainWindow::on_pushButton_released()
{
    ui->stackedWidget->setCurrentIndex(pantallaSelecEst);

}

void MainWindow::on_pushButton_2_released()
{
   ui->stackedWidget->setCurrentIndex(pantallaDest);
}


void MainWindow::on_BotonVuelta_released()
{
   ui->stackedWidget->setCurrentIndex(pantallaSelecEst);
   ui->label_2->setText("Volviendo a Estacion 1");
}




void MainWindow::on_BotonVerEst_released()
{
    ui->stackedWidget->setCurrentIndex(pantallaSelecEst);
}


void MainWindow::on_BotonVolvInicSens_released()
{
    ui->stackedWidget->setCurrentIndex(pantallaInicial);
}


void MainWindow::on_BotonVerSens_released()
{
    ui->stackedWidget->setCurrentIndex(pantallaSens);
}


void MainWindow::on_BotonSalirEst_released()
{
    ui->stackedWidget->setCurrentIndex(pantallaInicial);
}

