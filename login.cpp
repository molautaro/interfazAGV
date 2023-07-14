#include "login.h"
#include "ui_login.h"
#include <qmessagebox.h>
#include <QFile>
#include <QTextStream>
#include <QCryptographicHash>
#include "user.h"



login::login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::login)
{
    ui->setupUi(this);
}

login::~login()
{
    delete ui;
}

void login::on_botonLOGIN_pressed()
{
    QString username = ui->lineUSER->text();
    QString password = ui->lineCONTRA->text();
    QString role;
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

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QTextStream in(&file);
    bool loginSuccessful = false;

    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList fields = line.split(" ");
        if (fields.size() < 3)
            continue;
        if (fields[0] == username && QByteArray::fromHex(fields[1].toUtf8()) == hashedPassword ) {
            loginSuccessful = true;
            role = fields[2];
            break;
        }
    }
    file.close();

    if (loginSuccessful) {
        ui->labelError_log->setText("Login exitoso");
        User *user = new User(username, role); // Asume que tienes el rol del usuario de alguna manera
        emit userLoggedIn(user); // Asume que has declarado esta señal en tu clase de login
    } else {
        ui->labelError_log->setText("Usuario o contraseña incorrecto");
        QMessageBox::warning(this, "Login", "Usuario o contraseña incorrecto");
    }
}



