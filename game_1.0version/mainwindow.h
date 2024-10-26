#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "helpwindow.h"
#include "settingwindow.h"
#include "detect24.h"
#include "equation.h"
#include "generate24.h"
#include "timer.h"
#include <QMainWindow>
#include <QPushButton>
#include <QPropertyAnimation>
#include <QGraphicsOpacityEffect>
#include <QLabel>
#include <QMainWindow>
#include <QParallelAnimationGroup>
#include "SliderButton.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void toggleMode();  // 切换模式的槽函数
    void on_startButton_clicked();

private:
    QPushButton *modeButton;  // 切换模式的按钮
    bool isDarkMode;          // 追踪当前模式，初始为白天模式
    QPropertyAnimation *colorAnimation;  // 动画对象

    QColor startColor;  // 开始颜色
    QColor endColor;    // 结束颜色

    bool page3_gameblock1_clicked = false;
    bool page3_gameblock2_clicked = false;
    bool page3_gameblock3_clicked = false;
    bool page3_gameblock4_clicked = false;
    bool page3_gameblock5_clicked = false;
    bool page3_gameblock6_clicked = false;
    bool page3_gameblock7_clicked = false;
    bool page3_gameblock8_clicked = false;
    bool page3_gameblock9_clicked = false;
    bool page3_gameblock10_clicked = false;
    bool page3_gameblock11_clicked = false;
    bool page3_gameblock12_clicked = false;
    bool page3_gameblock13_clicked = false;
    bool page3_gameblock14_clicked = false;
    bool page3_gameblock15_clicked = false;
    bool page3_gameblock16_clicked = false;

    void startColorTransition(const QColor &start, const QColor &end);  // 颜色过渡函数
    void applyPalette(const QColor &color);  // 应用调色板颜色
    QIcon setIconColor(QIcon icon, QColor color);
    void switchPage();
    void initProperties();
    void homepagetitleinit();
    int *creat_numarry();
    int game_blocks_count;
    void game_blocks_init();
    int generateRandomInt10();
    int generateRandomInt3();
    int norm_random_key;
    int count_block_num;
    int page3_random_24numbers_key1;
    int page3_random_24numbers_key2;
    int page3_random_24numbers_key3;
    int page3_random_24numbers_key4;
    // void add_text_to_vector(QPushButton btn);
    QGraphicsOpacityEffect homepagetitleOpacity;
    QLabel *destroy_maintitle;
    QPropertyAnimation *homepagetitleAnimation;
    QPropertyAnimation *buttonopacityAnimation;
    QButtonGroup *norm_confirm_buttongroup;
    QPushButton *page3_gameblock1;
    QPushButton *page3_gameblock2;
    QPushButton *page3_gameblock3;
    QPushButton *page3_gameblock4;
    QPushButton *page3_gameblock5;
    QPushButton *page3_gameblock6;
    QPushButton *page3_gameblock7;
    QPushButton *page3_gameblock8;
    QPushButton *page3_gameblock9;
    QPushButton *page3_gameblock10;
    QPushButton *page3_gameblock11;
    QPushButton *page3_gameblock12;
    QPushButton *page3_gameblock13;
    QPushButton *page3_gameblock14;
    QPushButton *page3_gameblock15;
    QPushButton *page3_gameblock16;
    vector<double> page3_game_numberstore;
    vector<int> page3_game_blockstore;
    int page3_game_targetnumber;
    int countHiddenButtons(QButtonGroup *buttonGroup);
    vector<string> horizontal_line;

private:
    // 左侧侧边栏拉伸动画
    QButtonGroup *menubuttonGroup;
    Ui::MainWindow *ui;
    QParallelAnimationGroup *m_group;
    QPropertyAnimation *sidemenuAnimation1;
    QPropertyAnimation *sidemenuAnimation2;
    bool sidemenuFlag = false;

private slots:
    // 左侧侧边栏按钮被点击信号
    void sidemenu_pushbutton_clicked();

    void on_helpbutton_clicked();
    void on_settingbutton_clicked();
    void on_readresult_clicked();
};



#endif // MAINWINDOW_H
