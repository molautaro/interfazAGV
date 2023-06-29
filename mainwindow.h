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
    void on_BotonEst2_pressed();

    void on_BotonEst3_pressed();

    void on_pushButton_13_pressed();

    void on_pushButton_10_pressed();

    void on_pushButton_12_pressed();

    void on_pushButton_14_pressed();

    void on_pushButton_pressed();

    void on_pushButton_2_pressed();

    void on_BotonVuelta_pressed();

    void mostrarConfirmacionEnvio();



private:
    Ui::MainWindow *ui;

    QString estacion;
};
#endif // MAINWINDOW_H
