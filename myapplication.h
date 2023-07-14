#ifndef MYAPPLICATION_H
#define MYAPPLICATION_H

#include <QApplication>

class MyApplication : public QApplication
{
public:
    MyApplication(int &argc, char **argv);

    bool notify(QObject *receiver, QEvent *event) override;
};

#endif // MYAPPLICATION_H
