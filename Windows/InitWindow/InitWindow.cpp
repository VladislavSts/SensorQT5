#include "InitWindow.h"
#include "ui_SecWindow.h"
#include <QDebug>
#include <QTimer>
#include <QMessageBox>
#include <QCloseEvent>
#include <QSerialPort>
#include <QDateTime>
#include <QTextStream>


//-----------------------------------------------------------------------------------------------------------------//
bool ConnectStm32 = false; // Флаг успешного соединения с Stm32

//-----------------------------------------------------------------------------------------------------------------//
InitWindow::InitWindow(QWidget *parent) :
    QDialog(parent), ui(new Ui::InitWindow), SerialPort(new MySerialPort), TimerResponseStm(new QTimer)
{
    ui->setupUi(this);
    File = new QFile("output.txt");
    // Задаем интервал таймера в миллисекундах
    Timer.setInterval(1); // 1 мс
    Timer.stop();
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
    QTextStream OutStream(File);
    QString dateTime;

    while (SerialPort->waitForReadyRead(3)) {
        // TODO На больших скоростях опроса не вывозит, надо пофиксить
        data.append(SerialPort->readAll());
   }

   // Игнорировать пустые строки или строки, состоящие только из символа \r
    if (data.isEmpty() || data == "\r" || data == "" || data == "\n") {   
        return;
    }

    // Открытие файла
    if (!File->open(QIODevice::ReadWrite | QIODevice::Text | QIODevice::Append)) {
        qDebug() << "Cannot open file for writing: " << File->fileName();
        return;
    }

    // Отладка
    QString message = QString(data);  // Преобразование массива байт в строку
    qDebug() << "Received message: " << message;  // Вывод строки в консоль

    // stm32 готов к работе, получена строка подтверждения
    if (data.contains("stm32ready") && !ConnectStm32) {
        ConnectStm32 = true;
        ui->StatusSensorLabel->setText("Соединение установлено!");
        TimerResponseStm->stop();
        ui->StartSensorButton->setText("\nПолучить\nданные\n");
        disconnect(ui->StartSensorButton, &QPushButton::clicked, nullptr, nullptr);  // Отключаем старый слот
        connect(ui->StartSensorButton, &QPushButton::clicked, this, &InitWindow::on_GetDataButton_clicked);  // Подключаем новый слот

        QDateTime currentDateTime = QDateTime::currentDateTime();
        QString formattedDateTime = currentDateTime.toString("dd.MM.yyyy hh:mm:ss");
        qDebug() << "Текущая дата и время:" << formattedDateTime;

        dateTime = formattedDateTime + " -> Дата эксперимента\n";
        OutStream << dateTime;

        OutStream << "time\t\t" << "Accel_x\t\t" << "Accel_y\t\t" <<
                     "Accel_z\t\t" << "Gyro_x\t\t" << "Gyro_y\t\t" << "Gyro_z\t\t" << "Temperature\t\t";
        OutStream << Qt::endl;
    }
    else if (ConnectStm32) {
        /* Показать данные в label */
//        ui->StatusSensorLabel->setText(message);

        static bool FlagTimer = false; // Флаг запуска таймера только один раз
        if (FlagTimer == false) {
            elapsedTimer.start(); // Запускаем таймер
            FlagTimer = true;
        }

        // Получаем текущее значение таймера (время, прошедшее с момента последнего запуска)
        qint64 elapsedMilliseconds = elapsedTimer.elapsed();
        double elapsedSeconds = static_cast<double>(elapsedMilliseconds) / 1000.0;

        QString DataTime = QString("%1").arg(elapsedSeconds, 0, 'f', 3);

        // Разделяем строку на отдельные строки по символу ' ' (space)
        char Symbol = ' ';
        QList<QByteArray> List;
        List = data.split(Symbol);
        static float floatValue;

        DataTime = DataTime.leftJustified(15, ' '); // Выравнивание по левому краю
        DataTime += " ";

        OutStream << DataTime; // время в мсек

        // Проходим по каждой строке
        for (const QString line : List) {
            // Ищем позицию двоеточия в строке
            int colonIndex = line.indexOf(":");
            if (colonIndex != -1) {
                // Извлекаем имя параметра и значение
                QString paramName = line.mid(0, colonIndex).trimmed();
                QString paramValue = line.mid(colonIndex + 1).trimmed();
                floatValue = paramValue.toFloat();

                qDebug() << "Параметр:" << paramName;
                qDebug() << "Значение:" << floatValue;

                paramValue = paramValue.leftJustified(15, ' '); // Выравнивание по левому краю
                paramValue += " ";

                OutStream << paramValue;
            }
        }

        OutStream << Qt::endl;
    }

    File->close();
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
//#include "Graphic.h"
// Новый обработчик для кнопки "Получить данные"
void InitWindow::on_GetDataButton_clicked()
{
//    Graphic Graph;
//    Graph.setModal(true);
//    Graph.exec();

    // Код для получения данных
    ui->StatusSensorLabel->setText("Получение данных ...");
    ui->StartSensorButton->deleteLater();

    // Отправить команду в последовательный порт на получение данных
    SerialPort->write("getdata");
}


