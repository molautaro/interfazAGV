#ifndef THIRDWINDOW_H
#define THIRDWINDOW_H

#include <QMainWindow>

namespace Ui {
class ThirdWindow;
}

class ThirdWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ThirdWindow(QWidget *parent = nullptr);
    ~ThirdWindow();

private slots:
    void on_pushButton_clicked();

private:
    Ui::ThirdWindow *ui;
};

#endif // THIRDWINDOW_H
