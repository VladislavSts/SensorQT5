# SensorQT5

Qt5 Sensor and Windows aplication

# Introduction

Программа реализует взаимодействие через последовательный порт
с микроконтроллером stm32, к которому подключен датчик MPU6050.
При старте отсылает запрос на старт в последовательный порт,
и как только пришел ответ о готовности датчика к работе,
пользователю предложено получить данные.
Сохранение полученных через последовательный порт данных
происходит автоматически. По завершении работы пользователь
может обратиться к документу output.txt для дальнейшей работы
с полученными данными.

# Help Info

Данные в текстовый файл записываются в следующем формате:

Дата эксперимента: 24.10.2023 17:25:07

time;   Accel_x;    Accel_y;    Accel_z;    Gyro_x;     Gyro_y;     Gyro_z;     Temperature

0.000;  1.0183;     -0.0298;    0.2056;     -4.4427;    0.8702;     -0.9160;    28.6712;

0.032;  1.0154;     -0.0337;    0.2065;     -4.2519;    1.0763;     -0.8092;    28.6712;

0.063;  1.0134;     -0.0320;    0.1982;     -4.3206;    1.0382;     -0.7099;    28.6712;

0.096;  1.0166;     -0.0303;    0.2009;     -4.2672;    1.0916;     -0.8550;    28.6712;

0.127;  1.0159;     -0.0315;    0.2041;     -4.2595;    0.9695;     -0.7481;    28.6712;

0.160;  1.0149;     -0.0229;    0.1995;     -4.1985;    1.0916;     -0.8550;    28.6712;

0.191;  1.0168;     -0.0325;    0.2048;     -4.3435;    0.8397;     -0.9008;    28.6712;

0.224;  1.0154;     -0.0273;    0.2095;     -4.0076;    0.9389;     -0.8855;    28.6712;

В качестве разделителя используются ";".

Запуск приложения возможен вне среды разработки Qt. Для этого необходимо 
скачать папку release и запустить SensorTSUTula_rev_1_0.exe. Текстовый файл
с полученными данными будет сохраняться в корень папки release.


(с) Designed by Vladislav
