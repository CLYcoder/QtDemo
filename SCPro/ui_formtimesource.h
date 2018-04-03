/********************************************************************************
** Form generated from reading UI file 'formtimesource.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FORMTIMESOURCE_H
#define UI_FORMTIMESOURCE_H

#include <QtCore/QVariant>
#include <QAction>
#include <QApplication>
#include <QButtonGroup>
#include <QFrame>
#include <QHeaderView>
#include <QLabel>
#include <QWidget>

QT_BEGIN_NAMESPACE

class Ui_FormTimeSource
{
public:
    QFrame *frame;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_valid;
    QLabel *label_3;

    void setupUi(QWidget *FormTimeSource)
    {
        if (FormTimeSource->objectName().isEmpty())
            FormTimeSource->setObjectName(QStringLiteral("FormTimeSource"));
        FormTimeSource->resize(78, 80);
        FormTimeSource->setStyleSheet(QStringLiteral(""));
        frame = new QFrame(FormTimeSource);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setGeometry(QRect(0, 0, 78, 80));
        frame->setStyleSheet(QStringLiteral("background-color: rgb(190, 190, 190);"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        label = new QLabel(frame);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(7, 35, 64, 15));
        QFont font;
        font.setFamily(QStringLiteral("Arial"));
        font.setPointSize(12);
        label->setFont(font);
        label->setStyleSheet(QStringLiteral("color: rgb(0, 0, 128);"));
        label->setAlignment(Qt::AlignCenter);
        label_2 = new QLabel(frame);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(50, 3, 25, 25));
        label_valid = new QLabel(frame);
        label_valid->setObjectName(QStringLiteral("label_valid"));
        label_valid->setGeometry(QRect(7, 8, 23, 23));
        label_3 = new QLabel(frame);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(4, 53, 70, 15));
        QFont font1;
        font1.setFamily(QStringLiteral("Arial"));
        font1.setPointSize(11);
        label_3->setFont(font1);
        label_3->setStyleSheet(QStringLiteral("color: rgb(0, 0, 128);"));
        label_3->setAlignment(Qt::AlignCenter);

        retranslateUi(FormTimeSource);

        QMetaObject::connectSlotsByName(FormTimeSource);
    } // setupUi

    void retranslateUi(QWidget *FormTimeSource)
    {
        FormTimeSource->setWindowTitle(QApplication::translate("FormTimeSource", "Form", Q_NULLPTR));
        label->setText(QApplication::translate("FormTimeSource", "GPS", Q_NULLPTR));
        label_2->setText(QString());
        label_valid->setText(QString());
        label_3->setText(QApplication::translate("FormTimeSource", "GLONASS", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class FormTimeSource: public Ui_FormTimeSource {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORMTIMESOURCE_H
