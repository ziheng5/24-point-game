#ifndef SLIDERBUTTON_H
#define SLIDERBUTTON_H

#include <QPushButton>
#include <QPropertyAnimation>

class SliderButton : public QPushButton {
    Q_OBJECT
    Q_PROPERTY(int sliderPosition READ sliderPosition WRITE setSliderPosition NOTIFY sliderPositionChanged)

public:
    explicit SliderButton(QWidget *parent = nullptr);

    int sliderPosition() const { return m_sliderPosition; }
    void setSliderPosition(int position);

signals:
    void sliderPositionChanged(int position);

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;

private:
    void initAnimation();
    void drawSlider(QPainter *painter);

    int m_sliderPosition;
    int m_sliderWidth;
    int m_sliderLength;
    QPropertyAnimation *m_animation;
    QColor m_sliderStartColor;
    QColor m_sliderEndColor;
};

#endif // SLIDERBUTTON_H
