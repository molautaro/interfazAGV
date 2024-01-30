#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "login.h"
#include <QDateTime>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include "ultrasonicsensor.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

typedef struct {
    uint8_t *buf;
    uint8_t iW;
    uint8_t iR;
    uint8_t header;
    uint16_t timeout;
    uint8_t nBytes;
    uint8_t iData;
    uint8_t cks;
}__attribute__((packed, aligned(1))) _rx;

typedef struct {
    uint8_t *buf;
    uint8_t iW;
    uint8_t iR;
    uint8_t cks;
}__attribute__((packed, aligned(1))) _tx;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:
    void startMeasurement();

public slots: // Agrega esta sección
    void manejarBotonPresionadoSI();
    void manejarBotonPresionadoNO();
    void handleUserLoggedIn(User* user);
    void updateDistance(double distance); // Asegúrate de que acepta un parámetro double




private slots:

    void on_BotonEst2_released();

    void on_BotonEst3_released();

    void on_BotonEst4_released();

    void on_BotonEst5_released();

    void on_BotonEst6_released();

    void on_BotonEst7_released();

    void on_pushButton_released();

    void on_pushButton_2_released();

    void on_BotonVuelta_released();

    void mostrarConfirmacionEnvio();

    void mostrarLogin();

    void on_BotonVerEst_released();

    void on_BotonVolvInicSens_released();

    void on_BotonVerSens_released();

    void on_BotonSalirEst_released();

    void on_spinBox_valueChanged(int arg1);

    void on_pushButton_3_pressed();

    bool checkPermission(const QString &action);

    void on_BotonLOGIN_pressed();

    void on_botonREGISTRAR_released();

    void on_botonREGISTRO_released();

    void on_botonSalirReg_released();

    void CerrarSesionInactividad();

    bool eventFilter(QObject *obj, QEvent *event);

    void actualizarLastInteractionTime();

    void OnQSerialPort1Rx();

    void EnviarComando(uint8_t length, uint8_t cmd, uint8_t payload[]);

    void Decode();

    void CheckChecksumAndReceiveData();
    void UpdateChecksum();
    void CheckBytesLeft();
    void RecibirDatos(uint8_t head);

    void on_pushButton_4_pressed();

private:



    Ui::MainWindow *ui;
    //void updateDistance();
    QDateTime lastInteractionTime;
    QTimer *logoutTimer, *decodeTimer, *updateTimer;
    login *loginVentanaEmergente;
    User *user1 = new User("user", "user");
    User *usergenerico = new User("user", "user");
    UltrasonicSensor *sensor;
    QThread* sensorThread;
    QSerialPort* serial;
    QString estacion;
    uint8_t TX[256], payload[8],RX[256],indiceRX_r=0,indiceRX_t=0;
    volatile _rx ringRx;
    volatile _tx ringTx;
    bool iniciosesion=0;
    #define pantallaInicial 0
    #define pantallaSelecEst 1
    #define pantallaSens 2
    #define pantallaViaje 4
    #define pantallaDest 5
    #define pantallaReg 3



    // Define las constantes para los comandos
    #define CMD_LED_ON_OFF 0xC0
    #define CMD_WALL_BOUNCE 0xC1
    #define CMD_ALIVE 0xD2
    #define CMD_SENSORS 0xA0
    #define CMD_MAG_SENSOR 0xA1
    #define CMD_RFID_SENSOR 0xA2
    #define CMD_EMERGENCY_STOP 0xB0

    // Define un tamaño máximo para el buffer TX
    const int MAX_TX_SIZE = 256; // Ajusta el tamaño según tus necesidades

};
#endif // MAINWINDOW_H
