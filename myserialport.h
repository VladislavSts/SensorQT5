#ifndef MYSERIALPORT_H
#define MYSERIALPORT_H

#include <QSerialPort>

class MySerialPort : public QSerialPort
{
public:
    MySerialPort() : QSerialPort() {} // Конструктор по умолчанию

    /* Конфигурация по умолчанию */
    void Init() {
        setPortName("COM4");
        setBaudRate(QSerialPort::Baud9600);
        setDataBits(QSerialPort::Data8);
        setParity(QSerialPort::NoParity);
        setStopBits(QSerialPort::OneStop);
        setFlowControl(QSerialPort::NoFlowControl);
    }

    void ReInit() {

    }
};

#endif // MYSERIALPORT_H
