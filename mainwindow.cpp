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
#include <QTimer>
#include <qmessagebox.h>
#include <QFile>
#include <QTextStream>
#include <QCryptographicHash>
#include <QCoreApplication>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    ringTx.buf=TX;
    ringRx.buf=RX;
    ringTx.iW=0;
    ringTx.iR=0;
    ringRx.iW=0;
    ringRx.iR=0;
    ringRx.header=0;


    serial = new QSerialPort(this);
        //serial->setPortName("COM4"); // Ajusta el nombre del puerto a tu puerto correcto.
        serial->setPortName("COM6");
        serial->setBaudRate(QSerialPort::Baud9600);
        serial->open(QSerialPort::ReadWrite);
        serial->setDataTerminalReady(true);
        connect(serial, &QSerialPort::readyRead, this, &MainWindow::OnQSerialPort1Rx);
    // Inicializar la variable lastInteractionTime
    lastInteractionTime = QDateTime::currentDateTime();
    // Conectar eventos de ratón y teclado a los métodos correspondientes
    installEventFilter(this);
    ui->graphicsView->viewport()->installEventFilter(this);
    ui->graphicsView->viewport()->setMouseTracking(true);


    logoutTimer = new QTimer(this);
    connect(logoutTimer, &QTimer::timeout, this, &MainWindow::CerrarSesionInactividad);
    //logoutTimer->start(180000); // 3 minutos (180000 milisegundos)
    logoutTimer->start(60000);

    decodeTimer = new QTimer(this);
    connect(decodeTimer, &QTimer::timeout, this, &MainWindow::Decode);
    //logoutTimer->start(180000); // 3 minutos (180000 milisegundos)
    decodeTimer->start(1);

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

void MainWindow::OnQSerialPort1Rx()
{
    QByteArray data = serial->readAll();
    if (data.isEmpty()) {
        return;
    }

    QString strhex;
    for (int i = 0; i < data.size(); i++)
        strhex = strhex + QString("%1").arg(static_cast<quint8>(data[i]), 2, 16, QChar('0')).toUpper();

    //strData = QString::fromLatin1(data);

    for (int i = 0; i < data.size(); i++)
        {
            ringRx.buf[ringRx.iW] = data[i];
            ringRx.iW++;
            //Decode();
        }

    ui->lineEdit->setText(strhex);
    //ui->label_21->setText(QString::fromLatin1(data));
}

void MainWindow::Decode(){
    if(ringRx.iW == ringRx.iR)
        return;

    switch (ringRx.header)
    {
        case 0:
            if (ringRx.buf[ringRx.iR] == 'U')
                ringRx.header++;
            else{
                ringRx.header = 0;
                //ringRx.iR--;
            }
            break;
        case 1:
            if (ringRx.buf[ringRx.iR] == 'N')
                ringRx.header++;
            else{
                ringRx.header = 0;
                //ringRx.iR--;
            }
            break;
        case 2:
            if (ringRx.buf[ringRx.iR] == 'E')
                ringRx.header++;
            else{
                ringRx.header = 0;
                //ringRx.iR--;
            }
            break;
        case 3:
            if (ringRx.buf[ringRx.iR] == 'R'){
                ringRx.header++;

            }
            else{
                ringRx.header = 0;
                //ringRx.iR--;
            }
            break;
        case 4:
            ringRx.nBytes = ringRx.buf[ringRx.iR];
            ringRx.header++;
            break;
        case 5:
            if (ringRx.buf[ringRx.iR] == 0x00)
                ringRx.header++;
            else{
                ringRx.header = 0;
                //ringRx.iR--;
            }
            break;
        case 6:
            if (ringRx.buf[ringRx.iR] == ':')
            {
                ringRx.cks= 'U'^'N'^'E'^'R'^ringRx.nBytes^0x00^':';
                ringRx.header++;
                ringRx.iData = ringRx.iR+1;
                //LED_RED_TOGGLE();
            }
            else{
                ringRx.header = 0;
                //ringRx.iR--;
            }
            break;

        case 7:
            UpdateChecksum();
            CheckBytesLeft();
            if(ringRx.nBytes == 0)
            {
            CheckChecksumAndReceiveData();
            }
            break;
        default:
            ringRx.header = 0;
            break;
    }
    ringRx.iR++;
}

void MainWindow::EnviarComando(uint8_t length, uint8_t cmd, uint8_t payload[])
{
    static uint8_t indTX = 0;
    // Comprobar el desbordamiento del buffer
    if (length + 6 > MAX_TX_SIZE)
    {
        // Manejar el error de desbordamiento
        // ...
        return;
    }

    TX[0] = 'U';
    TX[1] = 'N';
    TX[2] = 'E';
    TX[3] = 'R';
    TX[4] = length;
    TX[5] = 0x00;
    TX[6] = ':';

    switch (cmd)
    {
        case CMD_SENSORS:
            break;
        case CMD_ALIVE:
            TX[7] = CMD_ALIVE;
            break;
        default:
            // Manejar el error de comando no reconocido
            // ...
            return;
    }

    // Calcular el checksum
    uint8_t cks = 0;
    cks=0;

        for(int i=0; i<TX[4]+6; i++){
            cks ^= TX[i];
        }
        TX[TX[4]+6] = cks;

        if(serial->isOpen()){
            serial->write((char*)TX, 7 + TX[4]);
        }
}

void MainWindow::UpdateChecksum()
{
    if(ringRx.nBytes > 1)
    {
        ringRx.cks ^= ringRx.buf[ringRx.iR];
    }
}

void MainWindow::CheckBytesLeft()
{
    ringRx.nBytes--;
    if(ringRx.nBytes == 0)
    {
        ringRx.header = 0;
    }
}

void MainWindow::CheckChecksumAndReceiveData()
{
    if(ringRx.cks == ringRx.buf[ringRx.iR])
    {
        RecibirDatos(ringRx.iData);
    }
}

void MainWindow::RecibirDatos(uint8_t head){
    static uint8_t cont=0;
    cont++;
    switch (ringRx.buf[head++]){
        case CMD_ALIVE:
            ui->label_21->setText("tonto");

            ui->label_22->setNum(cont);
            //algo
        break;
        case CMD_SENSORS:
            //timeoutSENSORS = 4;
            //SENSORS_RECIVE = 1;

        break;
        default:
        break;
    }
}

bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{
    if (obj == this || obj == ui->graphicsView->viewport()) {
        if (event->type() == QEvent::KeyPress || event->type() == QEvent::MouseMove
            || event->type() == QEvent::MouseButtonPress || event->type() == QEvent::MouseButtonRelease) {
            // Actualizar la variable lastInteractionTime al tiempo actual
            lastInteractionTime = QDateTime::currentDateTime();
        }
    }

    // Delegar al evento original
    return QMainWindow::eventFilter(obj, event);
}

void MainWindow::actualizarLastInteractionTime()
{
    lastInteractionTime = QDateTime::currentDateTime();
}

void MainWindow::mostrarConfirmacionEnvio() {
    confirmacionEnvio* ventanaEmergente = new confirmacionEnvio(this);
    connect(ventanaEmergente, &confirmacionEnvio::botonPresionadoSI, this, &MainWindow::manejarBotonPresionadoSI);
    connect(ventanaEmergente, &confirmacionEnvio::botonPresionadoNO, this, &MainWindow::manejarBotonPresionadoNO);
    ventanaEmergente->setAttribute(Qt::WA_DeleteOnClose);
    connect(ventanaEmergente, &QDialog::finished, this, &MainWindow::actualizarLastInteractionTime);
    ventanaEmergente->setModal(true);
    ventanaEmergente->show();
}

void MainWindow::mostrarLogin(){
    loginVentanaEmergente = new login(this);
    connect(loginVentanaEmergente, &login::userLoggedIn, this, &MainWindow::handleUserLoggedIn);
    loginVentanaEmergente->setAttribute(Qt::WA_DeleteOnClose);
    connect(loginVentanaEmergente, &QDialog::finished, this, &MainWindow::actualizarLastInteractionTime);
    loginVentanaEmergente->setModal(true);
    loginVentanaEmergente->show();
}

void MainWindow::on_BotonEst2_released()
{
    estacion = "2";
    mostrarConfirmacionEnvio();

}

void MainWindow::handleUserLoggedIn(User* user)
{
    // Escribe aquí el código que se debe ejecutar cuando se hace clic en el botón.
    ui->label_11->setText(user->getUsername());
    ui->label_12->setText(user->getRole());
    user1=user;
    iniciosesion=1;
    logoutTimer->start(6000);
}

void MainWindow::CerrarSesionInactividad()
{

    int elapsedSeconds = lastInteractionTime.secsTo(QDateTime::currentDateTime());

    // Cerrar la sesión si ha pasado más de 3 minutos (180 segundos) de inactividad
    if (elapsedSeconds > 60) {
        // Escribe aquí el código para cerrar la sesión
        iniciosesion = 0;
        user1 = usergenerico;
        ui->stackedWidget->setCurrentIndex(pantallaInicial);
        ui->label_11->clear();
        ui->label_12->clear();
    }
    else{
        logoutTimer->start(3000);
    }


    //iniciosesion=0;
    //user1=usergenerico;
    //ui->stackedWidget->setCurrentIndex(pantallaInicial);
    //mostrarLogin();
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
        if(checkPermission("Elegir Estacion")){
            ui->stackedWidget->setCurrentIndex(pantallaSelecEst);
        }
    }else{
        mostrarLogin();
    }
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
            EnviarComando(0x02,CMD_SENSORS,payload);
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
            if (user1->getRole() == "Admin") {
                if (action == "Ver Sensores") {
                    return true;
                }
                if(action == "Elegir Estacion"){
                    return true;
                }
                if(action == "Registrar Usuario"){
                    return true;
                }
            }
            if (user1->getRole() == "User") {
                if(action == "Elegir Estacion"){
                    return true;
                }
            }
            return false;
        }


void MainWindow::on_BotonLOGIN_pressed()
{
    mostrarLogin();
}


void MainWindow::on_botonREGISTRAR_released()
{
    if(iniciosesion){
                if(checkPermission("Registrar Usuario")){
                    ui->stackedWidget->setCurrentIndex(pantallaReg);
                }
    }else{
                mostrarLogin();
    }
}


void MainWindow::on_botonREGISTRO_released()
{
    QString username = ui->lineUSER_REG->text();
    QString password = ui->lineCONTRA_REG->text();
    QString role = ui->comboBox->currentText(); //define el rol

    // Comprueba que el nombre de usuario y la contraseña no estén vacíos
    if (username.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "Registro", "El nombre de usuario y la contraseña no pueden estar vacíos");
        return;
    }

    // Genera el hash de la contraseña ingresada
    QByteArray passwordData = password.toUtf8();
    QByteArray hashedPassword = QCryptographicHash::hash(passwordData, QCryptographicHash::Sha256);

    // Abre el archivo de texto que contiene los usuarios
    QFile file("user_data.txt");
    if (!file.exists()) {
        // Si el archivo no existe, crea un nuevo archivo
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QMessageBox::critical(this, "Error", "No se pudo crear el archivo de datos de usuario");
            return;
        }
        file.close();
    }

    if (!file.open(QIODevice::Append | QIODevice::Text)) {
        QMessageBox::critical(this, "Error", "No se pudo abrir el archivo de datos de usuario para añadir un nuevo usuario");
        return;
    }

    // out << username: Escribe el nombre de usuario en el archivo de texto. out es un objeto QTextStream que se ha vinculado al archivo de texto.
    QTextStream out(&file);
    out << username << " " << hashedPassword.toHex() << " " << role << "\n";

    file.close();

    QMessageBox::information(this, "Registro", "Usuario registrado exitosamente");

    ui->lineUSER_REG->clear();
    ui->lineCONTRA_REG->clear();
}


void MainWindow::on_botonSalirReg_released()
{
    ui->stackedWidget->setCurrentIndex(pantallaInicial);
}


void MainWindow::on_pushButton_4_pressed()
{
    EnviarComando(0X02,CMD_ALIVE,payload);
}

