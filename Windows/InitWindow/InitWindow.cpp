#include "ui_InitWindow.h""
#include "InitWindow.h"
#include <QDebug>
#include <QTimer>
#include <QMessageBox>
#include <QCloseEvent>
#include <QSerialPort>
#include <QDateTime>
#include <QTextStream>
#include <QRegularExpression>


//-----------------------------------------------------------------------------------------------------------------//

bool ConnectStm32 = false; // Флаг успешного соединения с Stm32

//-----------------------------------------------------------------------------------------------------------------//

InitWindow::InitWindow(QWidget *parent) :
    QDialog(parent), ui(new Ui::InitWindow), SerialPort(new MySerialPort), TimerResponseStm(new QTimer)
{
    ui->setupUi(this);
    File = new QFile("output.txt");
    ui->StartSensorButton->hide();
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
        TimerResponseStm->start(_sec(3));  // 3 секунды
    }
    else {
        ui->StatusSensorLabel->setText("Не удалось открыть порт " + SerialPort->portName());
    }
}
//-----------------------------------------------------------------------------------------------------------------//

/* Обработчик события сигнала timeour таймера */
void InitWindow::TimeoutResponseStm()
{
    // Время ожидания истекло, выводим ошибку
    ui->StatusSensorLabel->setText("Датчик не отвечает!");
    ui->StartSensorButton->setText("\nПовторить\nсоединение\n");
}

//-----------------------------------------------------------------------------------------------------------------//

/* Callback функция, вызывается при появлении новых данных для чтения */
void InitWindow::CallbackSerialReceive()
{
    data.append(SerialPort->readAll());

    // Принимать данные пока не встретится конец строки '\n' и игнорировать пустые строки
    if (!data.contains("\r\n") || data.isEmpty() || data == "") {
        return;
    }

    // Отладка
    QString message = QString(data);  // Преобразование массива байт в строку
    qDebug() << "Received message: " << message;  // Вывод строки в консоль

    emit DataIsReady(); // сгенерировать сигнал о готовности данных к обработке
}

//-----------------------------------------------------------------------------------------------------------------//

/* Метод, реализующий парсинг значений из полученной строки от stm и записывает эти значения в файл по столбцам с разделителем ";" */
void InitWindow::WriteDataToFile()
{
    QTextStream OutStream(File);
    QString dateTime;

    /* Датчик готов к работе, получена строка подтверждения */
    if (data.contains("stm32ready") && !ConnectStm32) {
        ConnectStm32 = true;
        ui->StatusSensorLabel->setText("Соединение установлено!");
        TimerResponseStm->stop();
        ui->StartSensorButton->setText("\nПолучить\nданные\n");
        disconnect(ui->StartSensorButton, &QPushButton::clicked, nullptr, nullptr);  // Отключаем старый слот
        connect(ui->StartSensorButton, &QPushButton::clicked, this, &InitWindow::on_GetDataButton_clicked);  // Подключаем новый слот

        // Первое включение - начало эксперимента, файл нужно перетереть
        if (!File->open(QIODevice::ReadWrite | QIODevice::Truncate)) {
            qDebug() << "Cannot open file for writing: " << File->fileName();
            return;
        }
        QByteArray emptyData;
        File->write(emptyData);

        QDateTime currentDateTime = QDateTime::currentDateTime();
        QString formattedDateTime = currentDateTime.toString("dd.MM.yyyy hh:mm:ss");
        qDebug() << "Текущая дата и время:" << formattedDateTime;
        dateTime = "Дата эксперимента: " + formattedDateTime;
        OutStream << dateTime << "\n";

        // Заголовок для записи данных
        OutStream << "time;" << "Accel_x;" << "Accel_y;" << "Accel_z;" << "Gyro_x;" << "Gyro_y;" << "Gyro_z;" << "Temperature";
        OutStream << Qt::endl;
    }
    else if (ConnectStm32) {
        /* Опрос датчика */
        static bool FlagTimer = false; // Флаг запуска таймера только один раз
        if (FlagTimer == false) {
            elapsedTimer.start(); // Запускаем таймер
            FlagTimer = true;
        }

        // Открыть файл в режиме дописывания данных
        if (!File->open(QIODevice::ReadWrite | QIODevice::Text | QIODevice::Append)) {
            qDebug() << "Cannot open file for writing: " << File->fileName();
            return;
        }

        // Получаем текущее значение таймера (время, прошедшее с момента последнего запуска)
        qint64 elapsedMilliseconds = elapsedTimer.elapsed();
        double elapsedSeconds = static_cast<double>(elapsedMilliseconds) / 1000.0;

        QString DataTime = QString("%1").arg(elapsedSeconds, 0, 'f', 3);
        DataTime += ";";
//      DataTime = DataTime.leftJustified(15, ' '); // Выравнивание по левому краю
//      DataTime += " ";

        OutStream << DataTime; // вывод времени в мсек

        // Извлечение значения для каждого параметра из списка значений
        // hard code :) зато молотит как часы
        QList<QByteArray> values = data.split(' ');
        static double accel_x, accel_y, accel_z, gyro_x, gyro_y, gyro_z, temperature;

        if (values.size() >= 7) {
            accel_x = values[0].mid(8).toDouble();   // Accel_x:
            accel_y = values[1].mid(8).toDouble();   // Accel_y:
            accel_z = values[2].mid(8).toDouble();   // Accel_z:
            gyro_x = values[3].mid(7).toDouble();    // Gyro_x:
            gyro_y = values[4].mid(7).toDouble();    // Gyro_y:
            gyro_z = values[5].mid(7).toDouble();    // Gyro_z:
            temperature = values[6].mid(12).toDouble(); // Temperature:
        }

        if (accel_x == 0 && accel_y == 0 && accel_z == 0) {
            ui->StatusSensorLabel->setText("Беда, датчик отвалился :(");
            OutStream << "Connection is failed! \n";
            ConnectStm32 = false;
        }
        else {
            if (accel_x <= 1.5 || accel_y <= 1.5 || accel_z <= 1.5 || temperature <= 50) {
                // Запись данных в файл в формате столбцов с разделителем ";"
                OutStream << QString::number(accel_x, 'f', 4)     << ";"    << QString::number(accel_y, 'f', 4) << ";";
                OutStream << QString::number(accel_z, 'f', 4)     << ";"    << QString::number(gyro_x, 'f', 4) << ";";
                OutStream << QString::number(gyro_y, 'f', 4)      << ";"    << QString::number(gyro_z, 'f', 4) << ";";
                OutStream << QString::number(temperature, 'f', 4) << ";"    << "\n";
            }
        }
    }
    File->close();
    data.clear();
}

//-----------------------------------------------------------------------------------------------------------------//

/* Переопределение метода закрытия окна */
void InitWindow::closeEvent(QCloseEvent *Event)
{
    SerialPort->write("stopdata");

    QMessageBox msgBox;
    msgBox.setWindowTitle("Завершение сеанса");
    msgBox.setText("Вы действительно хотите завершить сеанс?");
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msgBox.setDefaultButton(QMessageBox::No);

    int result = msgBox.exec();

    if (result != QMessageBox::Yes) {
        Event->ignore();
    }
    else {
        Event->accept();
        QCoreApplication::quit(); // Полностью приостановить работу программы
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

    // Подключить сигнал готовности данных к обработке
    connect(this, &InitWindow::DataIsReady, this, &InitWindow::WriteDataToFile);
}

//-----------------------------------------------------------------------------------------------------------------//

// Новый обработчик для кнопки "Получить данные"
void InitWindow::on_GetDataButton_clicked()
{
    /* Скрыть label и button при старте программы */
    ui->SetNameSerialPort->hide();
    ui->GetNameSerialPort->hide();

    // Код для получения данных
    ui->StatusSensorLabel->setText("Получение данных ...");
    ui->StartSensorButton->setText("Построить график\nпо полученным данным");

    disconnect(ui->StartSensorButton, &QPushButton::clicked, nullptr, nullptr);  // Отключаем старый слот
    connect(ui->StartSensorButton, &QPushButton::clicked, this, &InitWindow::PaintGraphic);  // Подключаем новый
//    ui->StartSensorButton->deleteLater();

    // Отправить команду в последовательный порт на получение данных
    SerialPort->write("getdata");
}

//-----------------------------------------------------------------------------------------------------------------//

void InitWindow::PaintGraphic()
{
    SerialPort->write("stopdata");
    ui->StatusSensorLabel->setText("Запутите скрипт python\nчтобы построить график :)");
}

//-----------------------------------------------------------------------------------------------------------------//

void InitWindow::on_SetNameSerialPort_clicked()
{
    QString PortName = ui->GetNameSerialPort->text();

    // Определение регулярного выражения
    QRegularExpression regex("^COM\\d+$");

    // Проверка строки на соответствие регулярному выражению
    if (regex.match(PortName).hasMatch()) {
        SerialPort->setPortName(PortName);
        ui->StatusSensorLabel->setText("Вы можете запустить датчик");
        ui->StartSensorButton->show();
    }
    else {
        ui->StatusSensorLabel->setText("Некорректное имя COM порта!");
    }
}

