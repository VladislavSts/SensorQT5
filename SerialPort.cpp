#include "SerialPort.h"

//-----------------------------------------------------------------------------------------------------------------//
/* Конфигурация по умолчанию */
void MySerialPort::Init() {
    setPortName("COM4");
    setBaudRate(QSerialPort::Baud9600);
    setDataBits(QSerialPort::Data8);
    setParity(QSerialPort::NoParity);
    setStopBits(QSerialPort::OneStop);
    setFlowControl(QSerialPort::NoFlowControl);
}
//-----------------------------------------------------------------------------------------------------------------//
void MySerialPort::ReInit(ConfigSerialPort* Config) {
    setPortName(Config->name);
    setBaudRate(Config->BaudRate);
    setDataBits(Config->DataBits);
    setParity(Config->Parity);
    setStopBits(Config->StopBits);
    setFlowControl(Config->FlowControl);
}

void MySerialPort::slot()
{

}
