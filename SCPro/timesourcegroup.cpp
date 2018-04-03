#include "timesourcegroup.h"

TimeSourceGroup::TimeSourceGroup(QWidget *parent, QString belongWidget):
    QGroupBox(parent)
{
    this->resize(455,171);
    this->setTitle("时间源信息");
    this->setAlignment(Qt::AlignHCenter);
    QFont font;
    font.setFamily("MicroSoft YaHei");
    font.setPointSize(g_groupBoxTitleSize);
    font.setBold(true);
    this->setFont(font);
    source_1 = new FormTimeSource(this);
    source_1->setItemText("北斗");
    source_1->setItemStatus(FormTimeSource::valid);
    source_1->setProperty("deviceType","client");
    source_1->setItemUsed(true);
    source_1->move(10,35);
    source_1->setProperty("belongWidget",belongWidget);

    source_2 = new FormTimeSource(this);
    source_2->setItemText("B时间码");
    source_2->setItemStatus(FormTimeSource::valid);
    source_2->setProperty("deviceType","client");
    source_2->setItemUsed(false);
    source_2->move(98,35);
    source_2->setProperty("belongWidget",belongWidget);

    source_3 = new FormTimeSource(this);
    source_3->setItemText("G/G");
    source_3->setItemStatus(FormTimeSource::invalid);
    source_3->setProperty("deviceType","client");
    source_3->setItemUsed(false);
    source_3->move(186,35);
    source_3->setProperty("belongWidget",belongWidget);

    source_4 = new FormTimeSource(this);
    source_4->setItemText("短波");
    source_4->setItemStatus(FormTimeSource::invalid);
    source_4->setProperty("deviceType","client");
    source_4->setItemUsed(false);
    source_4->move(274,35);
    source_4->setProperty("belongWidget",belongWidget);

    source_5 = new FormTimeSource(this);
    source_5->setItemText("长波");
    source_5->setItemStatus(FormTimeSource::valid);
    source_5->setProperty("deviceType","client");
    source_5->setItemUsed(false);
    source_5->move(362,35);
    source_5->setProperty("belongWidget",belongWidget);

    m_icon1 = new QLabel(this);
    m_icon1->resize(18,18);
    m_icon1->setProperty("render","static");
    m_icon1->move(50,139);
    m_icon1->setStyleSheet("background-color:#000080");

    m_icon2 = new QLabel(this);
    m_icon2->resize(18,18);
    m_icon2->setProperty("render","static");
    m_icon2->move(116,139);
    m_icon2->setStyleSheet("background-color:#939393");
#if 0
    // 无效图标
    m_icon3 = new QLabel(this);
    m_icon3->resize(18,18);
    m_icon3->setProperty("render","static");
    m_icon3->move(187,139);
    m_icon3->setStyleSheet("background-color:#000000");

    m_msg3 = new QLabel(this);
    m_msg3->setFont(font);
    m_msg3->setText("状态未知");
    m_msg3->move(212,140);
    m_msg3->resize(51,16);

#endif
    m_icon4 = new QLabel(this);
    m_icon4->resize(25,25);
    m_icon4->setProperty("render","static");
    m_icon4->move(314,136);
    m_icon4->setPixmap(QPixmap(":/image/timeIcon3.png"));
    m_icon4->setScaledContents(true);

    font.setPointSize(10);
    m_msg1 = new QLabel(this);
    m_msg1->setFont(font);
    m_msg1->setText("有效");
    m_msg1->move(75,140);
    m_msg1->resize(31,16);

    m_msg2 = new QLabel(this);
    m_msg2->setFont(font);
    m_msg2->setText("无效");
    m_msg2->move(141,140);
    m_msg2->resize(31,16);


    m_msg4 = new QLabel(this);
    m_msg4->setFont(font);
    m_msg4->setText("正在使用");
    m_msg4->move(341,140);
    m_msg4->resize(51,16);


}
TimeSourceGroup::~TimeSourceGroup()
{

}

