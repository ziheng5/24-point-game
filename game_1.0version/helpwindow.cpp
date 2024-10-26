#include "helpwindow.h"
#include "ui_helpwindow.h"

helpwindow::helpwindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::helpwindow)
{
    ui->setupUi(this);
}

helpwindow::~helpwindow()
{
    delete ui;
}
