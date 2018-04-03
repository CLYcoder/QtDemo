#ifndef CARDINFOGROUP_H
#define CARDINFOGROUP_H

#include <QGroupBox>
#include "formcard.h"
#include "define.h"
class CardInfoGroup : public QGroupBox
{
    Q_OBJECT
public:
    explicit CardInfoGroup(QWidget *parent);
    ~CardInfoGroup();

    FormCard *m_card_serial1;
    FormCard *m_card_serial2;
    FormCard *m_card_mainControl; // 主控
    FormCard *m_card_keepTime; // 断电守时
    FormCard *m_card_insulateRate; // 频率隔放
    FormCard *m_card_computer; // 计算机
    FormCard *m_card_standardRate; //标频
    FormCard *m_card_lightFibre; // 光纤
    FormCard *m_card_test;

};

#endif // CARDINFOGROUP_H
