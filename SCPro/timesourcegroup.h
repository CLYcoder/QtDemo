#ifndef TIMESOURCEGROUP_H
#define TIMESOURCEGROUP_H

#include <QGroupBox>
#include <QLabel>
#include "define.h"
#include "formtimesource.h"

class TimeSourceGroup : public QGroupBox
{
    Q_OBJECT
public:
    explicit TimeSourceGroup(QWidget *parent,QString belongWidget);
    ~TimeSourceGroup();

    QLabel *m_icon1;
    QLabel *m_icon2;
    QLabel *m_icon3;
    QLabel *m_icon4;
    QLabel *m_msg1;
    QLabel *m_msg2;
    QLabel *m_msg3;
    QLabel *m_msg4;

    FormTimeSource *source_1;
    FormTimeSource *source_2;
    FormTimeSource *source_3;
    FormTimeSource *source_4;
    FormTimeSource *source_5;
};

#endif // TIMESOURCEGROUP_H
