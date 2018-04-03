/********************************************************************************
** Form generated from reading UI file 'formstatus.ui'
**
** Created by: Qt User Interface Compiler version 5.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FORMSTATUS_H
#define UI_FORMSTATUS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>
#include <VLCQtWidgets/WidgetSeek.h>

QT_BEGIN_NAMESPACE

class Ui_FormStatus
{
public:
    QGridLayout *gridLayout;
    QPushButton *btn_pause;
    QPushButton *btn_stop;
    QSpacerItem *horizontalSpacer;
    VlcWidgetSeek *player_seek;

    void setupUi(QWidget *FormStatus)
    {
        if (FormStatus->objectName().isEmpty())
            FormStatus->setObjectName(QStringLiteral("FormStatus"));
        FormStatus->resize(810, 43);
        gridLayout = new QGridLayout(FormStatus);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        btn_pause = new QPushButton(FormStatus);
        btn_pause->setObjectName(QStringLiteral("btn_pause"));
        btn_pause->setMaximumSize(QSize(36, 32));
        QIcon icon;
        icon.addFile(QStringLiteral(":/icos/play.ico"), QSize(), QIcon::Normal, QIcon::Off);
        btn_pause->setIcon(icon);
        btn_pause->setIconSize(QSize(24, 24));

        gridLayout->addWidget(btn_pause, 0, 0, 1, 1);

        btn_stop = new QPushButton(FormStatus);
        btn_stop->setObjectName(QStringLiteral("btn_stop"));
        btn_stop->setMaximumSize(QSize(36, 32));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/icos/stop.ico"), QSize(), QIcon::Normal, QIcon::Off);
        btn_stop->setIcon(icon1);
        btn_stop->setIconSize(QSize(24, 24));

        gridLayout->addWidget(btn_stop, 0, 1, 1, 1);

        horizontalSpacer = new QSpacerItem(28, 20, QSizePolicy::Maximum, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 0, 2, 1, 1);

        player_seek = new VlcWidgetSeek(FormStatus);
        player_seek->setObjectName(QStringLiteral("player_seek"));

        gridLayout->addWidget(player_seek, 0, 3, 1, 1);


        retranslateUi(FormStatus);

        QMetaObject::connectSlotsByName(FormStatus);
    } // setupUi

    void retranslateUi(QWidget *FormStatus)
    {
        FormStatus->setWindowTitle(QApplication::translate("FormStatus", "Form", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        btn_pause->setToolTip(QApplication::translate("FormStatus", "\346\232\202\345\201\234/\347\273\247\347\273\255\350\247\206\351\242\221\346\222\255\346\224\276", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        btn_pause->setText(QString());
#ifndef QT_NO_TOOLTIP
        btn_stop->setToolTip(QApplication::translate("FormStatus", "\345\205\263\351\227\255\346\255\243\345\234\250\346\222\255\346\224\276\347\232\204\350\247\206\351\242\221", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        btn_stop->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class FormStatus: public Ui_FormStatus {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORMSTATUS_H
