#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "initwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

 // Обработчик нажатия кнопки Start -> переход в новое окно
void MainWindow::on_StartButton_clicked()
{
    InitWindow Window;
    Window.setModal(true);
    Window.exec();

}


