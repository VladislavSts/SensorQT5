#include "initwindow.h"
#include "ui_initwindow.h"
#include <QDebug>

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
    SerialPort->setBaudRate(QSerialPort::Baud115200);
    SerialPort->setDataBits(QSerialPort::Data8);
    SerialPort->setParity(QSerialPort::NoParity);
    SerialPort->setStopBits(QSerialPort::OneStop);
    SerialPort->setFlowControl(QSerialPort::NoFlowControl);
    SerialPort->open(QIODevice::ReadWrite); // открыть последовательный порт

    connect(SerialPort, SIGNAL(readyRead()), this, SLOT(SerialReceive()));
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
    SerialPort->write("Hello!");
}



void InitWindow::SerialReceive()
{
    QByteArray data = SerialPort->readAll();  // Чтение доступных данных из порта
    QString message = QString(data);  // Преобразование массива байт в строку

    // Обработка строки message
    ui->StatusSensorLabel->setText(data);

    // Пример: вывод строки в консоль
    qDebug() << "Received message: " << message;
}

void InitWindow::on_RepConnectButton_clicked()
{
    ui->StatusSensorLabel->setText("Повторное соединение ...");
    // Repeat connecting to sensor ...
}




