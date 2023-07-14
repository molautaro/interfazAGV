#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "login.h"
#include <QDateTime>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots: // Agrega esta sección
    void manejarBotonPresionadoSI();
    void manejarBotonPresionadoNO();
    void handleUserLoggedIn(User* user);;


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

    void on_pushButton_4_pressed();

    void CerrarSesionInactividad();

    bool eventFilter(QObject *obj, QEvent *event);

    void actualizarLastInteractionTime();

    void on_pushButton_5_clicked();

private:
    Ui::MainWindow *ui;
    QDateTime lastInteractionTime;
    QTimer *logoutTimer;
    login *loginVentanaEmergente;
    User *user1 = new User("user", "user");
    User *usergenerico = new User("user", "user");
    QString estacion;
    bool iniciosesion=0;
    #define pantallaInicial 0
    #define pantallaSelecEst 1
    #define pantallaSens 2
    #define pantallaViaje 3
    #define pantallaDest 4
};
#endif // MAINWINDOW_H
