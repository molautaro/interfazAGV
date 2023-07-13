#include "login.h"
#include "ui_login.h"
#include <qmessagebox.h>
#include <QFile>
#include <QTextStream>
#include <QCryptographicHash>
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
        if (fields.size() < 2)
            continue;
        if (fields[0] == username && QByteArray::fromHex(fields[1].toUtf8()) == hashedPassword) {
            loginSuccessful = true;
            break;
        }
    }
    file.close();

    if (loginSuccessful) {
        ui->labelError_log->setText("Login exitoso");
    } else {
        ui->labelError_log->setText("Usuario o contraseña incorrecto");
        QMessageBox::warning(this, "Login", "Usuario o contraseña incorrecto");
    }
}


void login::on_botonREGISTRO_pressed()
{
    QString username = ui->lineUSER->text();
    QString password = ui->lineCONTRA->text();

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
    out << username << " " << hashedPassword.toHex() << "\n";

    file.close();

    QMessageBox::information(this, "Registro", "Usuario registrado exitosamente");
}

