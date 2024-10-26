#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "equation.h"
#include "timer.h"
#include "generate24.h"
#include <QPalette>
#include <QColor>
#include <QDebug>
#include <QPoint>
#include <QCursor>
#include <stdio.h>
#include <QPainter>
#include <QButtonGroup>
#include <QTimer>
#include <QGraphicsOpacityEffect>
#include <QFont>
#include <QSpacerItem>
#include <cstring>
#include <QIntValidator>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>
#include <QSequentialAnimationGroup>
#include <QGraphicsOpacityEffect>

MainWindow* instance;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), isDarkMode(false), ui(new Ui::MainWindow)
{
    //----------------------------------------------------------------------------------2024.10.14
    // 载入 .ui 文件
    ui->setupUi(this);
    instance = this;

    // 绑定信号和槽
    connect(this,SIGNAL(signal_data(QString)),this,SLOT(slot_ReceiveData(QString)));
    //----------------------------------------------------------------------------------

    initProperties();

    QPropertyAnimation* pScaleAnimation1 = new QPropertyAnimation(ui->scaleButton, "geometry");
    pScaleAnimation1->setDuration(1000);
    pScaleAnimation1->setStartValue(QRect(190, 500, 0, 0));//(起始横坐标，起始纵坐标，起始窗口长度，起始窗口宽度)
    pScaleAnimation1->setEndValue(QRect(120, 160, 140, 140));//(末尾横坐标，末尾纵坐标，末尾窗口长度，末尾窗口宽度)
    pScaleAnimation1->setEasingCurve(QEasingCurve::InOutQuad);

    QPropertyAnimation* pScaleAnimation2 = new QPropertyAnimation(ui->scaleButton, "geometry");
    pScaleAnimation2->setDuration(1000);
    pScaleAnimation2->setStartValue(QRect(120, 160, 140, 140));//(起始横坐标，起始纵坐标，起始窗口长度，起始窗口宽度)
    pScaleAnimation2->setEndValue(QRect(190, 230, 0, 0));//(末尾横坐标，末尾纵坐标，末尾窗口长度，末尾窗口宽度)
    pScaleAnimation2->setEasingCurve(QEasingCurve::InOutQuad);

    QSequentialAnimationGroup* pScaleGroup = new QSequentialAnimationGroup(this);
    pScaleGroup->addAnimation(pScaleAnimation1);
    pScaleGroup->addAnimation(pScaleAnimation2);
    ui->scaleButton->setText("取值范围0~10");
    ui->startButton->setText("不要点我");
    ui->startButton->setGeometry(340, 500, 80, 40);
    m_group = new QParallelAnimationGroup(this);
    m_group->addAnimation(pScaleGroup);


}


MainWindow::~MainWindow()
{
    delete colorAnimation;
}




void MainWindow::on_startButton_clicked()
{
    m_group->setDirection(QAbstractAnimation::Forward);
    m_group->setLoopCount(1);
    m_group->start();
}


// 下面是需要用到的函数
void MainWindow::toggleMode()
{
    if (isDarkMode) {
        // 从夜间模式切换到白天模式
        startColorTransition(endColor, startColor);
        ui->menubutton->setIcon(setIconColor(ui->menubutton->icon(), QColor(64, 64, 64)));
        ui->helpbutton->setIcon(setIconColor(ui->helpbutton->icon(), QColor(64, 64, 64)));
        ui->settingbutton->setIcon(setIconColor(ui->settingbutton->icon(), QColor(64, 64, 64)));

        ui->choicebutton1->setStyleSheet("QPushButton {background-color:rgba(0,0,0,0); border: none; border-radius: 0px; transition: all 0.1s ease; color: rgb(64, 64, 64)}"
                                         "QPushButton:hover {background-color: #40E0D0; transform: translateY(-5px); box-shadow: 0px 5px 15px rgba(0, 0, 0, 0.2);}"
                                         "QPushButton:checked {border-left-width:7px; background-color: #20C0B0}");
        ui->choicebutton2->setStyleSheet("QPushButton {background-color:rgba(0,0,0,0); border: none; border-radius: 0px; transition: all 0.1s ease; color: rgb(64, 64, 64)}"
                                         "QPushButton:hover {background-color: #40E0D0; transform: translateY(-5px); box-shadow: 0px 5px 15px rgba(0, 0, 0, 0.2);}"
                                         "QPushButton:checked {border-left-width:7px; background-color: #20C0B0}");
        ui->choicebutton3->setStyleSheet("QPushButton {background-color:rgba(0,0,0,0); border: none; border-radius: 0px; transition: all 0.1s ease; color: rgb(64, 64, 64)}"
                                         "QPushButton:hover {background-color: #40E0D0; transform: translateY(-5px); box-shadow: 0px 5px 15px rgba(0, 0, 0, 0.2);}"
                                         "QPushButton:checked {border-left-width:7px; background-color: #20C0B0}");
        ui->choicebutton4->setStyleSheet("QPushButton {background-color:rgba(0,0,0,0); border: none; border-radius: 0px; transition: all 0.1s ease; color: rgb(64, 64, 64)}"
                                         "QPushButton:hover {background-color: #40E0D0; transform: translateY(-5px); box-shadow: 0px 5px 15px rgba(0, 0, 0, 0.2);}"
                                         "QPushButton:checked {border-left-width:7px; background-color: #20C0B0}");
        ui->choicebutton5->setStyleSheet("QPushButton {background-color:rgba(0,0,0,0); border: none; border-radius: 0px; transition: all 0.1s ease; color: rgb(64, 64, 64)}"
                                         "QPushButton:hover {background-color: #40E0D0; transform: translateY(-5px); box-shadow: 0px 5px 15px rgba(0, 0, 0, 0.2);}"
                                         "QPushButton:checked {border-left-width:7px; background-color: #20C0B0}");
        ui->normstart->setStyleSheet("QPushButton {color:rgb(64,64,64); background-color: rgba(128,128,128,0.5); border:none}"
                                           "QPushButton:hover {background-color: rgba(128,128,128,0.7)}");

        ui->creatorlist->setStyleSheet("color:rgb(64,64,64)");
        ui->homepagetitle->setStyleSheet("color:rgb(64,64,64)");
        ui->page2title->setStyleSheet("color:rgb(64,64,64)");
        // destroy_maintitle->setStyleSheet("color:rgb(64,64,64)");

        ui->choicebutton1->setIcon(setIconColor(ui->choicebutton1->icon(), QColor(64, 64, 64)));
        ui->choicebutton2->setIcon(setIconColor(ui->choicebutton2->icon(), QColor(64, 64, 64)));
        ui->choicebutton3->setIcon(setIconColor(ui->choicebutton3->icon(), QColor(64, 64, 64)));
        ui->choicebutton4->setIcon(setIconColor(ui->choicebutton4->icon(), QColor(64, 64, 64)));
        ui->choicebutton5->setIcon(setIconColor(ui->choicebutton5->icon(), QColor(64, 64, 64)));

        ui->norm_num1->setStyleSheet("color:rgb(64,64,64)");
        ui->norm_num2->setStyleSheet("color:rgb(64,64,64)");
        ui->norm_num3->setStyleSheet("color:rgb(64,64,64)");
        ui->norm_num4->setStyleSheet("color:rgb(64,64,64)");
        ui->right_or_not->setStyleSheet("color:rgb(64,64,64)");

        ui->numinput1->setStyleSheet("border-radius:8px; background-color: rgba(32, 192, 160, 0.5); color: rgb(64, 64, 64)");
        ui->strinput1->setStyleSheet("border-radius:8px; background-color: rgba(64, 224, 192, 0.5); color: rgb(64, 64, 64)");
        ui->numinput2->setStyleSheet("border-radius:8px; background-color: rgba(32, 192, 160, 0.5); color: rgb(64, 64, 64)");
        ui->strinput2->setStyleSheet("border-radius:8px; background-color: rgba(64, 224, 192, 0.5); color: rgb(64, 64, 64)");
        ui->numinput3->setStyleSheet("border-radius:8px; background-color: rgba(32, 192, 160, 0.5); color: rgb(64, 64, 64)");
        ui->strinput3->setStyleSheet("border-radius:8px; background-color: rgba(64, 224, 192, 0.5); color: rgb(64, 64, 64)");
        ui->numinput4->setStyleSheet("border-radius:8px; background-color: rgba(32, 192, 160, 0.5); color: rgb(64, 64, 64)");
        ui->strinput4->setStyleSheet("border-radius:8px; background-color: rgba(64, 224, 192, 0.5); color: rgb(64, 64, 64)");
        ui->strinput5->setStyleSheet("border-radius:8px; background-color: rgba(64, 224, 192, 0.5); color: rgb(64, 64, 64)");

        // modeButton->setText("夜间模式");
        // modeButton->setStyleSheet("QPushButton{color:black; font-family:Microsoft Yahei; background:rgb(192, 192, 192); border-radius:10px;}"
        //                           "QPushButton::hover{background:rgb(164, 164, 164);}");
        // printf(this->x());
    } else {
        // 从白天模式切换到夜间模式
        startColorTransition(startColor, endColor);
        ui->menubutton->setIcon(setIconColor(ui->menubutton->icon(), QColor(192, 192, 192)));
        ui->helpbutton->setIcon(setIconColor(ui->helpbutton->icon(), QColor(192, 192, 192)));
        ui->settingbutton->setIcon(setIconColor(ui->settingbutton->icon(), QColor(192, 192, 192)));

        ui->choicebutton1->setStyleSheet("QPushButton {background-color:rgba(0,0,0,0); border: none; border-radius: 0px; transition: all 0.1s ease; color: rgb(224, 224, 224)}"
                                         "QPushButton:hover {background-color: #10B0A0; transform: translateY(-5px); box-shadow: 0px 5px 15px rgba(64, 64, 64, 0.2);}"
                                         "QPushButton:checked {border-left-width:7px; background-color: #20C0B0}");
        ui->choicebutton2->setStyleSheet("QPushButton {background-color:rgba(0,0,0,0); border: none; border-radius: 0px; transition: all 0.1s ease; color: rgb(224, 224, 224)}"
                                         "QPushButton:hover {background-color: #10B0A0; transform: translateY(-5px); box-shadow: 0px 5px 15px rgba(64, 64, 64, 0.2);}"
                                         "QPushButton:checked {border-left-width:7px; background-color: #20C0B0}");
        ui->choicebutton3->setStyleSheet("QPushButton {background-color:rgba(0,0,0,0); border: none; border-radius: 0px; transition: all 0.1s ease; color: rgb(224, 224, 224)}"
                                         "QPushButton:hover {background-color: #10B0A0; transform: translateY(-5px); box-shadow: 0px 5px 15px rgba(64, 64, 64, 0.2);}"
                                         "QPushButton:checked {border-left-width:7px; background-color: #20C0B0}");
        ui->choicebutton4->setStyleSheet("QPushButton {background-color:rgba(0,0,0,0); border: none; border-radius: 0px; transition: all 0.1s ease; color: rgb(224, 224, 224)}"
                                         "QPushButton:hover {background-color: #10B0A0; transform: translateY(-5px); box-shadow: 0px 5px 15px rgba(64, 64, 64, 0.2);}"
                                         "QPushButton:checked {border-left-width:7px; background-color: #20C0B0}");
        ui->choicebutton5->setStyleSheet("QPushButton {background-color:rgba(0,0,0,0); border: none; border-radius: 0px; transition: all 0.1s ease; color: rgb(224, 224, 224)}"
                                         "QPushButton:hover {background-color: #10B0A0; transform: translateY(-5px); box-shadow: 0px 5px 15px rgba(64, 64, 64, 0.2);}");
        ui->normstart->setStyleSheet("QPushButton {color:rgb(192,192,192); background-color: rgba(128,128,128,0.5); border:none}"
                                           "QPushButton:hover {background-color: rgba(128,128,128,0.7)}");

        ui->creatorlist->setStyleSheet("color:rgb(224,224,224)");
        ui->homepagetitle->setStyleSheet("color:rgb(224,224,224)");
        // destroy_maintitle->setStyleSheet("color:rgb(224,224,224)");
        ui->page2title->setStyleSheet("color:rgb(224,224,224)");

        ui->choicebutton1->setIcon(setIconColor(ui->choicebutton1->icon(), QColor(224, 224, 224)));
        ui->choicebutton2->setIcon(setIconColor(ui->choicebutton2->icon(), QColor(224, 224, 224)));
        ui->choicebutton3->setIcon(setIconColor(ui->choicebutton3->icon(), QColor(224, 224, 224)));
        ui->choicebutton4->setIcon(setIconColor(ui->choicebutton4->icon(), QColor(224, 224, 224)));
        ui->choicebutton5->setIcon(setIconColor(ui->choicebutton5->icon(), QColor(224, 224, 224)));

        ui->norm_num1->setStyleSheet("color:rgb(224,224,224)");
        ui->norm_num2->setStyleSheet("color:rgb(224,224,224)");
        ui->norm_num3->setStyleSheet("color:rgb(224,224,224)");
        ui->norm_num4->setStyleSheet("color:rgb(224,224,224)");
        ui->right_or_not->setStyleSheet("color:rgb(224,224,224)");

        ui->numinput1->setStyleSheet("border-radius:8px; background-color: rgba(64, 224, 192, 0.5); color: rgb(224, 224, 224)");
        ui->strinput1->setStyleSheet("border-radius:8px; background-color: rgba(32, 192, 160, 0.5); color: rgb(224, 224, 224)");
        ui->numinput2->setStyleSheet("border-radius:8px; background-color: rgba(64, 224, 192, 0.5); color: rgb(224, 224, 224)");
        ui->strinput2->setStyleSheet("border-radius:8px; background-color: rgba(32, 192, 160, 0.5); color: rgb(224, 224, 224)");
        ui->numinput3->setStyleSheet("border-radius:8px; background-color: rgba(64, 224, 192, 0.5); color: rgb(224, 224, 224)");
        ui->strinput3->setStyleSheet("border-radius:8px; background-color: rgba(32, 192, 160, 0.5); color: rgb(224, 224, 224)");
        ui->numinput4->setStyleSheet("border-radius:8px; background-color: rgba(64, 224, 192, 0.5); color: rgb(224, 224, 224)");
        ui->strinput4->setStyleSheet("border-radius:8px; background-color: rgba(32, 192, 160, 0.5); color: rgb(224, 224, 224)");
        ui->strinput5->setStyleSheet("border-radius:8px; background-color: rgba(32, 192, 160, 0.5); color: rgb(224, 224, 224)");
        // modeButton->setText("日间模式");
        // modeButton->setStyleSheet("QPushButton{color:white; font-family:Microsoft Yahei; background:rgb(64, 64, 64); border-radius:10px;}"
        //                           "QPushButton::hover{background:rgb(92, 92, 92);}");
    }
    isDarkMode = !isDarkMode;  // 切换当前模式
}


void MainWindow::startColorTransition(const QColor &start, const QColor &end)
{
    // 动画设置开始值和结束值
    colorAnimation->setStartValue(start);
    colorAnimation->setEndValue(end);

    // 连接动画帧信号，用于实时更新背景颜色
    connect(colorAnimation, &QPropertyAnimation::valueChanged, [this](const QVariant &value) {
        QColor currentColor = value.value<QColor>();
        applyPalette(currentColor);
    });

    // 启动动画
    colorAnimation->start();
}


void MainWindow::applyPalette(const QColor &color)
{
    QPalette palette = this->palette();
    palette.setColor(QPalette::Window, color);  // 设置背景颜色
    this->setPalette(palette);
}


// 侧边栏动画
void MainWindow::sidemenu_pushbutton_clicked()
{
    if (!sidemenuFlag)
    {
        // 侧栏拉出
        sidemenuAnimation1->setStartValue(QRect(-ui->menu->width()/2 - 50, 0, ui->menu->width(), ui->menu->height()));
        sidemenuAnimation1->setEndValue(QRect(0, 0, ui->menu->width(), ui->menu->height()));
        sidemenuAnimation1->start();

        sidemenuAnimation2->setStartValue(QRect(110, 0, ui->homewidget->width(), ui->homewidget->height()));
        sidemenuAnimation2->setEndValue(QRect(60+ui->menu->width()/2+50, 0, ui->homewidget->width()-ui->menu->width()/2, ui->homewidget->height()));
        sidemenuAnimation2->start();
        sidemenuFlag = !sidemenuFlag;
    }
    else
    {
        // 侧栏收入
        sidemenuAnimation1->setStartValue(QRect(0, 0, ui->menu->width(), ui->menu->height()));
        sidemenuAnimation1->setEndValue(QRect(-ui->menu->width()/2 - 50, 0, ui->menu->width(), ui->menu->height()));
        sidemenuAnimation1->start();
        sidemenuAnimation2->setStartValue(QRect(60+ui->menu->width()/2+50, 0, ui->homewidget->width(), ui->homewidget->height()));
        sidemenuAnimation2->setEndValue(QRect(110, 0, ui->homewidget->width()+ui->menu->width()/2, ui->homewidget->height()));
        sidemenuAnimation2->start();
        sidemenuFlag = !sidemenuFlag;
    }
}


// 切换模式时用于修改各个控件中图标颜色（通用函数）
QIcon MainWindow::setIconColor(QIcon icon, QColor color)
{
    QPixmap pixmap = icon.pixmap(QSize(50,50));
    QPainter painter(&pixmap);
    painter.setCompositionMode(QPainter::CompositionMode_SourceIn);
    painter.fillRect(pixmap.rect(), color);
    QIcon colorIcon = QIcon(pixmap);
    return colorIcon;
}


void MainWindow::switchPage(){

}


// 初始化函数
void MainWindow::initProperties()
{
    // ---------------------------------------------------------------------------------
    // 初始化主页面
    this->setFixedSize(1000, 600);
    this->setWindowTitle("小游戏: 计算24点");


    // QGraphicsOpacityEffect *homepagetitleOpacity = new QGraphicsOpacityEffect(ui->homepagetitle);
    // homepagetitleOpacity->setOpacity(0);
    // ui->homepagetitle->setGraphicsEffect(homepagetitleOpacity);

    // homepagetitleAnimation = new QPropertyAnimation(homepagetitleOpacity, "opacity", this);
    // homepagetitleAnimation->setEasingCurve(QEasingCurve::Linear);
    // homepagetitleAnimation->setDuration(1000);
    // homepagetitleinit();

    // ---------------------------------------------------------------------------------2024.10.14
    // 这部分代码用于实现昼夜模式切换、帮助界面、设置界面
    modeButton = ui->testButton;
    // modeButton = new QPushButton("夜间模式", this);
    modeButton->setGeometry(960, 560, 30, 30);
    // modeButton->setStyleSheet("QPushButton{color:black; font-family:Microsoft Yahei; background:rgb(192, 192, 192); border-radius:10px;}"
    //                           "QPushButton::hover{background:rgb(164, 164, 164);}");
    modeButton->setStyleSheet("QPushButton{background-color:rgba(0,0,0,0); border: none}");
    ui->helpbutton->setStyleSheet("QPushButton{background-color:rgba(0,0,0,0); border: none}");
    ui->settingbutton->setStyleSheet("QPushButton{background-color:rgba(0,0,0,0); border: none}");

    connect(modeButton, &QPushButton::clicked, this, &MainWindow::toggleMode);
    connect(ui->menubutton, &QPushButton::clicked, this, &MainWindow::sidemenu_pushbutton_clicked);

    colorAnimation = new QPropertyAnimation(this, "color");
    colorAnimation->setDuration(300);  // 动画时长 0.3 秒

    startColor = QColor(255, 255, 255);  // 白天模式的背景颜色（白色）
    endColor = QColor(43, 43, 43);       // 夜间模式的背景颜色（黑色）

    applyPalette(startColor);
    //----------------------------------------------------------------------------------


    //----------------------------------------------------------------------------------2024.10.15
    // 侧边栏动画及按钮部分
    ui->widget_side->setStyleSheet("background-color: rgba(64, 224, 208, 128)");
    // ui->widget_side->setStyleSheet("background: qlineargradient(x1:0, y1:0, x2:1, y2:0,stop:0 #497BF0,stop:1 #1FB6F6)");
    // ui->menu->setStyleSheet("background-color: rgba(128, 128, 128, 128)");

    ui->choicebutton1->setStyleSheet("QPushButton {background-color:rgba(0,0,0,0); border: none; border-radius: 0px; transition: all 0.1s ease; color: rgb(64, 64, 64)}"
                                     "QPushButton:hover {background-color: #40E0D0; transform: translateY(-5px); box-shadow: 0px 5px 15px rgba(0, 0, 0, 0.2);}"
                                     "QPushButton:checked {border-left-width:7px; background-color: #20C0B0}");
    ui->choicebutton2->setStyleSheet("QPushButton {background-color:rgba(0,0,0,0); border: none; border-radius: 0px; transition: all 0.1s ease; color: rgb(64, 64, 64)}"
                                     "QPushButton:hover {background-color: #40E0D0; transform: translateY(-5px); box-shadow: 0px 5px 15px rgba(0, 0, 0, 0.2);}"
                                     "QPushButton:checked {border-left-width:7px; background-color: #20C0B0}");
    ui->choicebutton3->setStyleSheet("QPushButton {background-color:rgba(0,0,0,0); border: none; border-radius: 0px; transition: all 0.1s ease; color: rgb(64, 64, 64)}"
                                     "QPushButton:hover {background-color: #40E0D0; transform: translateY(-5px); box-shadow: 0px 5px 15px rgba(0, 0, 0, 0.2);}"
                                     "QPushButton:checked {border-left-width:7px; background-color: #20C0B0}");
    ui->choicebutton4->setStyleSheet("QPushButton {background-color:rgba(0,0,0,0); border: none; border-radius: 0px; transition: all 0.1s ease; color: rgb(64, 64, 64)}"
                                     "QPushButton:hover {background-color: #40E0D0; transform: translateY(-5px); box-shadow: 0px 5px 15px rgba(0, 0, 0, 0.2);}"
                                     "QPushButton:checked {border-left-width:7px; background-color: #20C0B0}");
    ui->choicebutton5->setStyleSheet("QPushButton {background-color:rgba(0,0,0,0); border: none; border-radius: 0px; transition: all 0.1s ease; color: rgb(64, 64, 64)}"
                                     "QPushButton:hover {background-color: #40E0D0; transform: translateY(-5px); box-shadow: 0px 5px 15px rgba(0, 0, 0, 0.2);}"
                                     "QPushButton:checked {border-left-width:7px; background-color: #20C0B0}");
    ui->menubutton->setStyleSheet("QPushButton {background-color:rgba(0,0,0,0); border: none; border-radius: 0px; transition: all 0.1s ease; color: rgb(64, 64, 64)}"
                                  "QPushButton: hover {background-color: rgba{0,0,0,0}; border: 0px; transform: translateY(-5px); box-shadow: 0px 5px 15px rgba(0, 0, 0, 0.1);}");
    ui->final_confirmbutton1->setText("确认？");
    ui->final_confirmbutton1->setStyleSheet("QPushButton {background-color:rgb(128,128,128); border:none; border-radius:0px}"
                                            "QPushButton:hover {background-color:rgb(128,128,128); border:none; border-radius:0px}");
    ui->numinput1->setStyleSheet("border-radius:8px; background-color: rgba(32, 192, 160, 0.5)");
    ui->strinput1->setStyleSheet("border-radius:8px; background-color: rgba(64, 224, 192, 0.5)");
    ui->numinput2->setStyleSheet("border-radius:8px; background-color: rgba(32, 192, 160, 0.5)");
    ui->strinput2->setStyleSheet("border-radius:8px; background-color: rgba(64, 224, 192, 0.5)");
    ui->numinput3->setStyleSheet("border-radius:8px; background-color: rgba(32, 192, 160, 0.5)");
    ui->strinput3->setStyleSheet("border-radius:8px; background-color: rgba(64, 224, 192, 0.5)");
    ui->numinput4->setStyleSheet("border-radius:8px; background-color: rgba(32, 192, 160, 0.5)");
    ui->strinput4->setStyleSheet("border-radius:8px; background-color: rgba(64, 224, 192, 0.5)");
    ui->strinput5->setStyleSheet("border-radius:8px; background-color: rgba(64, 224, 192, 0.5)");

    ui->menu->move(-ui->menu->width()/2-50, 0);
    ui->widget_side->layout()->setAlignment(Qt::AlignLeft);
    ui->widget_side2->layout()->setAlignment(Qt::AlignRight);
    ui->menubutton->setGeometry(0, 0, 40, 40);
    // ui->menubutton->setStyleSheet("QPushButton{background-color:rgba(0, 0, 0, 0);}");
    ui->widget_side->layout()->setAlignment(Qt::AlignBottom);

    menubuttonGroup = new QButtonGroup;
    menubuttonGroup->addButton(ui->choicebutton1, 0);
    menubuttonGroup->addButton(ui->choicebutton2, 1);
    menubuttonGroup->addButton(ui->choicebutton3, 2);
    menubuttonGroup->addButton(ui->choicebutton4, 3);

    norm_confirm_buttongroup = new QButtonGroup;
    norm_confirm_buttongroup->addButton(ui->confirmbutton0, 0);
    norm_confirm_buttongroup->addButton(ui->confirmbutton1, 1);

    connect(menubuttonGroup, &QButtonGroup::idClicked, ui->homewidget, &QStackedWidget::setCurrentIndex);
    connect(norm_confirm_buttongroup, &QButtonGroup::idClicked, ui->confirmpage, &QStackedWidget::setCurrentIndex);
    connect(ui->choicebutton5, &QPushButton::clicked, this, &QWidget::close);


    sidemenuAnimation1 = new QPropertyAnimation(ui->menu, "geometry");
    sidemenuAnimation1->setEasingCurve(QEasingCurve::InOutSine);
    sidemenuAnimation2 = new QPropertyAnimation(ui->homewidget, "geometry");
    sidemenuAnimation2->setEasingCurve(QEasingCurve::InOutSine);

    sidemenuAnimation1->setDuration(600);
    sidemenuAnimation2->setDuration(600);
    //---------------------------------------------------------------------------------


    //---------------------------------------------------------------------------------2024.10.16
    // 普通模式开发
    ui->normstart->setStyleSheet("QPushButton {color:rgb(64,64,64); background-color: rgba(128,128,128,0.5); border:none}"
                                       "QPushButton:hover {background-color: rgba(128,128,128,0.7)}");
    /// innerstackwidget 的第一页，点击“开始”进入第二页（普通模式游戏主要界面）
    connect(ui->normstart, &QPushButton::clicked, [=](){
        ui->innerstack2->setCurrentIndex(1);
    });

    ui->normgamerule->setStyleSheet("background-color: rgba(0,0,0,0); border-width:0; border-style:outset");

    /// 生成四个随机的满足24点的数字
    norm_random_key = generateRandomInt10();
    std::vector<string> norm_random_24numbers_exp = generate24(4, 24, norm_random_key);
    std::vector<string> norm_random_24numbers = getFirstFourNumericStrings(norm_random_24numbers_exp, 4);
    ui->norm_num2->setText(QString::fromStdString(norm_random_24numbers[0]));
    ui->norm_num2->setText(QString::fromStdString(norm_random_24numbers[1]));
    ui->norm_num2->setText(QString::fromStdString(norm_random_24numbers[2]));
    ui->norm_num2->setText(QString::fromStdString(norm_random_24numbers[3]));
    int norm_num_arr[4];
    for (int i=0; i<4; i++){
        norm_num_arr[i] = std::stoi(norm_random_24numbers[i]);
    }

    /// Find函数整体案例解析
    std::vector<double> numbers;
    std::vector<std::string> expressions;
    numbers.clear();/// 注意，因为传入Find函数之前的每个变量是以地址传输的所以最好最终传输前归一次0
    expressions.clear();
    for (int i = 0; i < 4; i++) {
        double num;
        std::cin >> num;
        numbers.push_back(norm_num_arr[i]);/// 数字向量初始化
        expressions.push_back(std::to_string(norm_num_arr[i]));/// 字符串向量初始化
    }
    double VOLUE=24;
    /// Find函数，输入（含有4个数的数组（类型vector<double> numbers），含有这4个数字字符串的字符串向量（类型vector<std::string> expressions）,数字个数，VOLUE(24点)）
    Result result = Find(numbers, expressions, 4, VOLUE);
    /// 输出：Result类型的result(包括两个变量，bool类型的ispossible,以及字符串数组类型的expressions)

    if (result.isPossible && !result.expressions.empty()) {
        std::cout << "YES" << std::endl;
        std::cout << result.expressions[0] <<"="<<VOLUE << std::endl;//每一个expression都是一种可能的解法，我们选取第一个
    }
    else {
        std::cout << "NO" << VOLUE << std::endl;
    }
    /// Find函数整体案例解析


    //-------------------------------------------------------------------------------------------
    // 消消乐模式初始化代码
    /// 创建一个VLayout
    // Timer *timer;

    QVBoxLayout *page3_main_layout = new QVBoxLayout(ui->page_3);
    /// 顶部加入弹簧
    QSpacerItem *page3_top_spacer = new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Fixed);
    QSpacerItem *page3_between_spacer = new QSpacerItem(10, 50, QSizePolicy::Minimum, QSizePolicy::Expanding);
    QSpacerItem *page3_bottom_spacer = new QSpacerItem(10, 50, QSizePolicy::Minimum, QSizePolicy::Expanding);
    page3_main_layout->addSpacerItem(page3_top_spacer);

    /// 弹簧下面放入页面主标题
    QLabel *destroy_maintitle = new QLabel(this);

    // SliderButton the_slider(this);

    QLabel *page3_bottom_icon = new QLabel();
    // page3_main_layout->addWidget(the_slider);
    page3_main_layout->addWidget(destroy_maintitle);
    destroy_maintitle->setText("消消乐模式");
    page3_bottom_icon->setText("<<");
    QFont ft("Microsoft YaHei UI", 20, 63);
    ft.setBold(true);
    destroy_maintitle->setFont(ft);
    page3_bottom_icon->setFont(ft);
    destroy_maintitle->setGeometry(9, 20, 300, 80);
    page3_bottom_icon->setAlignment(Qt::AlignRight);

    /// 标题下方加入 stack widget（含有3页）
    QStackedWidget *page3_inner_pages = new QStackedWidget;
    // page3_inner_pages->setMaximumHeight(370);
    page3_main_layout->addSpacerItem(page3_between_spacer);
    page3_main_layout->addWidget(page3_inner_pages);
    page3_main_layout->addSpacerItem(page3_bottom_spacer);
    page3_main_layout->addWidget(page3_bottom_icon);
    QWidget *page3_inner_page0 = new QWidget;
    QWidget *page3_inner_page1 = new QWidget;
    QWidget *page3_inner_page2 = new QWidget;

    page3_inner_pages->addWidget(page3_inner_page0);
    page3_inner_pages->addWidget(page3_inner_page1);
    page3_inner_pages->addWidget(page3_inner_page2);

    /// page3首页编辑
    QLabel *page3_inner_page0_label0 = new QLabel("我是首页", page3_inner_page0);
    QHBoxLayout *page3_inner_page0_mainlayout = new QHBoxLayout(page3_inner_page0);
    QVBoxLayout *page3_inner_page0_rulelayout = new QVBoxLayout;
    QPushButton *page3_inner_page0_startbutton = new QPushButton("Start");
    QSpacerItem *page3_inner_page0_mainlayout_leftspacer = new QSpacerItem(40, 10, QSizePolicy::Minimum, QSizePolicy::Fixed);
    QSpacerItem *page3_inner_page0_mainlayout_rightspacer = new QSpacerItem(120, 10, QSizePolicy::Minimum, QSizePolicy::Expanding);
    QSpacerItem *page3_inner_page0_underbutton_spacer = new QSpacerItem(10, 120, QSizePolicy::Fixed, QSizePolicy::Minimum);

    page3_inner_page0_rulelayout->addWidget(page3_inner_page0_label0);

    page3_inner_page0_mainlayout->addSpacerItem(page3_inner_page0_mainlayout_leftspacer);
    page3_inner_page0_mainlayout->addLayout(page3_inner_page0_rulelayout);
    page3_inner_page0_mainlayout->addSpacerItem(page3_inner_page0_mainlayout_rightspacer);

    page3_inner_page0_rulelayout->addWidget(page3_inner_page0_startbutton);
    page3_inner_page0_rulelayout->addSpacerItem(page3_inner_page0_underbutton_spacer);
    page3_inner_page0_label0->setGeometry(0, 0, 200, 50);
    page3_inner_page0_label0->setAlignment(Qt::AlignCenter);
    page3_inner_page0_startbutton->setFixedSize(80, 40);

    page3_inner_pages->setCurrentIndex(0);
    connect(page3_inner_page0_startbutton, &QPushButton::clicked, [=](){
        page3_inner_pages->setCurrentIndex(1);
        // timer->start();
    });


    /// page3游戏界面编辑
    QLabel *page3_inner_page1_label0 = new QLabel("我是游戏界面", page3_inner_page1);
    QHBoxLayout *page3_inner_page1_mainlayout = new QHBoxLayout(page3_inner_page1);
    QVBoxLayout *page3_inner_page1_rulelayout = new QVBoxLayout;
    QPushButton *page3_inner_page1_startbutton = new QPushButton("重置");
    QSpacerItem *page3_inner_page1_mainlayout_leftspacer = new QSpacerItem(40, 10, QSizePolicy::Minimum, QSizePolicy::Fixed);
    QSpacerItem *page3_inner_page1_mainlayout_rightspacer = new QSpacerItem(120, 10, QSizePolicy::Minimum, QSizePolicy::Expanding);
    QSpacerItem *page3_inner_page1_mainlayout_bottomspacer = new QSpacerItem(10, 40, QSizePolicy::Fixed, QSizePolicy::Minimum);
    QSpacerItem *page3_inner_page1_underbutton_spacer = new QSpacerItem(10, 60, QSizePolicy::Fixed, QSizePolicy::Minimum);
    QSpacerItem *page3_inner_page1_uponbutton_spacer = new QSpacerItem(10, 120, QSizePolicy::Fixed, QSizePolicy::Fixed);
    QSpacerItem *page3_inner_page1_between_layouts_spacer = new QSpacerItem(50, 10, QSizePolicy::Minimum, QSizePolicy::Fixed);
    QGridLayout *page3_inner_page1_gameblocks_layout = new QGridLayout;
    QPushButton *page3_gameblock1 = new QPushButton("我是按钮1", page3_inner_page1);
    QPushButton *page3_gameblock2 = new QPushButton("我是按钮2", page3_inner_page1);
    QPushButton *page3_gameblock3 = new QPushButton("我是按钮3", page3_inner_page1);
    QPushButton *page3_gameblock4 = new QPushButton("我是按钮4", page3_inner_page1);
    QPushButton *page3_gameblock5 = new QPushButton("我是按钮5", page3_inner_page1);
    QPushButton *page3_gameblock6 = new QPushButton("我是按钮6", page3_inner_page1);
    QPushButton *page3_gameblock7 = new QPushButton("我是按钮7", page3_inner_page1);
    QPushButton *page3_gameblock8 = new QPushButton("我是按钮8", page3_inner_page1);
    QPushButton *page3_gameblock9 = new QPushButton("我是按钮9", page3_inner_page1);
    QPushButton *page3_gameblock10 = new QPushButton("我是按钮10", page3_inner_page1);
    QPushButton *page3_gameblock11 = new QPushButton("我是按钮11", page3_inner_page1);
    QPushButton *page3_gameblock12 = new QPushButton("我是按钮12", page3_inner_page1);
    QPushButton *page3_gameblock13 = new QPushButton("我是按钮13", page3_inner_page1);
    QPushButton *page3_gameblock14 = new QPushButton("我是按钮14", page3_inner_page1);
    QPushButton *page3_gameblock15 = new QPushButton("我是按钮15", page3_inner_page1);
    QPushButton *page3_gameblock16 = new QPushButton("我是按钮16", page3_inner_page1);
    QButtonGroup *page3_game_blocks = new QButtonGroup(page3_inner_page1);
    QFont buttonfont("Microsoft YaHei UI", 18, 75);
    buttonfont.setBold(true);

    // vector<double> page3_game_numberstore;
    // int page3_game_targetnumber;
    page3_game_targetnumber = -1;

    page3_gameblock1->setCheckable(true);
    page3_gameblock2->setCheckable(true);
    page3_gameblock3->setCheckable(true);
    page3_gameblock4->setCheckable(true);
    page3_gameblock5->setCheckable(true);
    page3_gameblock6->setCheckable(true);
    page3_gameblock7->setCheckable(true);
    page3_gameblock8->setCheckable(true);
    page3_gameblock9->setCheckable(true);
    page3_gameblock10->setCheckable(true);
    page3_gameblock11->setCheckable(true);
    page3_gameblock12->setCheckable(true);
    page3_gameblock13->setCheckable(true);
    page3_gameblock14->setCheckable(true);
    page3_gameblock15->setCheckable(true);
    page3_gameblock16->setCheckable(true);

    page3_gameblock1->setStyleSheet("QPushButton {border-radius:8px; background-color: rgba(96, 255, 224, 0.5); color: rgb(64, 64, 64)}"
                                    "QPushButton:hover {border-radius:8px; background-color: rgba(64, 224, 192, 0.5); color: rgb(64, 64, 64)}"
                                    "QPushButton:pressed {border-radius:8px; background-color: rgba(32, 192, 160, 0.5); color: rgb(64, 64, 64)}"
                                    "QPushButton:checked {border-radius:8px; background-color: rgba(32, 192, 160, 0.5); color: rgb(64, 64, 64)}");
    page3_gameblock2->setStyleSheet("QPushButton {border-radius:8px; background-color: rgba(96, 255, 224, 0.5); color: rgb(64, 64, 64)}"
                                    "QPushButton:hover {border-radius:8px; background-color: rgba(64, 224, 192, 0.5); color: rgb(64, 64, 64)}"
                                    "QPushButton:pressed {border-radius:8px; background-color: rgba(32, 192, 160, 0.5); color: rgb(64, 64, 64)}"
                                    "QPushButton:checked {border-radius:8px; background-color: rgba(32, 192, 160, 0.5); color: rgb(64, 64, 64)}");
    page3_gameblock3->setStyleSheet("QPushButton {border-radius:8px; background-color: rgba(96, 255, 224, 0.5); color: rgb(64, 64, 64)}"
                                    "QPushButton:hover {border-radius:8px; background-color: rgba(64, 224, 192, 0.5); color: rgb(64, 64, 64)}"
                                    "QPushButton:pressed {border-radius:8px; background-color: rgba(32, 192, 160, 0.5); color: rgb(64, 64, 64)}"
                                    "QPushButton:checked {border-radius:8px; background-color: rgba(32, 192, 160, 0.5); color: rgb(64, 64, 64)}");
    page3_gameblock4->setStyleSheet("QPushButton {border-radius:8px; background-color: rgba(96, 255, 224, 0.5); color: rgb(64, 64, 64)}"
                                    "QPushButton:hover {border-radius:8px; background-color: rgba(64, 224, 192, 0.5); color: rgb(64, 64, 64)}"
                                    "QPushButton:pressed {border-radius:8px; background-color: rgba(32, 192, 160, 0.5); color: rgb(64, 64, 64)}"
                                    "QPushButton:checked {border-radius:8px; background-color: rgba(32, 192, 160, 0.5); color: rgb(64, 64, 64)}");
    page3_gameblock5->setStyleSheet("QPushButton {border-radius:8px; background-color: rgba(96, 255, 224, 0.5); color: rgb(64, 64, 64)}"
                                    "QPushButton:hover {border-radius:8px; background-color: rgba(64, 224, 192, 0.5); color: rgb(64, 64, 64)}"
                                    "QPushButton:pressed {border-radius:8px; background-color: rgba(32, 192, 160, 0.5); color: rgb(64, 64, 64)}"
                                    "QPushButton:checked {border-radius:8px; background-color: rgba(32, 192, 160, 0.5); color: rgb(64, 64, 64)}");
    page3_gameblock6->setStyleSheet("QPushButton {border-radius:8px; background-color: rgba(96, 255, 224, 0.5); color: rgb(64, 64, 64)}"
                                    "QPushButton:hover {border-radius:8px; background-color: rgba(64, 224, 192, 0.5); color: rgb(64, 64, 64)}"
                                    "QPushButton:pressed {border-radius:8px; background-color: rgba(32, 192, 160, 0.5); color: rgb(64, 64, 64)}"
                                    "QPushButton:checked {border-radius:8px; background-color: rgba(32, 192, 160, 0.5); color: rgb(64, 64, 64)}");
    page3_gameblock7->setStyleSheet("QPushButton {border-radius:8px; background-color: rgba(96, 255, 224, 0.5); color: rgb(64, 64, 64)}"
                                    "QPushButton:hover {border-radius:8px; background-color: rgba(64, 224, 192, 0.5); color: rgb(64, 64, 64)}"
                                    "QPushButton:pressed {border-radius:8px; background-color: rgba(32, 192, 160, 0.5); color: rgb(64, 64, 64)}"
                                    "QPushButton:checked {border-radius:8px; background-color: rgba(32, 192, 160, 0.5); color: rgb(64, 64, 64)}");
    page3_gameblock8->setStyleSheet("QPushButton {border-radius:8px; background-color: rgba(96, 255, 224, 0.5); color: rgb(64, 64, 64)}"
                                    "QPushButton:hover {border-radius:8px; background-color: rgba(64, 224, 192, 0.5); color: rgb(64, 64, 64)}"
                                    "QPushButton:pressed {border-radius:8px; background-color: rgba(32, 192, 160, 0.5); color: rgb(64, 64, 64)}"
                                    "QPushButton:checked {border-radius:8px; background-color: rgba(32, 192, 160, 0.5); color: rgb(64, 64, 64)}");
    page3_gameblock9->setStyleSheet("QPushButton {border-radius:8px; background-color: rgba(96, 255, 224, 0.5); color: rgb(64, 64, 64)}"
                                    "QPushButton:hover {border-radius:8px; background-color: rgba(64, 224, 192, 0.5); color: rgb(64, 64, 64)}"
                                    "QPushButton:pressed {border-radius:8px; background-color: rgba(32, 192, 160, 0.5); color: rgb(64, 64, 64)}"
                                    "QPushButton:checked {border-radius:8px; background-color: rgba(32, 192, 160, 0.5); color: rgb(64, 64, 64)}");
    page3_gameblock10->setStyleSheet("QPushButton {border-radius:8px; background-color: rgba(96, 255, 224, 0.5); color: rgb(64, 64, 64)}"
                                     "QPushButton:hover {border-radius:8px; background-color: rgba(64, 224, 192, 0.5); color: rgb(64, 64, 64)}"
                                     "QPushButton:pressed {border-radius:8px; background-color: rgba(32, 192, 160, 0.5); color: rgb(64, 64, 64)}"
                                     "QPushButton:checked {border-radius:8px; background-color: rgba(32, 192, 160, 0.5); color: rgb(64, 64, 64)}");
    page3_gameblock11->setStyleSheet("QPushButton {border-radius:8px; background-color: rgba(96, 255, 224, 0.5); color: rgb(64, 64, 64)}"
                                     "QPushButton:hover {border-radius:8px; background-color: rgba(64, 224, 192, 0.5); color: rgb(64, 64, 64)}"
                                     "QPushButton:pressed {border-radius:8px; background-color: rgba(32, 192, 160, 0.5); color: rgb(64, 64, 64)}"
                                     "QPushButton:checked {border-radius:8px; background-color: rgba(32, 192, 160, 0.5); color: rgb(64, 64, 64)}");
    page3_gameblock12->setStyleSheet("QPushButton {border-radius:8px; background-color: rgba(96, 255, 224, 0.5); color: rgb(64, 64, 64)}"
                                     "QPushButton:hover {border-radius:8px; background-color: rgba(64, 224, 192, 0.5); color: rgb(64, 64, 64)}"
                                     "QPushButton:pressed {border-radius:8px; background-color: rgba(32, 192, 160, 0.5); color: rgb(64, 64, 64)}"
                                     "QPushButton:checked {border-radius:8px; background-color: rgba(32, 192, 160, 0.5); color: rgb(64, 64, 64)}");
    page3_gameblock13->setStyleSheet("QPushButton {border-radius:8px; background-color: rgba(96, 255, 224, 0.5); color: rgb(64, 64, 64)}"
                                     "QPushButton:hover {border-radius:8px; background-color: rgba(64, 224, 192, 0.5); color: rgb(64, 64, 64)}"
                                     "QPushButton:pressed {border-radius:8px; background-color: rgba(32, 192, 160, 0.5); color: rgb(64, 64, 64)}"
                                     "QPushButton:checked {border-radius:8px; background-color: rgba(32, 192, 160, 0.5); color: rgb(64, 64, 64)}");
    page3_gameblock14->setStyleSheet("QPushButton {border-radius:8px; background-color: rgba(96, 255, 224, 0.5); color: rgb(64, 64, 64)}"
                                     "QPushButton:hover {border-radius:8px; background-color: rgba(64, 224, 192, 0.5); color: rgb(64, 64, 64)}"
                                     "QPushButton:pressed {border-radius:8px; background-color: rgba(32, 192, 160, 0.5); color: rgb(64, 64, 64)}"
                                     "QPushButton:checked {border-radius:8px; background-color: rgba(32, 192, 160, 0.5); color: rgb(64, 64, 64)}");
    page3_gameblock15->setStyleSheet("QPushButton {border-radius:8px; background-color: rgba(96, 255, 224, 0.5); color: rgb(64, 64, 64)}"
                                     "QPushButton:hover {border-radius:8px; background-color: rgba(64, 224, 192, 0.5); color: rgb(64, 64, 64)}"
                                     "QPushButton:pressed {border-radius:8px; background-color: rgba(32, 192, 160, 0.5); color: rgb(64, 64, 64)}"
                                     "QPushButton:checked {border-radius:8px; background-color: rgba(32, 192, 160, 0.5); color: rgb(64, 64, 64)}");
    page3_gameblock16->setStyleSheet("QPushButton {border-radius:8px; background-color: rgba(96, 255, 224, 0.5); color: rgb(64, 64, 64)}"
                                     "QPushButton:hover {border-radius:8px; background-color: rgba(64, 224, 192, 0.5); color: rgb(64, 64, 64)}"
                                     "QPushButton:pressed {border-radius:8px; background-color: rgba(32, 192, 160, 0.5); color: rgb(64, 64, 64)}"
                                     "QPushButton:checked {border-radius:8px; background-color: rgba(32, 192, 160, 0.5); color: rgb(64, 64, 64)}");

    page3_gameblock1->setMinimumSize(80, 80);
    page3_gameblock1->setMaximumSize(80, 80);
    page3_gameblock2->setMinimumSize(80, 80);
    page3_gameblock2->setMaximumSize(80, 80);
    page3_gameblock3->setMinimumSize(80, 80);
    page3_gameblock3->setMaximumSize(80, 80);
    page3_gameblock4->setMinimumSize(80, 80);
    page3_gameblock4->setMaximumSize(80, 80);
    page3_gameblock5->setMinimumSize(80, 80);
    page3_gameblock5->setMaximumSize(80, 80);
    page3_gameblock6->setMinimumSize(80, 80);
    page3_gameblock6->setMaximumSize(80, 80);
    page3_gameblock7->setMinimumSize(80, 80);
    page3_gameblock7->setMaximumSize(80, 80);
    page3_gameblock8->setMinimumSize(80, 80);
    page3_gameblock8->setMaximumSize(80, 80);
    page3_gameblock9->setMinimumSize(80, 80);
    page3_gameblock9->setMaximumSize(80, 80);
    page3_gameblock10->setMinimumSize(80, 80);
    page3_gameblock10->setMaximumSize(80, 80);
    page3_gameblock11->setMinimumSize(80, 80);
    page3_gameblock11->setMaximumSize(80, 80);
    page3_gameblock12->setMinimumSize(80, 80);
    page3_gameblock12->setMaximumSize(80, 80);
    page3_gameblock13->setMinimumSize(80, 80);
    page3_gameblock13->setMaximumSize(80, 80);
    page3_gameblock14->setMinimumSize(80, 80);
    page3_gameblock14->setMaximumSize(80, 80);
    page3_gameblock15->setMinimumSize(80, 80);
    page3_gameblock15->setMaximumSize(80, 80);
    page3_gameblock16->setMinimumSize(80, 80);
    page3_gameblock16->setMaximumSize(80, 80);

    page3_inner_page1_gameblocks_layout->setRowStretch(0, 1);
    page3_inner_page1_gameblocks_layout->setRowStretch(1, 1);
    page3_inner_page1_gameblocks_layout->setRowStretch(2, 1);
    page3_inner_page1_gameblocks_layout->setRowStretch(3, 1);

    page3_inner_page1_gameblocks_layout->setColumnStretch(0, 1);
    page3_inner_page1_gameblocks_layout->setColumnStretch(0, 1);
    page3_inner_page1_gameblocks_layout->setColumnStretch(0, 1);
    page3_inner_page1_gameblocks_layout->setColumnStretch(0, 1);

    page3_inner_page1_gameblocks_layout->setHorizontalSpacing(10);
    page3_inner_page1_gameblocks_layout->setVerticalSpacing(10);

    page3_inner_page1_gameblocks_layout->addWidget(page3_gameblock1, 0, 0);
    page3_inner_page1_gameblocks_layout->addWidget(page3_gameblock2, 0, 1);
    page3_inner_page1_gameblocks_layout->addWidget(page3_gameblock3, 0, 2);
    page3_inner_page1_gameblocks_layout->addWidget(page3_gameblock4, 0, 3);
    page3_inner_page1_gameblocks_layout->addWidget(page3_gameblock5, 1, 0);
    page3_inner_page1_gameblocks_layout->addWidget(page3_gameblock6, 1, 1);
    page3_inner_page1_gameblocks_layout->addWidget(page3_gameblock7, 1, 2);
    page3_inner_page1_gameblocks_layout->addWidget(page3_gameblock8, 1, 3);
    page3_inner_page1_gameblocks_layout->addWidget(page3_gameblock9, 2, 0);
    page3_inner_page1_gameblocks_layout->addWidget(page3_gameblock10, 2, 1);
    page3_inner_page1_gameblocks_layout->addWidget(page3_gameblock11, 2, 2);
    page3_inner_page1_gameblocks_layout->addWidget(page3_gameblock12, 2, 3);
    page3_inner_page1_gameblocks_layout->addWidget(page3_gameblock13, 3, 0);
    page3_inner_page1_gameblocks_layout->addWidget(page3_gameblock14, 3, 1);
    page3_inner_page1_gameblocks_layout->addWidget(page3_gameblock15, 3, 2);
    page3_inner_page1_gameblocks_layout->addWidget(page3_gameblock16, 3, 3);

    /// page3_gameblock 设置随机生成的 4 组满足24点的数字
    page3_random_24numbers_key1 = generateRandomInt10();
    page3_random_24numbers_key2 = generateRandomInt10();
    page3_random_24numbers_key3 = generateRandomInt10();
    page3_random_24numbers_key4 = generateRandomInt10();
    std::vector<string> page3_all_random_24numbers_exp = generate24(4, 24, page3_random_24numbers_key1);
    std::vector<std::string> page3_all_random_24numbers = getFirstFourNumericStrings(page3_all_random_24numbers_exp, 4);
    std::vector<string> page3_random_24numbers2_exp = generate24(4, 24, page3_random_24numbers_key2);
    std::vector<std::string> page3_random_24numbers2 = getFirstFourNumericStrings(page3_random_24numbers2_exp, 4);
    std::vector<string> page3_random_24numbers3_exp = generate24(4, 24, page3_random_24numbers_key3);
    std::vector<std::string> page3_random_24numbers3 = getFirstFourNumericStrings(page3_random_24numbers3_exp, 4);
    std::vector<string> page3_random_24numbers4_exp = generate24(4, 24, page3_random_24numbers_key4);
    std::vector<std::string> page3_random_24numbers4 = getFirstFourNumericStrings(page3_random_24numbers4_exp, 4);

    page3_all_random_24numbers.insert(page3_all_random_24numbers.end(), page3_random_24numbers2.begin(), page3_random_24numbers2.end());
    page3_all_random_24numbers.insert(page3_all_random_24numbers.end(), page3_random_24numbers3.begin(), page3_random_24numbers3.end());
    page3_all_random_24numbers.insert(page3_all_random_24numbers.end(), page3_random_24numbers4.begin(), page3_random_24numbers4.end());

    /// 在命令行输出答案（不然太难了写不出来，不方便演示）
    for (auto& dot: page3_all_random_24numbers){
        std::cout<< dot<<endl;
    }
    std::cout << "\n" <<endl;
    std::random_shuffle(page3_all_random_24numbers.begin(), page3_all_random_24numbers.end());

    /// 在 16 个 blocks 中填入上面生成好的 4 组随机数
    page3_gameblock1->setText(QString::fromStdString(page3_all_random_24numbers[0]));
    page3_gameblock2->setText(QString::fromStdString(page3_all_random_24numbers[1]));
    page3_gameblock3->setText(QString::fromStdString(page3_all_random_24numbers[2]));
    page3_gameblock4->setText(QString::fromStdString(page3_all_random_24numbers[3]));
    page3_gameblock5->setText(QString::fromStdString(page3_all_random_24numbers[4]));
    page3_gameblock6->setText(QString::fromStdString(page3_all_random_24numbers[5]));
    page3_gameblock7->setText(QString::fromStdString(page3_all_random_24numbers[6]));
    page3_gameblock8->setText(QString::fromStdString(page3_all_random_24numbers[7]));
    page3_gameblock9->setText(QString::fromStdString(page3_all_random_24numbers[8]));
    page3_gameblock10->setText(QString::fromStdString(page3_all_random_24numbers[9]));
    page3_gameblock11->setText(QString::fromStdString(page3_all_random_24numbers[10]));
    page3_gameblock12->setText(QString::fromStdString(page3_all_random_24numbers[11]));
    page3_gameblock13->setText(QString::fromStdString(page3_all_random_24numbers[12]));
    page3_gameblock14->setText(QString::fromStdString(page3_all_random_24numbers[13]));
    page3_gameblock15->setText(QString::fromStdString(page3_all_random_24numbers[14]));
    page3_gameblock16->setText(QString::fromStdString(page3_all_random_24numbers[15]));

    page3_gameblock1->setFont(buttonfont);
    page3_gameblock2->setFont(buttonfont);
    page3_gameblock3->setFont(buttonfont);
    page3_gameblock4->setFont(buttonfont);
    page3_gameblock5->setFont(buttonfont);
    page3_gameblock6->setFont(buttonfont);
    page3_gameblock7->setFont(buttonfont);
    page3_gameblock8->setFont(buttonfont);
    page3_gameblock9->setFont(buttonfont);
    page3_gameblock10->setFont(buttonfont);
    page3_gameblock11->setFont(buttonfont);
    page3_gameblock12->setFont(buttonfont);
    page3_gameblock13->setFont(buttonfont);
    page3_gameblock14->setFont(buttonfont);
    page3_gameblock15->setFont(buttonfont);
    page3_gameblock16->setFont(buttonfont);

    page3_game_blocks->addButton(page3_gameblock1, 1);
    page3_game_blocks->addButton(page3_gameblock2, 2);
    page3_game_blocks->addButton(page3_gameblock3, 3);
    page3_game_blocks->addButton(page3_gameblock4, 4);
    page3_game_blocks->addButton(page3_gameblock5, 5);
    page3_game_blocks->addButton(page3_gameblock6, 6);
    page3_game_blocks->addButton(page3_gameblock7, 7);
    page3_game_blocks->addButton(page3_gameblock8, 8);
    page3_game_blocks->addButton(page3_gameblock9, 9);
    page3_game_blocks->addButton(page3_gameblock10, 10);
    page3_game_blocks->addButton(page3_gameblock11, 11);
    page3_game_blocks->addButton(page3_gameblock12, 12);
    page3_game_blocks->addButton(page3_gameblock13, 13);
    page3_game_blocks->addButton(page3_gameblock14, 14);
    page3_game_blocks->addButton(page3_gameblock15, 15);
    page3_game_blocks->addButton(page3_gameblock16, 16);
    page3_game_blocks->setExclusive(false);

    game_blocks_count = 0;


    connect(page3_gameblock1, &QPushButton::clicked, [=](){
        if (!page3_gameblock1_clicked && game_blocks_count!=4){
            // page3_gameblock1->setText("被选中辣");
            game_blocks_count += 1;
            page3_gameblock1_clicked = !page3_gameblock1_clicked;


            string numstr1 = page3_gameblock1->text().toStdString();
            double num1 = (double)stoi(numstr1);
            page3_game_numberstore.push_back(num1);

            if (page3_game_numberstore.size()==4){
                std::vector<std::string> expressions;
                expressions.clear();
                for (int i = 0; i < 4; i++) {
                    expressions.push_back(std::to_string(page3_game_numberstore[i]));//字符串向量初始化
                }
                int VOLUE =24;
                Result result_2=Find(page3_game_numberstore, expressions, 4, VOLUE);
                if (result_2.isPossible){
                    // 如果能构成24
                    QList<QAbstractButton*> game_blocks = page3_game_blocks->buttons();
                    for (QAbstractButton *block: game_blocks){
                        if (block->isChecked()) {
                            // block->setChecked(false);
                            block->hide();
                        }
                    }
                    game_blocks_count = 0;
                    page3_game_numberstore.clear();

                    int destroyed_block_num = countHiddenButtons(page3_game_blocks);
                    if (destroyed_block_num == 16){
                        page3_inner_pages->setCurrentIndex(2);
                    }
                }
            }
        }
        else if (!page3_gameblock1_clicked && game_blocks_count==4){
            page3_gameblock1->setChecked(false);
        }
        else{
            // page3_gameblock1->setText("取消选中辣");

            game_blocks_count -= 1;
            page3_gameblock1_clicked = !page3_gameblock1_clicked;

            string numstr1 = page3_gameblock1->text().toStdString();
            double num1 = (double)stoi(numstr1);
            auto it = std::find(page3_game_numberstore.begin(), page3_game_numberstore.end(), num1);
            if (it != page3_game_numberstore.end()){
                page3_game_numberstore.erase(it);
            }
        }

    });

    connect(page3_gameblock2, &QPushButton::clicked, [=](){
        if (!page3_gameblock2_clicked && game_blocks_count!=4){
            // page3_gameblock2->setText("被选中辣");
            game_blocks_count += 1;
            page3_gameblock2_clicked = !page3_gameblock2_clicked;

            string numstr1 = page3_gameblock2->text().toStdString();
            double num1 = (double)stoi(numstr1);
            page3_game_numberstore.push_back(num1);

            if (page3_game_numberstore.size()==4){
                std::vector<std::string> expressions;
                expressions.clear();
                for (int i = 0; i < 4; i++) {
                    expressions.push_back(std::to_string(page3_game_numberstore[i]));//字符串向量初始化
                }
                int VOLUE =24;
                Result result_2=Find(page3_game_numberstore, expressions, 4, VOLUE);
                if (result_2.isPossible){
                    // 如果能构成24
                    QList<QAbstractButton*> game_blocks = page3_game_blocks->buttons();
                    for (QAbstractButton *block: game_blocks){
                        if (block->isChecked()) {
                            // block->setChecked(false);
                            block->hide();
                        }
                    }
                    game_blocks_count = 0;
                    page3_game_numberstore.clear();

                    int destroyed_block_num = countHiddenButtons(page3_game_blocks);
                    if (destroyed_block_num == 16){
                        page3_inner_pages->setCurrentIndex(2);
                    }
                }
            }
        }
        else if (!page3_gameblock2_clicked && game_blocks_count==4){
            page3_gameblock2->setChecked(false);
        }
        else{
            // page3_gameblock2->setText("取消选中辣");
            game_blocks_count -= 1;
            page3_gameblock2_clicked = !page3_gameblock2_clicked;

            string numstr1 = page3_gameblock2->text().toStdString();
            double num1 = (double)stoi(numstr1);
            auto it = std::find(page3_game_numberstore.begin(), page3_game_numberstore.end(), num1);
            if (it != page3_game_numberstore.end()){
                page3_game_numberstore.erase(it);
            }
        }

    });

    connect(page3_gameblock3, &QPushButton::clicked, [=](){
        if (!page3_gameblock3_clicked && game_blocks_count!=4){
            // page3_gameblock3->setText("被选中辣");
            game_blocks_count += 1;
            page3_gameblock3_clicked = !page3_gameblock3_clicked;

            string numstr1 = page3_gameblock3->text().toStdString();
            double num1 = (double)stoi(numstr1);
            page3_game_numberstore.push_back(num1);

            if (page3_game_numberstore.size()==4){
                std::vector<std::string> expressions;
                expressions.clear();
                for (int i = 0; i < 4; i++) {
                    expressions.push_back(std::to_string(page3_game_numberstore[i]));//字符串向量初始化
                }
                int VOLUE =24;
                Result result_2=Find(page3_game_numberstore, expressions, 4, VOLUE);
                if (result_2.isPossible){
                    // 如果能构成24
                    QList<QAbstractButton*> game_blocks = page3_game_blocks->buttons();
                    for (QAbstractButton *block: game_blocks){
                        if (block->isChecked()) {
                            // block->setChecked(false);
                            block->hide();
                        }
                    }
                    game_blocks_count = 0;
                    page3_game_numberstore.clear();

                    int destroyed_block_num = countHiddenButtons(page3_game_blocks);
                    if (destroyed_block_num == 16){
                        page3_inner_pages->setCurrentIndex(2);
                    }
                }
            }
        }
        else if (!page3_gameblock3_clicked && game_blocks_count==4){
            page3_gameblock3->setChecked(false);
        }
        else{
            // page3_gameblock3->setText("取消选中辣");
            game_blocks_count -= 1;
            page3_gameblock3_clicked = !page3_gameblock3_clicked;

            string numstr1 = page3_gameblock3->text().toStdString();
            double num1 = (double)stoi(numstr1);
            auto it = std::find(page3_game_numberstore.begin(), page3_game_numberstore.end(), num1);
            if (it != page3_game_numberstore.end()){
                page3_game_numberstore.erase(it);
            }
        }

    });

    connect(page3_gameblock4, &QPushButton::clicked, [=](){
        if (!page3_gameblock4_clicked && game_blocks_count!=4){
            // page3_gameblock4->setText("被选中辣");
            game_blocks_count += 1;
            page3_gameblock4_clicked = !page3_gameblock4_clicked;

            string numstr1 = page3_gameblock4->text().toStdString();
            double num1 = (double)stoi(numstr1);
            page3_game_numberstore.push_back(num1);

            if (page3_game_numberstore.size()==4){
                std::vector<std::string> expressions;
                expressions.clear();
                for (int i = 0; i < 4; i++) {
                    expressions.push_back(std::to_string(page3_game_numberstore[i]));//字符串向量初始化
                }
                int VOLUE =24;
                Result result_2=Find(page3_game_numberstore, expressions, 4, VOLUE);
                if (result_2.isPossible){
                    // 如果能构成24
                    QList<QAbstractButton*> game_blocks = page3_game_blocks->buttons();
                    for (QAbstractButton *block: game_blocks){
                        if (block->isChecked()) {
                            // block->setChecked(false);
                            block->hide();
                        }
                    }
                    game_blocks_count = 0;
                    page3_game_numberstore.clear();

                    int destroyed_block_num = countHiddenButtons(page3_game_blocks);
                    if (destroyed_block_num == 16){
                        page3_inner_pages->setCurrentIndex(2);
                    }
                }
            }
        }
        else if (!page3_gameblock4_clicked && game_blocks_count==4){
            page3_gameblock4->setChecked(false);
        }
        else{
            // page3_gameblock4->setText("取消选中辣");
            game_blocks_count -= 1;
            page3_gameblock4_clicked = !page3_gameblock4_clicked;

            string numstr1 = page3_gameblock4->text().toStdString();
            double num1 = (double)stoi(numstr1);
            auto it = std::find(page3_game_numberstore.begin(), page3_game_numberstore.end(), num1);
            if (it != page3_game_numberstore.end()){
                page3_game_numberstore.erase(it);
            }
        }
    });

    connect(page3_gameblock5, &QPushButton::clicked, [=](){
        if (!page3_gameblock5_clicked && game_blocks_count!=4){
            // page3_gameblock5->setText("被选中辣");
            game_blocks_count += 1;
            page3_gameblock5_clicked = !page3_gameblock5_clicked;

            string numstr1 = page3_gameblock5->text().toStdString();
            double num1 = (double)stoi(numstr1);
            page3_game_numberstore.push_back(num1);

            if (page3_game_numberstore.size()==4){
                std::vector<std::string> expressions;
                expressions.clear();
                for (int i = 0; i < 4; i++) {
                    expressions.push_back(std::to_string(page3_game_numberstore[i]));//字符串向量初始化
                }
                int VOLUE =24;
                Result result_2=Find(page3_game_numberstore, expressions, 4, VOLUE);
                if (result_2.isPossible){
                    // 如果能构成24
                    QList<QAbstractButton*> game_blocks = page3_game_blocks->buttons();
                    for (QAbstractButton *block: game_blocks){
                        if (block->isChecked()) {
                            // block->setChecked(false);
                            block->hide();
                        }
                    }
                    game_blocks_count = 0;
                    page3_game_numberstore.clear();

                    int destroyed_block_num = countHiddenButtons(page3_game_blocks);
                    if (destroyed_block_num == 16){
                        page3_inner_pages->setCurrentIndex(2);
                    }
                }
            }
        }
        else if (!page3_gameblock5_clicked && game_blocks_count==4){
            page3_gameblock5->setChecked(false);
        }
        else{
            // page3_gameblock5->setText("取消选中辣");
            game_blocks_count -= 1;
            page3_gameblock5_clicked = !page3_gameblock5_clicked;

            string numstr1 = page3_gameblock5->text().toStdString();
            double num1 = (double)stoi(numstr1);
            auto it = std::find(page3_game_numberstore.begin(), page3_game_numberstore.end(), num1);
            if (it != page3_game_numberstore.end()){
                page3_game_numberstore.erase(it);
            }
        }

    });

    connect(page3_gameblock6, &QPushButton::clicked, [=](){
        if (!page3_gameblock6_clicked && game_blocks_count!=4){
            // page3_gameblock6->setText("被选中辣");
            game_blocks_count += 1;
            page3_gameblock6_clicked = !page3_gameblock6_clicked;

            string numstr1 = page3_gameblock6->text().toStdString();
            double num1 = (double)stoi(numstr1);
            page3_game_numberstore.push_back(num1);

            if (page3_game_numberstore.size()==4){
                std::vector<std::string> expressions;
                expressions.clear();
                for (int i = 0; i < 4; i++) {
                    expressions.push_back(std::to_string(page3_game_numberstore[i]));//字符串向量初始化
                }
                int VOLUE =24;
                Result result_2=Find(page3_game_numberstore, expressions, 4, VOLUE);
                if (result_2.isPossible){
                    // 如果能构成24
                    QList<QAbstractButton*> game_blocks = page3_game_blocks->buttons();
                    for (QAbstractButton *block: game_blocks){
                        if (block->isChecked()) {
                            // block->setChecked(false);
                            block->hide();
                        }
                    }
                    game_blocks_count = 0;
                    page3_game_numberstore.clear();

                    int destroyed_block_num = countHiddenButtons(page3_game_blocks);
                    if (destroyed_block_num == 16){
                        page3_inner_pages->setCurrentIndex(2);
                    }
                }
            }
        }
        else if (!page3_gameblock6_clicked && game_blocks_count==4){
            page3_gameblock6->setChecked(false);
        }
        else{
            // page3_gameblock6->setText("取消选中辣");
            game_blocks_count -= 1;
            page3_gameblock6_clicked = !page3_gameblock6_clicked;

            string numstr1 = page3_gameblock6->text().toStdString();
            double num1 = (double)stoi(numstr1);
            auto it = std::find(page3_game_numberstore.begin(), page3_game_numberstore.end(), num1);
            if (it != page3_game_numberstore.end()){
                page3_game_numberstore.erase(it);
            }
        }

    });

    /// 消消乐模式第七个消除按钮点击事件处理
    connect(page3_gameblock7, &QPushButton::clicked, [=](){
        if (!page3_gameblock7_clicked && game_blocks_count!=4){
            // page3_gameblock7->setText("被选中辣");
            game_blocks_count += 1;
            page3_gameblock7_clicked = !page3_gameblock7_clicked;

            string numstr1 = page3_gameblock7->text().toStdString();
            double num1 = (double)stoi(numstr1);
            page3_game_numberstore.push_back(num1);

            if (page3_game_numberstore.size()==4){
                std::vector<std::string> expressions;
                expressions.clear();
                for (int i = 0; i < 4; i++) {
                    expressions.push_back(std::to_string(page3_game_numberstore[i]));//字符串向量初始化
                }
                int VOLUE =24;
                Result result_2=Find(page3_game_numberstore, expressions, 4, VOLUE);
                if (result_2.isPossible){
                    // 如果能构成24
                    QList<QAbstractButton*> game_blocks = page3_game_blocks->buttons();
                    for (QAbstractButton *block: game_blocks){
                        if (block->isChecked()) {
                            // block->setChecked(false);
                            block->hide();
                        }
                    }
                    game_blocks_count = 0;
                    page3_game_numberstore.clear();

                    int destroyed_block_num = countHiddenButtons(page3_game_blocks);
                    if (destroyed_block_num == 16){
                        page3_inner_pages->setCurrentIndex(2);
                    }
                }
            }
        }
        else if (!page3_gameblock7_clicked && game_blocks_count==4){
            page3_gameblock7->setChecked(false);
        }
        else{
            // page3_gameblock7->setText("取消选中辣");
            game_blocks_count -= 1;
            page3_gameblock7_clicked = !page3_gameblock7_clicked;

            string numstr1 = page3_gameblock7->text().toStdString();
            double num1 = (double)stoi(numstr1);
            auto it = std::find(page3_game_numberstore.begin(), page3_game_numberstore.end(), num1);
            if (it != page3_game_numberstore.end()){
                page3_game_numberstore.erase(it);
            }
        }

    });

    connect(page3_gameblock8, &QPushButton::clicked, [=](){
        if (!page3_gameblock8_clicked && game_blocks_count!=4){
            // page3_gameblock8->setText("被选中辣");
            game_blocks_count += 1;
            page3_gameblock8_clicked = !page3_gameblock8_clicked;

            string numstr1 = page3_gameblock8->text().toStdString();
            double num1 = (double)stoi(numstr1);
            page3_game_numberstore.push_back(num1);

            if (page3_game_numberstore.size()==4){
                std::vector<std::string> expressions;
                expressions.clear();
                for (int i = 0; i < 4; i++) {
                    expressions.push_back(std::to_string(page3_game_numberstore[i]));//字符串向量初始化
                }
                int VOLUE =24;
                Result result_2=Find(page3_game_numberstore, expressions, 4, VOLUE);
                if (result_2.isPossible){
                    // 如果能构成24
                    QList<QAbstractButton*> game_blocks = page3_game_blocks->buttons();
                    for (QAbstractButton *block: game_blocks){
                        if (block->isChecked()) {
                            // block->setChecked(false);
                            block->hide();
                        }
                    }
                    game_blocks_count = 0;
                    page3_game_numberstore.clear();

                    int destroyed_block_num = countHiddenButtons(page3_game_blocks);
                    if (destroyed_block_num == 16){
                        page3_inner_pages->setCurrentIndex(2);
                    }
                }
            }
        }
        else if (!page3_gameblock8_clicked && game_blocks_count==4){
            page3_gameblock8->setChecked(false);
        }
        else{
            // page3_gameblock8->setText("取消选中辣");
            game_blocks_count -= 1;
            page3_gameblock8_clicked = !page3_gameblock8_clicked;

            string numstr1 = page3_gameblock8->text().toStdString();
            double num1 = (double)stoi(numstr1);
            auto it = std::find(page3_game_numberstore.begin(), page3_game_numberstore.end(), num1);
            if (it != page3_game_numberstore.end()){
                page3_game_numberstore.erase(it);
            }
        }

    });

    connect(page3_gameblock9, &QPushButton::clicked, [=](){
        if (!page3_gameblock9_clicked && game_blocks_count!=4){
            // page3_gameblock9->setText("被选中辣");
            game_blocks_count += 1;
            page3_gameblock9_clicked = !page3_gameblock9_clicked;

            string numstr1 = page3_gameblock9->text().toStdString();
            double num1 = (double)stoi(numstr1);
            page3_game_numberstore.push_back(num1);

            if (page3_game_numberstore.size()==4){
                std::vector<std::string> expressions;
                expressions.clear();
                for (int i = 0; i < 4; i++) {
                    expressions.push_back(std::to_string(page3_game_numberstore[i]));//字符串向量初始化
                }
                int VOLUE =24;
                Result result_2=Find(page3_game_numberstore, expressions, 4, VOLUE);
                if (result_2.isPossible){
                    // 如果能构成24
                    QList<QAbstractButton*> game_blocks = page3_game_blocks->buttons();
                    for (QAbstractButton *block: game_blocks){
                        if (block->isChecked()) {
                            // block->setChecked(false);
                            block->hide();
                        }
                    }
                    game_blocks_count = 0;
                    page3_game_numberstore.clear();

                    int destroyed_block_num = countHiddenButtons(page3_game_blocks);
                    if (destroyed_block_num == 16){
                        page3_inner_pages->setCurrentIndex(2);
                    }
                }
            }
        }
        else if (!page3_gameblock9_clicked && game_blocks_count==4){
            page3_gameblock9->setChecked(false);
        }
        else{
            // page3_gameblock9->setText("取消选中辣");
            game_blocks_count -= 1;
            page3_gameblock9_clicked = !page3_gameblock9_clicked;

            string numstr1 = page3_gameblock9->text().toStdString();
            double num1 = (double)stoi(numstr1);
            auto it = std::find(page3_game_numberstore.begin(), page3_game_numberstore.end(), num1);
            if (it != page3_game_numberstore.end()){
                page3_game_numberstore.erase(it);
            }
        }

    });

    connect(page3_gameblock10, &QPushButton::clicked, [=](){
        if (!page3_gameblock10_clicked && game_blocks_count!=4){
            // page3_gameblock10->setText("被选中辣");
            game_blocks_count += 1;
            page3_gameblock10_clicked = !page3_gameblock10_clicked;

            string numstr1 = page3_gameblock10->text().toStdString();
            double num1 = (double)stoi(numstr1);
            page3_game_numberstore.push_back(num1);

            if (page3_game_numberstore.size()==4){
                std::vector<std::string> expressions;
                expressions.clear();
                for (int i = 0; i < 4; i++) {
                    expressions.push_back(std::to_string(page3_game_numberstore[i]));//字符串向量初始化
                }
                int VOLUE =24;
                Result result_2=Find(page3_game_numberstore, expressions, 4, VOLUE);
                if (result_2.isPossible){
                    // 如果能构成24
                    QList<QAbstractButton*> game_blocks = page3_game_blocks->buttons();
                    for (QAbstractButton *block: game_blocks){
                        if (block->isChecked()) {
                            // block->setChecked(false);
                            block->hide();
                        }
                    }
                    game_blocks_count = 0;
                    page3_game_numberstore.clear();

                    int destroyed_block_num = countHiddenButtons(page3_game_blocks);
                    if (destroyed_block_num == 16){
                        page3_inner_pages->setCurrentIndex(2);
                    }
                }
            }
        }
        else if (!page3_gameblock10_clicked && game_blocks_count==4){
            page3_gameblock10->setChecked(false);
        }
        else{
            // page3_gameblock10->setText("取消选中辣");
            game_blocks_count -= 1;
            page3_gameblock10_clicked = !page3_gameblock10_clicked;

            string numstr1 = page3_gameblock10->text().toStdString();
            double num1 = (double)stoi(numstr1);
            auto it = std::find(page3_game_numberstore.begin(), page3_game_numberstore.end(), num1);
            if (it != page3_game_numberstore.end()){
                page3_game_numberstore.erase(it);
            }
        }

    });

    connect(page3_gameblock11, &QPushButton::clicked, [=](){
        if (!page3_gameblock11_clicked && game_blocks_count!=4){
            // page3_gameblock11->setText("被选中辣");
            game_blocks_count += 1;
            page3_gameblock11_clicked = !page3_gameblock11_clicked;

            string numstr1 = page3_gameblock11->text().toStdString();
            double num1 = (double)stoi(numstr1);
            page3_game_numberstore.push_back(num1);

            if (page3_game_numberstore.size()==4){
                std::vector<std::string> expressions;
                expressions.clear();
                for (int i = 0; i < 4; i++) {
                    expressions.push_back(std::to_string(page3_game_numberstore[i]));//字符串向量初始化
                }
                int VOLUE =24;
                Result result_2=Find(page3_game_numberstore, expressions, 4, VOLUE);
                if (result_2.isPossible){
                    // 如果能构成24
                    QList<QAbstractButton*> game_blocks = page3_game_blocks->buttons();
                    for (QAbstractButton *block: game_blocks){
                        if (block->isChecked()) {
                            // block->setChecked(false);
                            block->hide();
                        }
                    }
                    game_blocks_count = 0;
                    page3_game_numberstore.clear();

                    int destroyed_block_num = countHiddenButtons(page3_game_blocks);
                    if (destroyed_block_num == 16){
                        page3_inner_pages->setCurrentIndex(2);
                    }
                }
            }
        }
        else if (!page3_gameblock11_clicked && game_blocks_count==4){
            page3_gameblock11->setChecked(false);
        }
        else{
            // page3_gameblock11->setText("取消选中辣");
            game_blocks_count -= 1;
            page3_gameblock11_clicked = !page3_gameblock11_clicked;

            string numstr1 = page3_gameblock11->text().toStdString();
            double num1 = (double)stoi(numstr1);
            auto it = std::find(page3_game_numberstore.begin(), page3_game_numberstore.end(), num1);
            if (it != page3_game_numberstore.end()){
                page3_game_numberstore.erase(it);
            }
        }

    });

    connect(page3_gameblock12, &QPushButton::clicked, [=](){
        if (!page3_gameblock12_clicked && game_blocks_count!=4){
            // page3_gameblock12->setText("被选中辣");
            game_blocks_count += 1;
            page3_gameblock12_clicked = !page3_gameblock12_clicked;

            string numstr1 = page3_gameblock12->text().toStdString();
            double num1 = (double)stoi(numstr1);
            page3_game_numberstore.push_back(num1);

            if (page3_game_numberstore.size()==4){
                std::vector<std::string> expressions;
                expressions.clear();
                for (int i = 0; i < 4; i++) {
                    expressions.push_back(std::to_string(page3_game_numberstore[i]));//字符串向量初始化
                }
                int VOLUE =24;
                Result result_2=Find(page3_game_numberstore, expressions, 4, VOLUE);
                if (result_2.isPossible){
                    // 如果能构成24
                    QList<QAbstractButton*> game_blocks = page3_game_blocks->buttons();
                    for (QAbstractButton *block: game_blocks){
                        if (block->isChecked()) {
                            // block->setChecked(false);
                            block->hide();
                        }
                    }
                    game_blocks_count = 0;
                    page3_game_numberstore.clear();

                    int destroyed_block_num = countHiddenButtons(page3_game_blocks);
                    if (destroyed_block_num == 16){
                        page3_inner_pages->setCurrentIndex(2);
                    }
                }
            }
        }
        else if (!page3_gameblock12_clicked && game_blocks_count==4){
            page3_gameblock12->setChecked(false);
        }
        else{
            // page3_gameblock12->setText("取消选中辣");
            game_blocks_count -= 1;
            page3_gameblock12_clicked = !page3_gameblock12_clicked;

            string numstr1 = page3_gameblock12->text().toStdString();
            double num1 = (double)stoi(numstr1);
            auto it = std::find(page3_game_numberstore.begin(), page3_game_numberstore.end(), num1);
            if (it != page3_game_numberstore.end()){
                page3_game_numberstore.erase(it);
            }
        }
    });

    connect(page3_gameblock13, &QPushButton::clicked, [=](){
        if (!page3_gameblock13_clicked && game_blocks_count!=4){
            // page3_gameblock13->setText("被选中辣");
            game_blocks_count += 1;
            page3_gameblock13_clicked = !page3_gameblock13_clicked;

            string numstr1 = page3_gameblock13->text().toStdString();
            double num1 = (double)stoi(numstr1);
            page3_game_numberstore.push_back(num1);

            if (page3_game_numberstore.size()==4){
                std::vector<std::string> expressions;
                expressions.clear();
                for (int i = 0; i < 4; i++) {
                    expressions.push_back(std::to_string(page3_game_numberstore[i]));//字符串向量初始化
                }
                int VOLUE =24;
                Result result_2=Find(page3_game_numberstore, expressions, 4, VOLUE);
                if (result_2.isPossible){
                    // 如果能构成24
                    QList<QAbstractButton*> game_blocks = page3_game_blocks->buttons();
                    for (QAbstractButton *block: game_blocks){
                        if (block->isChecked()) {
                            // block->setChecked(false);
                            block->hide();
                        }
                    }
                    game_blocks_count = 0;
                    page3_game_numberstore.clear();

                    int destroyed_block_num = countHiddenButtons(page3_game_blocks);
                    if (destroyed_block_num == 16){
                        page3_inner_pages->setCurrentIndex(2);
                    }
                }
            }
        }
        else if (!page3_gameblock13_clicked && game_blocks_count==4){
            page3_gameblock13->setChecked(false);
        }
        else{
            // page3_gameblock13->setText("取消选中辣");
            game_blocks_count -= 1;
            page3_gameblock13_clicked = !page3_gameblock13_clicked;

            string numstr1 = page3_gameblock13->text().toStdString();
            double num1 = (double)stoi(numstr1);
            auto it = std::find(page3_game_numberstore.begin(), page3_game_numberstore.end(), num1);
            if (it != page3_game_numberstore.end()){
                page3_game_numberstore.erase(it);
            }
        }
    });

    connect(page3_gameblock14, &QPushButton::clicked, [=](){
        if (!page3_gameblock14_clicked && game_blocks_count!=4){
            // page3_gameblock14->setText("被选中辣");
            game_blocks_count += 1;
            page3_gameblock14_clicked = !page3_gameblock14_clicked;

            string numstr1 = page3_gameblock14->text().toStdString();
            double num1 = (double)stoi(numstr1);
            page3_game_numberstore.push_back(num1);

            if (page3_game_numberstore.size()==4){
                std::vector<std::string> expressions;
                expressions.clear();
                for (int i = 0; i < 4; i++) {
                    expressions.push_back(std::to_string(page3_game_numberstore[i]));//字符串向量初始化
                }
                int VOLUE =24;
                Result result_2=Find(page3_game_numberstore, expressions, 4, VOLUE);
                if (result_2.isPossible){
                    // 如果能构成24
                    QList<QAbstractButton*> game_blocks = page3_game_blocks->buttons();
                    for (QAbstractButton *block: game_blocks){
                        if (block->isChecked()) {
                            block->setChecked(false);
                            block->hide();
                        }
                    }
                    game_blocks_count = 0;
                    page3_game_numberstore.clear();

                    int destroyed_block_num = countHiddenButtons(page3_game_blocks);
                    if (destroyed_block_num == 16){
                        page3_inner_pages->setCurrentIndex(2);
                    }
                }
            }
        }
        else if (!page3_gameblock14_clicked && game_blocks_count==4){
            page3_gameblock14->setChecked(false);
        }
        else{
            // page3_gameblock14->setText("取消选中辣");
            game_blocks_count -= 1;
            page3_gameblock14_clicked = !page3_gameblock14_clicked;

            string numstr1 = page3_gameblock14->text().toStdString();
            double num1 = (double)stoi(numstr1);
            auto it = std::find(page3_game_numberstore.begin(), page3_game_numberstore.end(), num1);
            if (it != page3_game_numberstore.end()){
                page3_game_numberstore.erase(it);
            }
        }

    });

    connect(page3_gameblock15, &QPushButton::clicked, [=](){
        if (!page3_gameblock15_clicked && game_blocks_count!=4){
            // page3_gameblock15->setText("被选中辣");
            game_blocks_count += 1;
            page3_gameblock15_clicked = !page3_gameblock15_clicked;

            string numstr1 = page3_gameblock15->text().toStdString();
            double num1 = (double)stoi(numstr1);
            page3_game_numberstore.push_back(num1);

            if (page3_game_numberstore.size()==4){
                std::vector<std::string> expressions;
                expressions.clear();
                for (int i = 0; i < 4; i++) {
                    expressions.push_back(std::to_string(page3_game_numberstore[i]));//字符串向量初始化
                }
                int VOLUE =24;
                Result result_2=Find(page3_game_numberstore, expressions, 4, VOLUE);
                if (result_2.isPossible){
                    // 如果能构成24
                    QList<QAbstractButton*> game_blocks = page3_game_blocks->buttons();
                    for (QAbstractButton *block: game_blocks){
                        if (block->isChecked()) {
                            block->setChecked(false);
                            block->hide();
                        }
                    }
                    game_blocks_count = 0;
                    page3_game_numberstore.clear();

                    int destroyed_block_num = countHiddenButtons(page3_game_blocks);
                    if (destroyed_block_num == 16){
                        page3_inner_pages->setCurrentIndex(2);
                    }
                }
            }
        }
        else if (!page3_gameblock15_clicked && game_blocks_count==4){
            page3_gameblock15->setChecked(false);
        }
        else{
            // page3_gameblock15->setText("取消选中辣");
            game_blocks_count -= 1;
            page3_gameblock15_clicked = !page3_gameblock15_clicked;

            string numstr1 = page3_gameblock15->text().toStdString();
            double num1 = (double)stoi(numstr1);
            auto it = std::find(page3_game_numberstore.begin(), page3_game_numberstore.end(), num1);
            if (it != page3_game_numberstore.end()){
                page3_game_numberstore.erase(it);
            }
        }
    });

    connect(page3_gameblock16, &QPushButton::clicked, [=](){
        if (!page3_gameblock16_clicked && game_blocks_count!=4){
            // page3_gameblock16->setText("被选中辣");
            game_blocks_count += 1;
            page3_gameblock16_clicked = !page3_gameblock16_clicked;

            string numstr1 = page3_gameblock16->text().toStdString();
            double num1 = (double)stoi(numstr1);
            page3_game_numberstore.push_back(num1);

            if (page3_game_numberstore.size()==4){
                std::vector<std::string> expressions;
                expressions.clear();
                for (int i = 0; i < 4; i++) {
                    expressions.push_back(std::to_string(page3_game_numberstore[i]));//字符串向量初始化
                }
                int VOLUE =24;
                Result result_2=Find(page3_game_numberstore, expressions, 4, VOLUE);
                if (result_2.isPossible){
                    // 如果能构成24
                    QList<QAbstractButton*> game_blocks = page3_game_blocks->buttons();
                    for (QAbstractButton *block: game_blocks){
                        if (block->isChecked()) {
                            block->setChecked(false);
                            block->hide();
                        }
                    }
                    game_blocks_count = 0;
                    page3_game_numberstore.clear();

                    int destroyed_block_num = countHiddenButtons(page3_game_blocks);
                    if (destroyed_block_num == 16){
                        page3_inner_pages->setCurrentIndex(2);
                    }
                }
            }
        }
        else if (!page3_gameblock16_clicked && game_blocks_count==4){
            page3_gameblock16->setChecked(false);
        }
        else{
            // page3_gameblock16->setText("取消选中辣");
            game_blocks_count -= 1;
            page3_gameblock16_clicked = !page3_gameblock16_clicked;

            string numstr1 = page3_gameblock16->text().toStdString();
            double num1 = (double)stoi(numstr1);
            auto it = std::find(page3_game_numberstore.begin(), page3_game_numberstore.end(), num1);
            if (it != page3_game_numberstore.end()){
                page3_game_numberstore.erase(it);
            }
        }

    });


    page3_inner_page1_rulelayout->addWidget(page3_inner_page1_label0);
    page3_inner_page1_mainlayout->addSpacerItem(page3_inner_page1_mainlayout_leftspacer);
    page3_inner_page1_mainlayout->addLayout(page3_inner_page1_gameblocks_layout);
    page3_inner_page1_mainlayout->addSpacerItem(page3_inner_page1_between_layouts_spacer);
    page3_inner_page1_mainlayout->addLayout(page3_inner_page1_rulelayout);
    page3_inner_page1_mainlayout->addSpacerItem(page3_inner_page1_mainlayout_rightspacer);

    page3_inner_page1_rulelayout->addWidget(page3_inner_page1_startbutton, Qt::AlignCenter);
    page3_inner_page1_rulelayout->addSpacerItem(page3_inner_page1_underbutton_spacer);
    page3_inner_page1_label0->setGeometry(0, 0, 200, 50);
    // page3_inner_page1_label0->setStyleSheet("background-color:black");
    page3_inner_page1_label0->setAlignment(Qt::AlignCenter);
    page3_inner_page1_startbutton->setFixedSize(80, 40);

    connect(page3_inner_page1_startbutton, &QPushButton::clicked, [=](){
        QList<QAbstractButton*> game_blocks = page3_game_blocks->buttons();
        for (QAbstractButton *block: game_blocks){
            block->setChecked(false);
            block->setVisible(true);
        }
        game_blocks_count = 0;
        page3_game_numberstore.clear();
        page3_gameblock1_clicked = false;
        page3_gameblock2_clicked = false;
        page3_gameblock3_clicked = false;
        page3_gameblock4_clicked = false;
        page3_gameblock5_clicked = false;
        page3_gameblock6_clicked = false;
        page3_gameblock7_clicked = false;
        page3_gameblock8_clicked = false;
        page3_gameblock9_clicked = false;
        page3_gameblock10_clicked = false;
        page3_gameblock11_clicked = false;
        page3_gameblock12_clicked = false;
        page3_gameblock13_clicked = false;
        page3_gameblock14_clicked = false;
        page3_gameblock15_clicked = false;
        page3_gameblock16_clicked = false;
        // timer->stop();
        // std::cout << "Elapsed time: " << timer->getElapsedTime().count() << " seconds" << std::endl;
    });


    /// page3结算界面编辑
    QLabel *page3_inner_page2_label0 = new QLabel("用时很少，你真棒！", page3_inner_page2);
    QHBoxLayout *page3_inner_page2_mainlayout = new QHBoxLayout(page3_inner_page2);
    QVBoxLayout *page3_inner_page2_rulelayout = new QVBoxLayout;
    QPushButton *page3_inner_page2_startbutton = new QPushButton("再来一局？");
    QSpacerItem *page3_inner_page2_mainlayout_leftspacer = new QSpacerItem(40, 10, QSizePolicy::Minimum, QSizePolicy::Fixed);
    QSpacerItem *page3_inner_page2_mainlayout_rightspacer = new QSpacerItem(120, 10, QSizePolicy::Minimum, QSizePolicy::Expanding);
    QSpacerItem *page3_inner_page2_underbutton_spacer = new QSpacerItem(10, 120, QSizePolicy::Fixed, QSizePolicy::Minimum);

    page3_inner_page2_rulelayout->addWidget(page3_inner_page2_label0);

    page3_inner_page2_mainlayout->addSpacerItem(page3_inner_page2_mainlayout_leftspacer);
    page3_inner_page2_mainlayout->addLayout(page3_inner_page2_rulelayout);
    page3_inner_page2_mainlayout->addSpacerItem(page3_inner_page2_mainlayout_rightspacer);

    page3_inner_page2_rulelayout->addWidget(page3_inner_page2_startbutton);
    page3_inner_page2_rulelayout->addSpacerItem(page3_inner_page2_underbutton_spacer);
    page3_inner_page2_label0->setGeometry(0, 0, 200, 50);
    page3_inner_page2_label0->setAlignment(Qt::AlignCenter);
    page3_inner_page2_startbutton->setFixedSize(80, 40);

    connect(page3_inner_page2_startbutton, &QPushButton::clicked, [=](){
        page3_inner_pages->setCurrentIndex(1);
    });


    // 杂交模式开发部分
    /// 创建一个VLayout
    QVBoxLayout *page4_main_layout = new QVBoxLayout(ui->page_4);
    /// 顶部加入弹簧
    QSpacerItem *page4_top_spacer = new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Fixed);
    QSpacerItem *page4_between_spacer = new QSpacerItem(10, 50, QSizePolicy::Minimum, QSizePolicy::Expanding);
    QSpacerItem *page4_bottom_spacer = new QSpacerItem(10, 50, QSizePolicy::Minimum, QSizePolicy::Expanding);
    page4_main_layout->addSpacerItem(page4_top_spacer);

    /// 弹簧下面放入页面主标题
    QLabel *hybridization_maintitle = new QLabel(this);
    QLabel *page4_bottom_icon = new QLabel();
    page4_main_layout->addWidget(hybridization_maintitle);
    hybridization_maintitle->setText("杂交模式");
    page4_bottom_icon->setText("<<<");
    ft.setBold(true);
    hybridization_maintitle->setFont(ft);
    page4_bottom_icon->setFont(ft);
    hybridization_maintitle->setGeometry(9, 20, 300, 80);
    page4_bottom_icon->setAlignment(Qt::AlignRight);

    /// 标题下方加入 stack widget（含有3页）
    QStackedWidget *page4_inner_pages = new QStackedWidget;
    page4_main_layout->addSpacerItem(page4_between_spacer);
    page4_main_layout->addWidget(page4_inner_pages);
    page4_main_layout->addSpacerItem(page4_bottom_spacer);
    page4_main_layout->addWidget(page4_bottom_icon);
    QWidget *page4_inner_page0 = new QWidget;
    QWidget *page4_inner_page1 = new QWidget;
    QWidget *page4_inner_page2 = new QWidget;

    page4_inner_pages->addWidget(page4_inner_page0);
    page4_inner_pages->addWidget(page4_inner_page1);
    page4_inner_pages->addWidget(page4_inner_page2);

    /// page4首页编辑
    QLabel *page4_inner_page0_label0 = new QLabel("我是首页", page4_inner_page0);
    QHBoxLayout *page4_inner_page0_mainlayout = new QHBoxLayout(page4_inner_page0);
    QVBoxLayout *page4_inner_page0_rulelayout = new QVBoxLayout;

    QPushButton *page4_inner_page0_startbutton = new QPushButton("Start");

    QSpacerItem *page4_inner_page0_mainlayout_leftspacer = new QSpacerItem(40, 10, QSizePolicy::Minimum, QSizePolicy::Fixed);
    QSpacerItem *page4_inner_page0_mainlayout_rightspacer = new QSpacerItem(120, 10, QSizePolicy::Minimum, QSizePolicy::Expanding);
    QSpacerItem *page4_inner_page0_underbutton_spacer = new QSpacerItem(10, 120, QSizePolicy::Fixed, QSizePolicy::Minimum);

    page4_inner_page0_rulelayout->addWidget(page4_inner_page0_label0);

    page4_inner_page0_mainlayout->addSpacerItem(page4_inner_page0_mainlayout_leftspacer);
    page4_inner_page0_mainlayout->addLayout(page4_inner_page0_rulelayout);
    page4_inner_page0_mainlayout->addSpacerItem(page4_inner_page0_mainlayout_rightspacer);

    page4_inner_page0_rulelayout->addWidget(page4_inner_page0_startbutton);
    page4_inner_page0_rulelayout->addSpacerItem(page4_inner_page0_underbutton_spacer);
    page4_inner_page0_label0->setGeometry(0, 0, 200, 50);
    page4_inner_page0_label0->setAlignment(Qt::AlignCenter);
    page4_inner_page0_startbutton->setFixedSize(80, 40);

    page4_inner_pages->setCurrentIndex(0);
    connect(page4_inner_page0_startbutton, &QPushButton::clicked, [=](){
        page4_inner_pages->setCurrentIndex(1);
    });

    /// page4游戏界面编辑
    QLabel *page4_inner_page1_label0 = new QLabel("我是游戏界面", page4_inner_page1);
    QHBoxLayout *page4_inner_page1_mainlayout = new QHBoxLayout(page4_inner_page1);
    QVBoxLayout *page4_inner_page1_rulelayout = new QVBoxLayout;
    QPushButton *page4_inner_page1_startbutton = new QPushButton("确认？");
    QSpacerItem *page4_inner_page1_mainlayout_leftspacer = new QSpacerItem(40, 10, QSizePolicy::Minimum, QSizePolicy::Fixed);
    QSpacerItem *page4_inner_page1_mainlayout_rightspacer = new QSpacerItem(120, 10, QSizePolicy::Minimum, QSizePolicy::Expanding);
    QSpacerItem *page4_inner_page1_underbutton_spacer = new QSpacerItem(10, 120, QSizePolicy::Fixed, QSizePolicy::Minimum);
    QSpacerItem *page4_inner_page1_mainlayout_bottomspacer = new QSpacerItem(10, 40, QSizePolicy::Fixed, QSizePolicy::Minimum);
    QSpacerItem *page4_inner_page1_uponbutton_spacer = new QSpacerItem(10, 120, QSizePolicy::Fixed, QSizePolicy::Fixed);
    QSpacerItem *page4_inner_page1_between_layouts_spacer = new QSpacerItem(50, 10, QSizePolicy::Minimum, QSizePolicy::Fixed);
    QGridLayout *page4_inner_page1_gameblocks_layout = new QGridLayout;
    QLineEdit *page4_gameblocks0[7];
    QLineEdit *page4_gameblock1 = new QLineEdit("我是方框1", page4_inner_page1);
    QLineEdit *page4_gameblock2 = new QLineEdit("我是方框2", page4_inner_page1);
    QLineEdit *page4_gameblock3 = new QLineEdit("我是方框3", page4_inner_page1);
    QLineEdit *page4_gameblock4 = new QLineEdit("我是方框4", page4_inner_page1);
    QLineEdit *page4_gameblock5 = new QLineEdit("我是方框5", page4_inner_page1);
    QLineEdit *page4_gameblock6 = new QLineEdit("我是方框6", page4_inner_page1);
    QLineEdit *page4_gameblock7 = new QLineEdit("我是方框7", page4_inner_page1);
    page4_gameblocks0[0] = page4_gameblock5;
    page4_gameblocks0[1] = page4_gameblock6;
    page4_gameblocks0[2] = page4_gameblock7;
    page4_gameblocks0[3] = page4_gameblock7;
    page4_gameblocks0[4] = page4_gameblock7;
    page4_gameblocks0[5] = page4_gameblock7;
    page4_gameblocks0[6] = page4_gameblock7;


    // page4_gameblock1->setText("1");
    // page4_gameblock2->setText("2");
    // page4_gameblock3->setText("3");
    // page4_gameblock4->setText("4");
    // page4_gameblock5->setText("4");
    // page4_gameblock6->setText("3");
    // page4_gameblock7->setText("1");

    page4_gameblock1->setReadOnly(true);
    page4_gameblock2->setReadOnly(true);
    page4_gameblock3->setReadOnly(true);
    page4_gameblock4->setReadOnly(true);
    page4_gameblock5->setReadOnly(true);
    page4_gameblock6->setReadOnly(true);
    page4_gameblock7->setReadOnly(true);

    page4_gameblock1->setMinimumSize(80, 80);
    page4_gameblock1->setMaximumSize(80, 80);
    page4_gameblock2->setMinimumSize(80, 80);
    page4_gameblock2->setMaximumSize(80, 80);
    page4_gameblock3->setMinimumSize(80, 80);
    page4_gameblock3->setMaximumSize(80, 80);
    page4_gameblock4->setMinimumSize(80, 80);
    page4_gameblock4->setMaximumSize(80, 80);
    page4_gameblock5->setMinimumSize(80, 80);
    page4_gameblock5->setMaximumSize(80, 80);
    page4_gameblock6->setMinimumSize(80, 80);
    page4_gameblock6->setMaximumSize(80, 80);
    page4_gameblock7->setMinimumSize(80, 80);
    page4_gameblock7->setMaximumSize(80, 80);

    page4_gameblock1->setStyleSheet("border-radius:8px; background-color: rgba(64, 224, 192, 0.5)");
    page4_gameblock2->setStyleSheet("border-radius:8px; background-color: rgba(64, 224, 192, 0.5)");
    page4_gameblock3->setStyleSheet("border-radius:8px; background-color: rgba(64, 224, 192, 0.5)");
    page4_gameblock4->setStyleSheet("border-radius:8px; background-color: rgba(64, 224, 192, 0.5)");
    page4_gameblock5->setStyleSheet("border-radius:8px; background-color: rgba(64, 224, 192, 0.5)");
    page4_gameblock6->setStyleSheet("border-radius:8px; background-color: rgba(64, 224, 192, 0.5)");
    page4_gameblock7->setStyleSheet("border-radius:8px; background-color: rgba(64, 224, 192, 0.5)");

    page4_gameblock1->setFont(buttonfont);
    page4_gameblock2->setFont(buttonfont);
    page4_gameblock3->setFont(buttonfont);
    page4_gameblock4->setFont(buttonfont);
    page4_gameblock5->setFont(buttonfont);
    page4_gameblock6->setFont(buttonfont);
    page4_gameblock7->setFont(buttonfont);

    page4_gameblock1->setAlignment(Qt::AlignCenter);
    page4_gameblock2->setAlignment(Qt::AlignCenter);
    page4_gameblock3->setAlignment(Qt::AlignCenter);
    page4_gameblock4->setAlignment(Qt::AlignCenter);
    page4_gameblock5->setAlignment(Qt::AlignCenter);
    page4_gameblock6->setAlignment(Qt::AlignCenter);
    page4_gameblock7->setAlignment(Qt::AlignCenter);

    /// 随机生成游戏数值
    int random_answer = generateRandomInt10();
    std::cout<<random_answer; 
    string random_answer_string = to_string(random_answer);

    std::vector<std::string> horizontal_line0 = generate24(4, 24, random_answer);
    std::vector<std::string> vertical_line0 = generate24(4, 24, random_answer);

    std::vector<std::string> horizontal_line = getFirstFourNumericStrings(horizontal_line0, 4);
    std::vector<std::string> vertical_line = getFirstFourNumericStrings(vertical_line0, 4);

    // for (int var = 0; var < 3; var++) {
    //     cout << horizontal_line[var] << endl;
    // }

    auto ith = std::find(horizontal_line.begin(), horizontal_line.end(), random_answer_string);
    auto itv = std::find(vertical_line.begin(), vertical_line.end(), random_answer_string);
    int random_col_num = ith - horizontal_line.begin();
    int random_row_num = itv - vertical_line.begin();

    // 插入一行block
    page4_inner_page1_gameblocks_layout->addWidget(page4_gameblock1, random_row_num, 0);
    page4_inner_page1_gameblocks_layout->addWidget(page4_gameblock2, random_row_num, 1);
    page4_inner_page1_gameblocks_layout->addWidget(page4_gameblock3, random_row_num, 2);
    page4_inner_page1_gameblocks_layout->addWidget(page4_gameblock4, random_row_num, 3);

    count_block_num = 0;

    // 插入一列blcok
    for (int i=0; i<3; i += 1){
        if (i!=random_row_num){
            page4_inner_page1_gameblocks_layout->addWidget(page4_gameblocks0[count_block_num], i, random_col_num);
            count_block_num += 1;
        }
    }

    for (int i=0; i<4; i++){
        QLineEdit *currentblock = qobject_cast<QLineEdit*>(page4_inner_page1_gameblocks_layout->itemAtPosition(random_row_num, i)->widget());
        if (currentblock) {
            currentblock->setText(QString::fromStdString(horizontal_line[i]));
        }
    }

    // 设置各个block的内容
    for (int j=0; j<3; j+=1){
        QLineEdit *currentblock = qobject_cast<QLineEdit*>(page4_inner_page1_gameblocks_layout->itemAtPosition(j, random_col_num)->widget());
        if (currentblock) {
            currentblock->setText(QString::fromStdString(vertical_line[j]));//这里当时你用的还是horizontal_line
        }
    }

    QLineEdit *currentblock = qobject_cast<QLineEdit*>(page4_inner_page1_gameblocks_layout->itemAtPosition(random_row_num, random_col_num)->widget());
    if (currentblock) {
        currentblock->setText("");
        currentblock->setReadOnly(false);
        currentblock->setValidator(new QIntValidator(currentblock));
        currentblock->setMaxLength(3);
    }

    // page4_gameblock2->setText("");
    // page4_gameblock2->setValidator(new QIntValidator(page4_gameblock2));
    // page4_gameblock2->setMaxLength(3);



    page4_inner_page1_rulelayout->addWidget(page4_inner_page1_label0);
    page4_inner_page1_mainlayout->addSpacerItem(page4_inner_page1_mainlayout_leftspacer);
    page4_inner_page1_mainlayout->addLayout(page4_inner_page1_gameblocks_layout);
    page4_inner_page1_mainlayout->addSpacerItem(page4_inner_page1_between_layouts_spacer);
    page4_inner_page1_mainlayout->addLayout(page4_inner_page1_rulelayout);
    page4_inner_page1_mainlayout->addSpacerItem(page4_inner_page1_mainlayout_rightspacer);

    page4_inner_page1_rulelayout->addWidget(page4_inner_page1_startbutton, Qt::AlignCenter);
    page4_inner_page1_rulelayout->addSpacerItem(page4_inner_page1_underbutton_spacer);
    page4_inner_page1_label0->setGeometry(0, 0, 200, 50);
    // page3_inner_page1_label0->setStyleSheet("background-color:black");
    page4_inner_page1_label0->setAlignment(Qt::AlignCenter);
    page4_inner_page1_startbutton->setFixedSize(80, 40);

    connect(page4_inner_page1_startbutton, &QPushButton::clicked, [=](){

        QLineEdit *currentblock = qobject_cast<QLineEdit*>(page4_inner_page1_gameblocks_layout->itemAtPosition(random_row_num, random_col_num)->widget());
        if (currentblock) {
            // currentblock->setText(QString::fromStdString(horizontal_line[i]));
            string ans = currentblock->text().toStdString();

            if (ans==random_answer_string){
                page4_inner_pages->setCurrentIndex(2);
                currentblock->setText("");
                page4_inner_page1_label0->setText("我是游戏界面");
            }
            else {
                page4_inner_page1_label0->setText("填错了哦~再试一试？");
            }
        }
    });

    /// page4结算界面编辑
    QLabel *page4_inner_page2_label0 = new QLabel("用时很少，你真棒！", page4_inner_page2);
    QHBoxLayout *page4_inner_page2_mainlayout = new QHBoxLayout(page4_inner_page2);
    QVBoxLayout *page4_inner_page2_rulelayout = new QVBoxLayout;
    QPushButton *page4_inner_page2_startbutton = new QPushButton("再来一局？");
    QSpacerItem *page4_inner_page2_mainlayout_leftspacer = new QSpacerItem(40, 10, QSizePolicy::Minimum, QSizePolicy::Fixed);
    QSpacerItem *page4_inner_page2_mainlayout_rightspacer = new QSpacerItem(120, 10, QSizePolicy::Minimum, QSizePolicy::Expanding);
    QSpacerItem *page4_inner_page2_underbutton_spacer = new QSpacerItem(10, 120, QSizePolicy::Fixed, QSizePolicy::Minimum);

    page4_inner_page2_rulelayout->addWidget(page4_inner_page2_label0);

    page4_inner_page2_mainlayout->addSpacerItem(page4_inner_page2_mainlayout_leftspacer);
    page4_inner_page2_mainlayout->addLayout(page4_inner_page2_rulelayout);
    page4_inner_page2_mainlayout->addSpacerItem(page4_inner_page2_mainlayout_rightspacer);

    page4_inner_page2_rulelayout->addWidget(page4_inner_page2_startbutton);
    page4_inner_page2_rulelayout->addSpacerItem(page4_inner_page2_underbutton_spacer);
    page4_inner_page2_label0->setGeometry(0, 0, 200, 50);
    page4_inner_page2_label0->setAlignment(Qt::AlignCenter);
    page4_inner_page2_startbutton->setFixedSize(80, 40);

    connect(page4_inner_page2_startbutton, &QPushButton::clicked, [=](){
        page4_inner_pages->setCurrentIndex(1);
    });
}


// 打开帮助界面的函数
void MainWindow::on_helpbutton_clicked()
{
    helpwindow *HelpWindow = new helpwindow;
    HelpWindow->show();
    QLabel *the_rules = new QLabel("游戏规则：将牌面上的数字通过加、减、乘、除、括号的运算得到24。\n\n普通模式：我们将给出四个数字，请你判断能否通过运算得到24，若能，则\n选择“能”输入使运算成立的式子；反之，请选择“不能”并点击“确定”。\n\n消消乐模式：我们将给出4*4的数字矩阵，玩家选择能够构成24点的四个数\n字并将它们消去，若矩阵全部数字都被消去视为成功，反之则为失败，如果\n发现剩余数字无法构成，请选择重置。\n\n杂交模式：我们将给出两组（每组四个数字）数字，并挖去一个两组的公共\n数字，玩家填入这个公共数字，使两组数字都能构成24点。", HelpWindow);
    // the_rules->setGeometry(0, 0, 300, 300);
    the_rules->show();
}


// 打开设置界面的函数
void MainWindow::on_settingbutton_clicked()
{
    settingwindow *SettingWindow = new settingwindow;
    SettingWindow->show();
}


// 用于提取用户输入的公式，并用于计算的函数
void MainWindow::on_readresult_clicked()
{
    string content1 = ui->strinput1->text().toStdString();
    string content2 = ui->numinput1->text().toStdString();
    string content3 = ui->strinput2->text().toStdString();
    string content4 = ui->numinput2->text().toStdString();
    string content5 = ui->strinput3->text().toStdString();
    string content6 = ui->numinput3->text().toStdString();
    string content7 = ui->strinput4->text().toStdString();
    string content8 = ui->numinput4->text().toStdString();
    string content9 = ui->strinput5->text().toStdString();

    string result;
    result.append(content1 + content2 + content3 + content4 + content5 + content6 + content7 + content8 + content9);
    int the_final_result;
    the_final_result = calculate(result);

    if (the_final_result == 24){
        // ui->resultdisplay->setText("Right!!");
        ui->final_confirmbutton1->setText("Right!!!");
        ui->final_confirmbutton1->setStyleSheet("QPushButton {background-color:green; border:none; border-radius:0px}");
    }
    else{
        // ui->resultdisplay->setText("Wrong!!");
        ui->final_confirmbutton1->setText("Wrong!!!");
        ui->final_confirmbutton1->setStyleSheet("QPushButton {background-color:red; border:none; border-radius:0px}");
    }

    QString Result = QString::fromStdString(result);

    ui->resultdisplay->setText(Result);
}


// void MainWindow::add_text_to_vector(QPushButton btn)
// {
//     string numstr = btn.text().toStdString();
//     cout<< numstr;
// }


// 主页面渐变出现动画
void MainWindow::homepagetitleinit()
{
    homepagetitleAnimation->setStartValue(0);
    homepagetitleAnimation->setEndValue(1);
    homepagetitleAnimation->start();
};


int *MainWindow::creat_numarry()
{
    static int arr[4] = {4, 3, 2, 1};
    return arr;
}

int MainWindow::countHiddenButtons(QButtonGroup *buttonGroup) {
    int hiddenCount = 0;

    QList<QAbstractButton*> buttons = buttonGroup->buttons();
    for (QAbstractButton *button : buttons) {
        if (!button->isVisible()) {
            hiddenCount++; // 如果按钮不可见，则计数
        }
    }
    return hiddenCount;
}

// std::vector<double> generateRandomIntVector(int n) {
//     std::vector<double> vec(n); // 创建一个有四个元素的向量
//     for (auto& num : vec) {
//         num = generateRandomInt10(); // 填充随机整数
//     }
//     return vec; // 返回填充好的向量
// }

// 生成一个0到3之间的随机整数
int MainWindow::generateRandomInt3() {
    std::random_device rd;  // 随机数生成器
    std::mt19937 gen(rd()); // 以随机设备作为种子的Mersenne Twister生成器
    std::uniform_int_distribution<> dis(0, 3); // 定义一个在[0, 10]范围内均匀分布的整数
    return dis(gen); // 生成随机整数并返回
}

// 生成一个0到10之间的随机整数
int MainWindow::generateRandomInt10() {
    std::random_device rd;  // 随机数生成器
    std::mt19937 gen(rd()); // 以随机设备作为种子的Mersenne Twister生成器
    std::uniform_int_distribution<> dis(0, 10); // 定义一个在[0, 10]范围内均匀分布的整数
    return dis(gen); // 生成随机整数并返回
}
