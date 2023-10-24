#ifndef INITWINDOW_H
#define INITWINDOW_H

#include <QDialog>
#include <QSerialPort>
#include <QLabel>
#include "SerialPort.h"
#include <QFile>
#include <QTimer>
#include <QTime>
#include <QElapsedTimer>
#include <QTextStream>

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

signals:
    void DataIsReady();

private slots:
    void on_StartSensorButton_clicked();
    void on_GetDataButton_clicked();

    void CallbackSerialReceive();
    void TimeoutResponseStm();

    void on_SetNameSerialPort_clicked();

private:
    Ui::InitWindow *ui;
    MySerialPort* SerialPort;
    QTimer* TimerResponseStm;   // время ожидания ответа от stm32
    QFile* File;
    QElapsedTimer elapsedTimer;
    QByteArray data;

    void closeEvent(QCloseEvent* Event);
    void WriteDataToFile();
};

#endif // INITWINDOW_H
