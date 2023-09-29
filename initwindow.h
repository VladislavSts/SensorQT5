#ifndef INITWINDOW_H
#define INITWINDOW_H

#include <QDialog>
#include <QSerialPort>

namespace Ui {
class InitWindow;
}

class InitWindow : public QDialog
{
    Q_OBJECT

public:
    explicit InitWindow(QWidget *parent = nullptr);
    ~InitWindow();

private slots:
    void on_RepConnectButton_clicked();
    void on_StartSensorButton_clicked();

    void CallbackSerialReceive();

private:
    Ui::InitWindow *ui;
    QSerialPort* SerialPort;
};

#endif // INITWINDOW_H
