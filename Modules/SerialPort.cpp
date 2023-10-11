#include "SerialPort.h"

//-----------------------------------------------------------------------------------------------------------------//
/* Конфигурация по умолчанию */
void MySerialPort::Init() {
    setPortName("COM15");
    setBaudRate(QSerialPort::Baud115200);
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
