#include "InitWindow.h"
#include "ui_SecWindow.h"
#include <QDebug>
#include <QTimer>
#include <QMessageBox>
#include <QCloseEvent>
#include <QSerialPort>

//-----------------------------------------------------------------------------------------------------------------//
bool ConnectStm32 = false; // Флаг успешного соединения с Stm32

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
        TimerResponseStm->start(_sec(10));  // 10 секунд
    }
    else {
        ui->StatusSensorLabel->setText("Не удалось открыть порт " + SerialPort->portName());
    }
}

//-----------------------------------------------------------------------------------------------------------------//
/* Callback функция, вызывается при появлении новых данных для чтения */
void InitWindow::CallbackSerialReceive()
{
    static QByteArray data; // = SerialPort->readAll();

    while (SerialPort->waitForReadyRead(10)) {
        data.append(SerialPort->readAll());
    }

    if (data.isEmpty() || data == "\r" || data == "" || data == "\n") {
        // Игнорировать пустые строки или строки, состоящие только из символа \r
        return;
    }

    // Отладка
    QString message = QString(data);  // Преобразование массива байт в строку
    qDebug() << "Received message: " << message;  // Вывод строки в консоль

    if (data.contains("stm32ready") && !ConnectStm32) {
        ConnectStm32 = true;
        ui->StatusSensorLabel->setText("Соединение установлено!");
        TimerResponseStm->stop();
        ui->StartSensorButton->setText("\nПолучить\nданные\n");
        disconnect(ui->StartSensorButton, &QPushButton::clicked, nullptr, nullptr);  // Отключаем старый слот
        connect(ui->StartSensorButton, &QPushButton::clicked, this, &InitWindow::on_GetDataButton_clicked);  // Подключаем новый слот
    }
    else if (ConnectStm32) {
        ui->StatusSensorLabel->setText(message);
    }

    data.clear();
}

//-----------------------------------------------------------------------------------------------------------------//
/* Обработчик события сигнала timeour таймера */
void InitWindow::TimeoutResponseStm()
{
    // Время ожидания истекло, выводим ошибку
    qDebug() << "Stm32 не отвечает!";
    ui->StatusSensorLabel->setText("Stm32 не отвечает!");
    ui->StartSensorButton->setText("\nПовторить\nсоединение\n");
}

//-----------------------------------------------------------------------------------------------------------------//
/* Переопределение метода закрытия окна */
void InitWindow::closeEvent(QCloseEvent *Event)
{
    SerialPort->write("stopdata");

    QMessageBox::StandardButton StateButton =
        QMessageBox::question( this, "Завершение сеанса", tr("Вы действительно хотите завершить сеанс?\n"),
            QMessageBox::No | QMessageBox::Yes, QMessageBox::No);

    if (StateButton != QMessageBox::Yes) {
        Event->ignore();
        SerialPort->write("getdata");
    }
    else {
        Event->accept();       
        qApp->quit(); // Закрыть приложение целиком
    }
}

//-----------------------------------------------------------------------------------------------------------------//
/* Установка пользовательских настроек окна InitWindow (+ настройки последовательного порта) */
void InitWindow::SetupInitWindow()
{
    setWindowTitle("Connect Sensor");
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint); // отключить знак "?"

    // Установка размера буфера чтения на достаточно большое значение
    SerialPort->setReadBufferSize(4096); // Здесь 4096 - это размер буфера
    // Подключаем сигналы и слоты для SerialPort
    connect(SerialPort, &MySerialPort::readyRead, this, &InitWindow::CallbackSerialReceive);
    SerialPort->Init();

    // Подключаем сигналы и слоты для Timer
    connect(TimerResponseStm, &QTimer::timeout, this, &InitWindow::TimeoutResponseStm);
}

//-----------------------------------------------------------------------------------------------------------------//
// Новый обработчик для кнопки "Получить данные"
void InitWindow::on_GetDataButton_clicked()
{
    // Код для получения данных
    ui->StatusSensorLabel->setText("Получение данных ...");
    ui->StartSensorButton->deleteLater();

    // Отправить команду в последовательный порт на получение данных
    SerialPort->write("getdata");
}


