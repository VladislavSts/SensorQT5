#ifndef MYSERIALPORT_H
#define MYSERIALPORT_H

#include <QSerialPort>
//-----------------------------------------------------------------------------------------------------------------//
struct ConfigSerialPort {
    const QString            &name;
    QSerialPort::BaudRate    BaudRate;
    QSerialPort::DataBits    DataBits;
    QSerialPort::Parity      Parity;
    QSerialPort::StopBits    StopBits;
    QSerialPort::FlowControl FlowControl;
};

//-----------------------------------------------------------------------------------------------------------------//
class MySerialPort : public QSerialPort
{
public:
    MySerialPort() : QSerialPort() {}; // Конструктор по умолчанию

    void Init();
    void ReInit(ConfigSerialPort* Config); // Возможно и не понадобится, но продумать стоит
};

#endif // MYSERIALPORT_H
