#ifndef INITWINDOW_H
#define INITWINDOW_H

#include <QDialog>
#include <QSerialPort>

#include "myserialport.h"

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
    void TimeoutResponseStm();

private:
    Ui::InitWindow *ui;
    MySerialPort* SerialPort;
    QTimer* TimerResponseStm;   // время ожидания ответа от stm32

    void SetupInitWindow();
};

#endif // INITWINDOW_H
