#include "scrolltextshow.h"

ScrollTextShow::ScrollTextShow(QWidget *parent) :
    QWidget(parent)
{
    m_normalStr = "设备运行正常";
    m_font.setFamily("新宋体"); // 设置新宋体
    m_font.setPixelSize(24);   // 设置字号
    this->setFont(m_font);
    m_fontHeight = this->fontMetrics().height();
    m_yPos = (56-m_fontHeight)/2;
    this->resize(918,56); // 限定窗口大小
    // 定时器 50ms 移动一次位置
    m_timer = new QTimer(this);
    connect(m_timer,SIGNAL(timeout()),this,SLOT(onTimerOut()));
    m_timer->start(8);

    m_normalText1 = new QLabel(this);
    m_normalText1->setText("设备运行一切正常！");
    m_normalText1->setFont(m_font);
    int width = this->fontMetrics().width("设备运行一切正常！");
    m_normalText1->resize(width,m_fontHeight);
    m_normalText1->move(958,m_yPos);
    m_normalText1->setStyleSheet("color:rgb(0, 0, 128)");
   // qDebug()<<m_normalText1->width();
}

void ScrollTextShow::onTimerOut()
{
    condenseShowList();
    if(m_showTextList.isEmpty()){
        m_showText1 = m_normalText1;

        int offset = m_normalText1->pos().x();
        //offset -= m_normalText1->width()/m_normalText1->text().size();
        offset -= 1;
        if(offset <= 0-m_normalText1->width()){
            offset = 958;
        }
        m_normalText1->move(offset,m_yPos);
    }else{

    }
}
// 将错误信息添加到显示列表中
void ScrollTextShow::addNewText(errorInfo info)
{
    QLabel *label = new QLabel(this);
    label->setFont(m_font);
    int width = this->fontMetrics().width(info.str);
    label->resize(width,m_fontHeight);
    label->setText(info.str);
    label->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    label->setFrameShape(QFrame::Box);
    label->move(958,(56-m_fontHeight)/2);
    label->setProperty("ID",info.id);
    label->setProperty("isHandled",info.isHandled);

    m_showTextList.append(label); // 将文本加入列表中
}

// 设置文本的处理状态，设置成功返回true,否则返回false
bool ScrollTextShow::setErrorInfoStatus(int id, bool isHandled)
{
    bool ret = false;
    for(int i=0;i<m_showTextList.count();i++){
        QLabel * label = m_showTextList.at(i);
        if(label->property("ID").toInt() == id){
            label->setProperty("inHandled",isHandled);
            ret = true;
            break;
        }
    }
    return ret;
}
void ScrollTextShow::condenseShowList()
{
    for(int i =0;i<m_showTextList.count();++i){
        QLabel *lab = m_showTextList.at(i);
        if(lab->property("isHandled").toBool()){
            m_showTextList.removeAt(i);
            i--;
        }
    }
}
