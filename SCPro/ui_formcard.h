/********************************************************************************
** Form generated from reading UI file 'formcard.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FORMCARD_H
#define UI_FORMCARD_H

#include <QtCore/QVariant>
#include <QAction>
#include <QApplication>
#include <QButtonGroup>
#include <QFrame>
#include <QHeaderView>
#include <QLabel>
#include <QTextBrowser>
#include <QWidget>

QT_BEGIN_NAMESPACE

class Ui_FormCard
{
public:
    QFrame *frame;
    QTextBrowser *textBrowser;
    QLabel *label_cardName;
    QLabel *label_Temp;
    QLabel *label_3;

    void setupUi(QWidget *FormCard)
    {
        if (FormCard->objectName().isEmpty())
            FormCard->setObjectName(QString("FormCard"));
        FormCard->resize(95, 161);
        frame = new QFrame(FormCard);
        frame->setObjectName(QString("frame"));
        frame->setGeometry(QRect(0, 0, 95, 161));
        frame->setFrameShape(QFrame::Box);
        frame->setFrameShadow(QFrame::Raised);
        frame->setLineWidth(1);
        textBrowser = new QTextBrowser(frame);
        textBrowser->setObjectName(QString("textBrowser"));
        textBrowser->setEnabled(false);
        textBrowser->setGeometry(QRect(3, 79, 88, 80));
        textBrowser->setFrameShape(QFrame::Panel);
        textBrowser->setFrameShadow(QFrame::Sunken);
        textBrowser->setReadOnly(true);
        label_cardName = new QLabel(frame);
        label_cardName->setObjectName(QString("label_cardName"));
        label_cardName->setGeometry(QRect(9, 5, 78, 22));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\215\216\346\226\207\346\245\267\344\275\223"));
        font.setPointSize(14);
        font.setBold(true);
        font.setWeight(75);
        label_cardName->setFont(font);
        label_cardName->setFrameShape(QFrame::NoFrame);
        label_cardName->setFrameShadow(QFrame::Raised);
        label_cardName->setAlignment(Qt::AlignCenter);
        label_Temp = new QLabel(frame);
        label_Temp->setObjectName(QString("label_Temp"));
        label_Temp->setGeometry(QRect(30, 40, 51, 31));
        QFont font1;
        font1.setFamily(QString::fromUtf8("\347\255\211\347\272\277"));
        font1.setPointSize(15);
        font1.setBold(false);
        font1.setWeight(50);
        label_Temp->setFont(font1);
        label_Temp->setAlignment(Qt::AlignCenter);
        label_3 = new QLabel(frame);
        label_3->setObjectName(QString("label_3"));
        label_3->setGeometry(QRect(8, 37, 23, 36));
        label_3->setStyleSheet(QString("image: url(:/image/card_tempera.png);"));

        retranslateUi(FormCard);

        QMetaObject::connectSlotsByName(FormCard);
    } // setupUi

    void retranslateUi(QWidget *FormCard)
    {
        FormCard->setWindowTitle(QApplication::translate("FormCard", "Form", NULL));
        textBrowser->setHtml(QApplication::translate("FormCard", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'SimSun'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p>\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:10pt;\">\345\267\245\344\275\234\346\255\243\345\270\270</span></p></body></html>", NULL));
        label_cardName->setText(QApplication::translate("FormCard", "\344\270\262\345\217\2431", NULL));
        label_Temp->setText(QApplication::translate("FormCard", "40\342\204\203", NULL));
        label_3->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class FormCard: public Ui_FormCard {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORMCARD_H
