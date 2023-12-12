#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include "user.h"

namespace Ui {
class login;
}

class login : public QDialog
{
    Q_OBJECT

public:
    explicit login(QWidget *parent = nullptr);
    ~login();

signals: // Agrega esta sección
    void userLoggedIn(User *user);
    //void botonPresionadoNO();

private slots:
    void on_botonLOGIN_pressed();


    void on_BotonSalirEst_pressed();

private:
    Ui::login *ui;
};

#endif // LOGIN_H
