/********************************************************************************
** Form generated from reading UI file 'formonlinestatus.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FORMONLINESTATUS_H
#define UI_FORMONLINESTATUS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FormOnlineStatus
{
public:

    void setupUi(QWidget *FormOnlineStatus)
    {
        if (FormOnlineStatus->objectName().isEmpty())
            FormOnlineStatus->setObjectName(QStringLiteral("FormOnlineStatus"));
        FormOnlineStatus->resize(913, 306);

        retranslateUi(FormOnlineStatus);

        QMetaObject::connectSlotsByName(FormOnlineStatus);
    } // setupUi

    void retranslateUi(QWidget *FormOnlineStatus)
    {
        FormOnlineStatus->setWindowTitle(QApplication::translate("FormOnlineStatus", "Form", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class FormOnlineStatus: public Ui_FormOnlineStatus {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORMONLINESTATUS_H
