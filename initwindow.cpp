#include "initwindow.h"
#include "ui_initwindow.h"
#include <QDebug>
#include <qthread.h>

InitWindow::InitWindow(QWidget *parent) : QDialog(parent), ui(new Ui::InitWindow), SerialPort(new QSerialPort)
{
    ui->setupUi(this);

    setWindowTitle("Connect Sensor");
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);

    // Конфигурация StatusLabel
    ui->StatusSensorLabel->setAlignment(Qt::AlignHCenter); // Установка выравнивания по центру
    QFont font;
    font.setPointSize(14); // Установка курсивного шрифта размером 14
    font.setItalic(true);
    ui->StatusSensorLabel->setFont(font);

    // Конфигурация последовательного порта
    SerialPort->setPortName("COM4");
    SerialPort->setBaudRate(QSerialPort::Baud9600);
    SerialPort->setDataBits(QSerialPort::Data8);
    SerialPort->setParity(QSerialPort::NoParity);
    SerialPort->setStopBits(QSerialPort::OneStop);
    SerialPort->setFlowControl(QSerialPort::NoFlowControl);
}

InitWindow::~InitWindow()
{
    delete ui;
    SerialPort->close();
    delete SerialPort;
}

void InitWindow::on_StartSensorButton_clicked()
{
    ui->StatusSensorLabel->setText("Соединение с датчиком ...");
    // Connecting to sensor ...
    SerialPort->open(QIODevice::ReadWrite); // открыть последовательный порт
    connect(SerialPort, SIGNAL(readyRead()), this, SLOT(CallbackSerialReceive()));
    SerialPort->write("Hello!");
}

void InitWindow::CallbackSerialReceive()
{
    QByteArray data = SerialPort->readAll();  // Чтение доступных данных из порта

    if (data.isEmpty() || data == "\r") {
        // Игнорировать пустые строки или строки, состоящие только из символа \r
        return;
    }

    // Обработка строки message
    ui->StatusSensorLabel->setText(data);

    // Вывод строки в консоль
    QString message = QString(data);  // Преобразование массива байт в строку
    qDebug() << "Received message: " << message;
}

void InitWindow::on_RepConnectButton_clicked()
{
    ui->StatusSensorLabel->setText("Повторное соединение ...");
    // Repeat connecting to sensor ...
}




