#include "SecWindow.h"
#include "ui_initwindow.h"
#include <QDebug>
#include <QTimer>

//-----------------------------------------------------------------------------------------------------------------//
InitWindow::InitWindow(QWidget *parent) :
    QDialog(parent), ui(new Ui::InitWindow), SerialPort(new MySerialPort), TimerResponseStm(new QTimer)
{
        ui->setupUi(this);
}

//-----------------------------------------------------------------------------------------------------------------//
InitWindow::~InitWindow()
{
    delete ui;
    SerialPort->close();
    delete SerialPort;
    delete TimerResponseStm;
}

//-----------------------------------------------------------------------------------------------------------------//
/* Обработчик кнокпи запуска датчика */
void InitWindow::on_StartSensorButton_clicked()
{
    ui->StatusSensorLabel->setText("Соединение с датчиком ...");
    // Connecting to sensor ...
    if (SerialPort->open(QIODevice::ReadWrite) || SerialPort->isOpen()) {
        ui->StatusSensorLabel->setText("Порт " + SerialPort->portName() + " открыт! Соединение ...");
        SerialPort->write("start");

        // Запускаем таймер для ожидания ответа
        TimerResponseStm->setSingleShot(true);
        TimerResponseStm->start(10000);  // 10 секунд
    }
    else {
        ui->StatusSensorLabel->setText("Не удалось открыть порт " + SerialPort->portName());
    }
}

//-----------------------------------------------------------------------------------------------------------------//
/* Callback функция, вызывается при появлении новых данных для чтения */
void InitWindow::CallbackSerialReceive()
{
    QByteArray data = SerialPort->readAll();

    if (data.isEmpty() || data == "\r") {
        // Игнорировать пустые строки или строки, состоящие только из символа \r
        return;
    }

    if (data == "startsensor") {
        ui->StatusSensorLabel->setText("Соединение установлено!");
        TimerResponseStm->stop();
        // Нужно вычитывать данные от сенсора
        // Вопрос протокола обмена данными
    }

    QString message = QString(data);  // Преобразование массива байт в строку
    qDebug() << "Received message: " << message;  // Вывод строки в консоль
}

//-----------------------------------------------------------------------------------------------------------------//
/* Обработчик события сигнала timeour таймера */
void InitWindow::TimeoutResponseStm() {
    // Время ожидания истекло, выводим ошибку
    qDebug() << "Stm32 не отвечает!";
    ui->StatusSensorLabel->setText("Stm32 не отвечает!");
}

//-----------------------------------------------------------------------------------------------------------------//
/* Обработчик кноки повторного соединения */
void InitWindow::on_RepConnectButton_clicked()
{
    ui->StatusSensorLabel->setText("Повторное соединение ...");
    // Repeat connecting to sensor ...
}

//-----------------------------------------------------------------------------------------------------------------//
/* Установка пользовательских настроек окна InitWindow (+ настройки последовательного порта) */
void InitWindow::SetupInitWindow()
{
    setWindowTitle("Connect Sensor");
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint); // отключить знак "?"

    // Подключаем сигналы и слоты для SerialPort
    connect(SerialPort, &MySerialPort::readyRead, this, &InitWindow::CallbackSerialReceive);
    SerialPort->Init();

    // Подключаем сигналы и слоты для Timer
    connect(TimerResponseStm, &QTimer::timeout, this, &InitWindow::TimeoutResponseStm);
}



