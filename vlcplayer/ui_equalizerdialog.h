/********************************************************************************
** Form generated from reading UI file 'equalizerdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EQUALIZERDIALOG_H
#define UI_EQUALIZERDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>

QT_BEGIN_NAMESPACE

class Ui_EqualizerDialog
{
public:

    void setupUi(QDialog *EqualizerDialog)
    {
        if (EqualizerDialog->objectName().isEmpty())
            EqualizerDialog->setObjectName(QStringLiteral("EqualizerDialog"));
        EqualizerDialog->resize(758, 404);

        retranslateUi(EqualizerDialog);

        QMetaObject::connectSlotsByName(EqualizerDialog);
    } // setupUi

    void retranslateUi(QDialog *EqualizerDialog)
    {
        EqualizerDialog->setWindowTitle(QApplication::translate("EqualizerDialog", "Dialog", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class EqualizerDialog: public Ui_EqualizerDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EQUALIZERDIALOG_H
