#include "SliderButton.h"
#include <QPainter>
#include <QLinearGradient>

SliderButton::SliderButton(QWidget *parent) : QPushButton(parent),
    m_sliderPosition(-100), // 初始位置在按钮外
    m_sliderWidth(30), // 设置滑块的宽度
    m_sliderLength(80), // 设置滑块的初始长度，确保大于按钮宽度
    m_animation(new QPropertyAnimation(this, "sliderPosition")),
    m_sliderStartColor(Qt::white), // 滑块渐变的起始颜色
    m_sliderEndColor(Qt::red) { // 滑块渐变的结束颜色

    setFixedSize(100, m_sliderWidth); // 设置按钮的固定大小
    initAnimation();
    setStyleSheet("background-color: white;"); // 设置按钮底色为白色
}

void SliderButton::initAnimation() {
    m_animation->setDuration(1500); // 设置动画持续时间为1000毫秒
    m_animation->setStartValue(m_sliderPosition);
    m_animation->setEndValue(width() + m_sliderWidth);
    m_animation->setEasingCurve(QEasingCurve::OutQuad);
    connect(m_animation, &QPropertyAnimation::finished, this, [this]() {
        // 动画完成后重置滑块位置
        m_sliderPosition = width() + m_sliderWidth;
        update();
    });
}

void SliderButton::setSliderPosition(int position) {
    if (m_sliderPosition != position) {
        m_sliderPosition = position;
        update();
        emit sliderPositionChanged(position);
    }
}

void SliderButton::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // 绘制滑块的渐变色
    QLinearGradient gradient(m_sliderPosition, 0, m_sliderPosition + m_sliderLength, 0);
    gradient.setColorAt(0.0, m_sliderStartColor); // 滑块左侧为白色
    gradient.setColorAt(1.0, m_sliderEndColor); // 滑块右侧为粉红色

    painter.setBrush(gradient);
    painter.setPen(Qt::NoPen);

    // 绘制滑块
    QRect sliderRect(m_sliderPosition, (height() - m_sliderWidth) / 2, m_sliderLength, m_sliderWidth);
    painter.drawRect(sliderRect);
}

void SliderButton::mousePressEvent(QMouseEvent *event) {
    if (m_animation->state() == QPropertyAnimation::Stopped) {
        m_animation->start();
    }
    QPushButton::mousePressEvent(event);
}
