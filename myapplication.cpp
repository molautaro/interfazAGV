#include "myapplication.h"
#include <QEvent>
#include <QDateTime>

MyApplication::MyApplication(int &argc, char **argv)
    : QApplication(argc, argv)
{
}

bool MyApplication::notify(QObject *receiver, QEvent *event)
{
    // Actualizar la variable lastInteractionTime al tiempo actual para cualquier evento en la aplicación
    static QDateTime lastInteractionTime = QDateTime::currentDateTime();
    lastInteractionTime = QDateTime::currentDateTime();

    // Delegar al método notify() de la clase base
    return QApplication::notify(receiver, event);
}
