#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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

    void on_BotonVerEst_released();

    void on_BotonVolvInicSens_released();

    void on_BotonVerSens_released();

    void on_BotonSalirEst_released();

private:
    Ui::MainWindow *ui;

    QString estacion;

    #define pantallaInicial 0
    #define pantallaSelecEst 1
    #define pantallaSens 2
    #define pantallaViaje 3
    #define pantallaDest 4
};
#endif // MAINWINDOW_H
