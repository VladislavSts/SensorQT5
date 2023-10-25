/********************************************************************************
** Form generated from reading UI file 'InitWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INITWINDOW_H
#define UI_INITWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_InitWindow
{
public:
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayout;
    QLineEdit *GetNameSerialPort;
    QPushButton *SetNameSerialPort;
    QGridLayout *gridLayout_2;
    QPushButton *StartSensorButton;
    QLabel *StatusSensorLabel;

    void setupUi(QDialog *InitWindow)
    {
        if (InitWindow->objectName().isEmpty())
            InitWindow->setObjectName(QString::fromUtf8("InitWindow"));
        InitWindow->resize(457, 391);
        verticalLayout = new QVBoxLayout(InitWindow);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        GetNameSerialPort = new QLineEdit(InitWindow);
        GetNameSerialPort->setObjectName(QString::fromUtf8("GetNameSerialPort"));
        QFont font;
        font.setPointSize(12);
        font.setItalic(true);
        GetNameSerialPort->setFont(font);

        gridLayout->addWidget(GetNameSerialPort, 1, 0, 1, 1);

        SetNameSerialPort = new QPushButton(InitWindow);
        SetNameSerialPort->setObjectName(QString::fromUtf8("SetNameSerialPort"));
        SetNameSerialPort->setFont(font);

        gridLayout->addWidget(SetNameSerialPort, 2, 0, 1, 1);


        verticalLayout->addLayout(gridLayout);

        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        StartSensorButton = new QPushButton(InitWindow);
        StartSensorButton->setObjectName(QString::fromUtf8("StartSensorButton"));
        QFont font1;
        font1.setPointSize(14);
        font1.setItalic(true);
        StartSensorButton->setFont(font1);

        gridLayout_2->addWidget(StartSensorButton, 1, 0, 1, 1);

        StatusSensorLabel = new QLabel(InitWindow);
        StatusSensorLabel->setObjectName(QString::fromUtf8("StatusSensorLabel"));
        StatusSensorLabel->setFont(font1);
        StatusSensorLabel->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(StatusSensorLabel, 0, 0, 1, 1);


        verticalLayout->addLayout(gridLayout_2);


        retranslateUi(InitWindow);

        QMetaObject::connectSlotsByName(InitWindow);
    } // setupUi

    void retranslateUi(QDialog *InitWindow)
    {
        InitWindow->setWindowTitle(QCoreApplication::translate("InitWindow", "Dialog", nullptr));
        GetNameSerialPort->setText(QCoreApplication::translate("InitWindow", "\320\243\321\201\321\202\320\260\320\275\320\276\320\262\320\270\321\202\320\265 \320\270\320\274\321\217 COM \320\277\320\276\321\200\321\202\320\260", nullptr));
        SetNameSerialPort->setText(QCoreApplication::translate("InitWindow", "\320\243\321\201\321\202\320\260\320\275\320\276\320\262\320\270\321\202\321\214 \320\270\320\274\321\217", nullptr));
        StartSensorButton->setText(QCoreApplication::translate("InitWindow", "\n"
"\320\227\320\260\320\277\321\203\321\201\321\202\320\270\321\202\321\214 \n"
"\320\264\320\260\321\202\321\207\320\270\320\272\n"
"", nullptr));
        StatusSensorLabel->setText(QCoreApplication::translate("InitWindow", "<html><head/><body><p align=\"center\"><br/></p><p align=\"center\"><br/></p><p align=\"center\"><br/></p></body></html>", nullptr));
    } // retranslateUi

};

namespace Ui {
    class InitWindow: public Ui_InitWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INITWINDOW_H
