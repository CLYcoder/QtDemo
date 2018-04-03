#include "cardinfogroup.h"
#include <QFont>
CardInfoGroup::CardInfoGroup(QWidget* parent):
QGroupBox(parent)
{
    this->resize(621,375);
    this->setTitle("板卡信息");
    this->setAlignment(Qt::AlignHCenter);
    QFont font;
    font.setFamily("MicroSoft YaHei");
    font.setPointSize(g_groupBoxTitleSize);
    font.setBold(true);  // 字体加粗
    this->setFont(font);
    m_card_mainControl = new FormCard(this);
    m_card_mainControl->setCardName("主控");
    m_card_mainControl->move(25,25);
    m_card_computer = new FormCard(this);
    m_card_computer->setCardName("计算机");
    m_card_computer->move(144,25);
    m_card_serial1 = new FormCard(this);
    m_card_serial1->move(263,25);
    m_card_serial1->setCardName("串口1");
    m_card_serial2 = new FormCard(this);
    m_card_serial2->setCardName("串口2");
    m_card_serial2->move(382,25);
    m_card_standardRate = new FormCard(this);
    m_card_standardRate->setCardName("标频");
    m_card_standardRate->move(501,25);
    m_card_keepTime = new FormCard(this);
    m_card_keepTime->setCardName("断电守时");
    m_card_keepTime->move(25,200);
    m_card_insulateRate = new FormCard(this);
    m_card_insulateRate->setCardName("频率隔放");
    m_card_insulateRate->move(144,200);
    m_card_lightFibre = new FormCard(this);
    m_card_lightFibre->setCardName("光纤");
    m_card_lightFibre->move(263,200);
    m_card_test = new FormCard(this);
    m_card_test->setCardName("测试");
    m_card_test->move(382,200);

}
CardInfoGroup::~CardInfoGroup()
{

}
