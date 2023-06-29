#ifndef CONFIRMACIONENVIO_H
#define CONFIRMACIONENVIO_H

#include <QDialog>

namespace Ui {
class confirmacionEnvio;
}

class confirmacionEnvio : public QDialog
{
    Q_OBJECT

public:
    explicit confirmacionEnvio(QWidget *parent = nullptr);
    ~confirmacionEnvio();

signals: // Agrega esta sección
    void botonPresionadoSI();
    void botonPresionadoNO();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::confirmacionEnvio *ui;
};

#endif // CONFIRMACIONENVIO_H
