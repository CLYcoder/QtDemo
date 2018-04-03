#include "analogclock.h"

AnalogClock::AnalogClock(QWidget *parent, int width, int height) :
    QWidget(parent),
    m_width(width),
    m_height(height)
{
    m_hour = 0;
    m_minute = 0;
    m_second = 0;
    this->resize(m_width,m_height);
   // QFrame *frame = new QFrame(this);
    //frame->setLineWidth(2);
   // frame->resize(m_width,m_height);
   // frame->show();

}
// 画时钟
void AnalogClock::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    // 时、分、秒指针的多边形
    static const QPoint hourHand[3] = {
        QPoint(3,8),
        QPoint(-3,8),
      //  QPoint(-4,-23),
        QPoint(0,-43),
      //  QPoint(4,-23)
    };
    static const QPoint minuteHand[3] = {
        QPoint(3,12),
        QPoint(-3,12),
      //  QPoint(-3,-58),
        QPoint(0,-65),
      //  QPoint(3,-58)
    };
    static const QPoint secondHand[4] = {
        QPoint(1,14),
        QPoint(-1,14),
      //  QPoint(-2,-70),
        QPoint(-1,-80),
        QPoint(1,-80)
      //  QPoint(2,-70)
    };

    // 指针颜色
    QColor hourColor(200,100,0,200);
    QColor minuteColor(0,127,127,150);
    QColor secondColor(0,160,230,150);

    int side = qMin(m_width,m_height);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    // 平移坐标系原点到界面中心
    painter.translate(m_width/2.0,m_height/2.0);
    // 坐标缩放
    painter.scale(side/200.0,side/200.0);
/********************************************/
    /* 绘制时针 */
    painter.setPen(Qt::NoPen);
    painter.setBrush(hourColor);
    painter.save();

    painter.rotate((m_hour + m_minute / 60.0)*30); // 旋转指针
    painter.drawConvexPolygon(hourHand,3);
    painter.restore();
    //绘制小时线
    painter.setPen(hourColor);
    for(int i=0;i<12;++i){
        painter.drawLine(88,0,96,0);
        painter.rotate(30.0);
    }
    // 绘制小时文本
    int nHour = 0;

    double radius = side / 2;
    QFont font = painter.font();
    font.setBold(true);
    painter.setFont(font);

    for(int i =0 ;i<12;++i){
        nHour = i+3;
        if(nHour > 12){
            nHour -= 12;
        }
        painter.drawText(textRectF(radius*0.8,font.pointSize(),i*30),Qt::AlignCenter,QString::number(nHour));
    }

/********************************************/
    /* 绘制分针 */
    painter.setPen(Qt::NoPen);
    painter.setBrush(minuteColor);

    painter.save();

    painter.rotate(6.0*(m_minute + m_second/60.0));
    painter.drawConvexPolygon(minuteHand,3);
    painter.restore();
    // 绘制分钟线
    painter.setPen(minuteColor);
    for(int i=0;i<60;++i){
        if(i%5){
            painter.drawLine(92,0,96,0);
        }
        painter.rotate(6);
    }

/********************************************/
    /* 绘制秒针 */
    painter.setPen(Qt::NoPen);
    painter.setBrush(secondColor);

    painter.save();

    painter.rotate(6.0*m_second);
    painter.drawConvexPolygon(secondHand,4);
    painter.restore();
/********************************************/
}

// 更新时钟显示时间内容
void AnalogClock::setTime(QTime time)
{
    m_hour = time.hour();
    m_minute = time.minute();
    m_second = time.second();
    update(); // 更新时钟
}
// 返回时钟，小时文本的书写位置
QRectF AnalogClock::textRectF(double radius, int pointsize, double angle)
{
    QRectF rectf;
    rectf.setX(radius*qCos(angle*M_PI/180.0)-pointsize*2);
    rectf.setY(radius*qSin(angle*M_PI/180.0)-pointsize/2.0);
    rectf.setWidth(pointsize*4);
    rectf.setHeight(pointsize);

    return rectf;
}
