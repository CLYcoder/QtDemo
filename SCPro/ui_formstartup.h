/********************************************************************************
** Form generated from reading UI file 'formstartup.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FORMSTARTUP_H
#define UI_FORMSTARTUP_H

#include <QtCore/QVariant>
#include <QAction>
#include <QApplication>
#include <QButtonGroup>
#include <QCheckBox>
#include <QFrame>
#include <QGroupBox>
#include <QHeaderView>
#include <QLabel>
#include <QWidget>

QT_BEGIN_NAMESPACE

class Ui_FormStartUp
{
public:
    QFrame *frame;
    QGroupBox *groupBox;
    QGroupBox *groupBox_timeSource;
    QLabel *label;
    QLabel *label_6;
    QLabel *label_timeSource;
    QGroupBox *groupBox_connect;
    QLabel *label_3;
    QLabel *label_8;
    QCheckBox *checkBox_connect;
    QGroupBox *groupBox_keyModule;
    QCheckBox *checkBox_module;
    QLabel *label_4;
    QLabel *label_9;
    QGroupBox *groupBox_heatBalance;
    QLabel *label_5;
    QCheckBox *checkBox_module_2;
    QLabel *label_10;
    QGroupBox *groupBox_tips;
    QLabel *label_2;
    QGroupBox *groupBox_infoShow;

    void setupUi(QWidget *FormStartUp)
    {
        if (FormStartUp->objectName().isEmpty())
            FormStartUp->setObjectName(QStringLiteral("FormStartUp"));
        FormStartUp->resize(1024, 768);
        FormStartUp->setStyleSheet(QStringLiteral(""));
        frame = new QFrame(FormStartUp);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setGeometry(QRect(116, 93, 791, 581));
        frame->setStyleSheet(QStringLiteral(""));
        frame->setFrameShape(QFrame::Box);
        frame->setFrameShadow(QFrame::Sunken);
        frame->setLineWidth(1);
        groupBox = new QGroupBox(frame);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(20, 25, 201, 531));
        groupBox_timeSource = new QGroupBox(groupBox);
        groupBox_timeSource->setObjectName(QStringLiteral("groupBox_timeSource"));
        groupBox_timeSource->setGeometry(QRect(7, 70, 187, 78));
        label = new QLabel(groupBox_timeSource);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(8, 5, 28, 28));
        label->setStyleSheet(QStringLiteral("image: url(:/image/timeIcon1.png);"));
        label_6 = new QLabel(groupBox_timeSource);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(67, 14, 54, 16));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font.setPointSize(11);
        label_6->setFont(font);
        label_6->setAlignment(Qt::AlignCenter);
        label_timeSource = new QLabel(groupBox_timeSource);
        label_timeSource->setObjectName(QStringLiteral("label_timeSource"));
        label_timeSource->setGeometry(QRect(20, 45, 141, 21));
        QFont font1;
        font1.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font1.setPointSize(12);
        label_timeSource->setFont(font1);
        label_timeSource->setAlignment(Qt::AlignCenter);
        groupBox_connect = new QGroupBox(groupBox);
        groupBox_connect->setObjectName(QStringLiteral("groupBox_connect"));
        groupBox_connect->setGeometry(QRect(7, 178, 187, 51));
        label_3 = new QLabel(groupBox_connect);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(8, 12, 27, 27));
        label_3->setStyleSheet(QStringLiteral("image: url(:/image/connect_connectivity.png);"));
        label_8 = new QLabel(groupBox_connect);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(50, 14, 76, 20));
        label_8->setFont(font);
        label_8->setAlignment(Qt::AlignCenter);
        checkBox_connect = new QCheckBox(groupBox_connect);
        checkBox_connect->setObjectName(QStringLiteral("checkBox_connect"));
        checkBox_connect->setGeometry(QRect(147, 12, 28, 28));
        checkBox_connect->setStyleSheet(QLatin1String("QCheckBox::indicator{width:32px;height:32;}\n"
"QCheckBox::indicator:unchecked{image:url(:/image/checkbox_unchecked.png);}\n"
"QCheckBox::indicator:checked{image:url(:/image/checkbox_checked.png);}"));
        groupBox_keyModule = new QGroupBox(groupBox);
        groupBox_keyModule->setObjectName(QStringLiteral("groupBox_keyModule"));
        groupBox_keyModule->setGeometry(QRect(7, 259, 187, 51));
        checkBox_module = new QCheckBox(groupBox_keyModule);
        checkBox_module->setObjectName(QStringLiteral("checkBox_module"));
        checkBox_module->setGeometry(QRect(147, 12, 28, 28));
        checkBox_module->setStyleSheet(QLatin1String("QCheckBox::indicator{width:32px;height:32;}\n"
"QCheckBox::indicator:unchecked{image:url(:/image/checkbox_unchecked.png);}\n"
"QCheckBox::indicator:checked{image:url(:/image/checkbox_checked.png);}"));
        label_4 = new QLabel(groupBox_keyModule);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(8, 12, 27, 27));
        label_4->setStyleSheet(QStringLiteral("image: url(:/image/Sound_Card_751px_1191380_easyicon.net.png);"));
        label_9 = new QLabel(groupBox_keyModule);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setGeometry(QRect(47, 14, 91, 20));
        label_9->setFont(font);
        label_9->setAlignment(Qt::AlignCenter);
        groupBox_heatBalance = new QGroupBox(groupBox);
        groupBox_heatBalance->setObjectName(QStringLiteral("groupBox_heatBalance"));
        groupBox_heatBalance->setGeometry(QRect(7, 340, 187, 51));
        label_5 = new QLabel(groupBox_heatBalance);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(8, 12, 27, 27));
        label_5->setStyleSheet(QStringLiteral("image: url(:/image/card_tempera.png);"));
        checkBox_module_2 = new QCheckBox(groupBox_heatBalance);
        checkBox_module_2->setObjectName(QStringLiteral("checkBox_module_2"));
        checkBox_module_2->setGeometry(QRect(147, 12, 28, 28));
        checkBox_module_2->setStyleSheet(QLatin1String("QCheckBox::indicator{width:32px;height:32;}\n"
"QCheckBox::indicator:unchecked{image:url(:/image/checkbox_unchecked.png);}\n"
"QCheckBox::indicator:checked{image:url(:/image/checkbox_checked.png);}"));
        label_10 = new QLabel(groupBox_heatBalance);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setGeometry(QRect(38, 14, 105, 20));
        label_10->setFont(font);
        label_10->setAlignment(Qt::AlignCenter);
        groupBox_tips = new QGroupBox(groupBox);
        groupBox_tips->setObjectName(QStringLiteral("groupBox_tips"));
        groupBox_tips->setGeometry(QRect(7, 426, 187, 81));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(40, 16, 121, 31));
        label_2->setFont(font);
        label_2->setAlignment(Qt::AlignCenter);
        groupBox_infoShow = new QGroupBox(frame);
        groupBox_infoShow->setObjectName(QStringLiteral("groupBox_infoShow"));
        groupBox_infoShow->setGeometry(QRect(240, 25, 531, 531));

        retranslateUi(FormStartUp);

        QMetaObject::connectSlotsByName(FormStartUp);
    } // setupUi

    void retranslateUi(QWidget *FormStartUp)
    {
        FormStartUp->setWindowTitle(QApplication::translate("FormStartUp", "Form", Q_NULLPTR));
        groupBox->setTitle(QString());
        groupBox_timeSource->setTitle(QString());
        label->setText(QString());
        label_6->setText(QApplication::translate("FormStartUp", "\346\227\266\351\227\264\346\272\220", Q_NULLPTR));
        label_timeSource->setText(QApplication::translate("FormStartUp", "GPS/GLONASS", Q_NULLPTR));
        groupBox_connect->setTitle(QString());
        label_3->setText(QString());
        label_8->setText(QApplication::translate("FormStartUp", "\350\256\276\345\244\207\350\201\224\351\200\232", Q_NULLPTR));
        checkBox_connect->setText(QString());
        groupBox_keyModule->setTitle(QString());
        checkBox_module->setText(QString());
        label_4->setText(QString());
        label_9->setText(QApplication::translate("FormStartUp", "\345\205\263\351\224\256\346\250\241\345\235\227\345\234\250\347\272\277", Q_NULLPTR));
        groupBox_heatBalance->setTitle(QString());
        label_5->setText(QString());
        checkBox_module_2->setText(QString());
        label_10->setText(QApplication::translate("FormStartUp", "\346\240\207\351\242\221\345\231\250\344\273\266\347\203\255\345\271\263\350\241\241", Q_NULLPTR));
        groupBox_tips->setTitle(QString());
        label_2->setText(QApplication::translate("FormStartUp", "\350\275\257\344\273\266\345\220\257\345\212\250\346\265\201\347\250\213", Q_NULLPTR));
        groupBox_infoShow->setTitle(QString());
    } // retranslateUi

};

namespace Ui {
    class FormStartUp: public Ui_FormStartUp {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORMSTARTUP_H
