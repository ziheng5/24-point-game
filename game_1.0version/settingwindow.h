#ifndef SETTINGWINDOW_H
#define SETTINGWINDOW_H

#include <QWidget>

namespace Ui {
class settingwindow;
}

class settingwindow : public QWidget
{
    Q_OBJECT

public:
    explicit settingwindow(QWidget *parent = nullptr);
    ~settingwindow();

private:
    Ui::settingwindow *ui;
};

#endif // SETTINGWINDOW_H
