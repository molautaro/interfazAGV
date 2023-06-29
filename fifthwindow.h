#ifndef FIFTHWINDOW_H
#define FIFTHWINDOW_H

#include <QMainWindow>

namespace Ui {
class FifthWindow;
}

class FifthWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit FifthWindow(QWidget *parent = nullptr);
    ~FifthWindow();

private slots:
    void on_pushButton_clicked();

private:
    Ui::FifthWindow *ui;
};

#endif // FIFTHWINDOW_H
