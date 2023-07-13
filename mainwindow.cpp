#include "mainwindow.h"
#include "confirmacionenvio.h"
#include "login.h"
#include "user.h"
#include "./ui_mainwindow.h"
#include <QGraphicsView>
#include <QGraphicsEllipseItem>
#include <QGraphicsLineItem>
#include <cmath>
#include <QVBoxLayout>
#include <QTime>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QTime time = QTime::currentTime();
    qsrand((uint)time.msec());

    // Acceder a la vista y la escena de la interfaz de usuario
    //QGraphicsViewview = ui->graphicsView;
    QGraphicsScene *scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);


    // Configurar vista
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);

    // Configurar escena
    scene->setSceneRect(-100, -100, 200, 200);
    //scene->setSceneRect(-ui->graphicsView->width()/2, -ui->graphicsView->height()/2, ui->graphicsView->width(), ui->graphicsView->height());

    // Crear puntos de datos (en coordenadas polares)
    QVector<QPointF> points;
    for (int i = 0; i < 10; ++i) {
        // Generar un radio y un ángulo aleatorios
        double radius = (qrand() % 100) / 100.0; // Número aleatorio entre 0 y 1
        double angle = (qrand() % 360) * M_PI / 180.0; // Ángulo aleatorio entre 0 y 2π radianes
        points << QPointF(radius * std::cos(angle), radius * std::sin(angle));
    }

    // Convertir puntos a coordenadas cartesianas y dibujar
    for (const QPointF &point : points) {
        qreal x = point.x() * (ui->graphicsView->width()/2);
        qreal y = -point.y() * (ui->graphicsView->height()/2);
        //scene->addEllipse(x - 2, y - 2, 4, 4, QPen(), QBrush(Qt::SolidPattern));
        scene->addEllipse(x, y, 7, 7, QPen(), QBrush(Qt::red,Qt::SolidPattern));
    }

    // Dibujar lineas de referencia
    for (int i = 0; i < 360; i += 45) {
        qreal x = std::cos(i * M_PI / 180.0) * (ui->graphicsView->width());
        qreal y = -std::sin(i * M_PI / 180.0) * (ui->graphicsView->height());
        scene->addLine(0, 0, x, y);
    }
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

void MainWindow::mostrarLogin(){
    loginVentanaEmergente = new login(this);
    connect(loginVentanaEmergente, &login::userLoggedIn, this, &MainWindow::handleUserLoggedIn);
    loginVentanaEmergente->setAttribute(Qt::WA_DeleteOnClose);
    loginVentanaEmergente->setModal(true);
    loginVentanaEmergente->show();
}

void MainWindow::on_BotonEst2_released()
{
    estacion = "2";
    mostrarConfirmacionEnvio();

}

void MainWindow::handleUserLoggedIn(User* user) //CUANDO TOCA BOTON SI - EN LA VENTANA EMERGENTE
{
    // Escribe aquí el código que se debe ejecutar cuando se hace clic en el botón.
    ui->label_11->setText(user->getUsername());
    ui->label_12->setText(user->getRole());
    user1=user;
    iniciosesion=1;

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
   ui->stackedWidget->setCurrentIndex(pantallaViaje);
   ui->label_2->setText("Volviendo a Estacion 1");
}




void MainWindow::on_BotonVerEst_released()
{
    if(iniciosesion){
        ui->stackedWidget->setCurrentIndex(pantallaSelecEst);
    }

    mostrarLogin();
}


void MainWindow::on_BotonVolvInicSens_released()
{
    ui->stackedWidget->setCurrentIndex(pantallaInicial);
}


void MainWindow::on_BotonVerSens_released()
{
    if(iniciosesion){
        if(checkPermission("Ver Sensores")){
            ui->stackedWidget->setCurrentIndex(pantallaSens);
        }
    }else{
        mostrarLogin();
    }

}


void MainWindow::on_BotonSalirEst_released()
{
    ui->stackedWidget->setCurrentIndex(pantallaInicial);
}


void MainWindow::on_spinBox_valueChanged(int arg1)
{
    ui->barraIZQ->setValue(arg1);
}


void MainWindow::on_pushButton_3_pressed()
{
    ui->codRFID->setPlainText("XD");
}

bool MainWindow::checkPermission(const QString &action) {
            if (user1->getUsername() == "admin") {
                if (action == "Ver Sensores") {
                    return true;
                }
            }
            return false;
        }


void MainWindow::on_pushButton_4_pressed()
{
    mostrarLogin();
}

