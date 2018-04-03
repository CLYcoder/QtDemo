#ifndef ANALOGCLOCK_H
#define ANALOGCLOCK_H

#include "define.h"
#include <QWidget>

class AnalogClock : public QWidget
{
    Q_OBJECT
public:
    explicit AnalogClock(QWidget *parent,int width,int height);
    void paintEvent(QPaintEvent *event);
    QRectF textRectF(double,int,double);
signals:

public slots:
    void setTime(QTime time);
private:
    // 时间信息时分秒
    int m_hour;
    int m_minute;
    int m_second;

    int m_width;
    int m_height;
};

#endif // ANALOGCLOCK_H
