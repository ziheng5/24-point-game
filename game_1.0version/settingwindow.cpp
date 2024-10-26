#include "settingwindow.h"
#include "ui_settingwindow.h"

settingwindow::settingwindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::settingwindow)
{
    ui->setupUi(this);
}

settingwindow::~settingwindow()
{
    delete ui;
}
