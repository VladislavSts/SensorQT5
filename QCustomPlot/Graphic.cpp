#include "Graphic.h"
#include "ui_Graphic.h"

Graphic::Graphic(QWidget *parent) : QDialog(parent), ui(new Ui::Graphic)
{
    ui->setupUi(this);

    CustomPlot = new QCustomPlot();
    ui->gridLayout->addWidget(CustomPlot, 0, 0, 1, 1);
    // TODO Добавить

}

Graphic::~Graphic()
{
    delete ui;
}
