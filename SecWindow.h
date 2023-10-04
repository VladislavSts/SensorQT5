#ifndef SECWINDOW_H
#define SECWINDOW_H

#include <QDialog>
#include <QSerialPort>
#include "SerialPort.h"

#define _msec(X) (X)
#define _sec(X)  (X*1000)

namespace Ui {
class InitWindow;
}

class InitWindow : public QDialog
{
    Q_OBJECT

public:
    explicit InitWindow(QWidget *parent = nullptr);
    ~InitWindow();

    void SetupInitWindow();

private slots:
    void on_RepConnectButton_clicked();
    void on_StartSensorButton_clicked();
    void on_GetDataButton_clicked();

    void CallbackSerialReceive();
    void TimeoutResponseStm();

private:
    Ui::InitWindow *ui;
    MySerialPort* SerialPort;
    QTimer* TimerResponseStm;   // время ожидания ответа от stm32


};

#endif // SECWINDOW_H
