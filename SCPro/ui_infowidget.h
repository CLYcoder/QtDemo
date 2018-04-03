/********************************************************************************
** Form generated from reading UI file 'infowidget.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INFOWIDGET_H
#define UI_INFOWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_InfoWidget
{
public:
    QTabWidget *tabWidget;
    QWidget *tab_4;
    QGroupBox *groupBox;
    QGroupBox *groupBox_36;
    QLabel *label_8;
    QCheckBox *checkBox_4;
    QGroupBox *groupBox_33;
    QLabel *label_5;
    QCheckBox *checkBox;
    QGroupBox *groupBox_37;
    QLabel *label_9;
    QCheckBox *checkBox_5;
    QGroupBox *groupBox_34;
    QLabel *label_6;
    QCheckBox *checkBox_2;
    QGroupBox *groupBox_35;
    QLabel *label_7;
    QCheckBox *checkBox_3;
    QLabel *label;
    QLabel *label_remanentTime;
    QLabel *label_3;
    QPushButton *pushButton;
    QWidget *tab;
    QLabel *label_message;
    QLabel *label_warinIcon;
    QWidget *tab_2;
    QLabel *label_message_2;
    QLabel *label_warinIcon_2;
    QTextBrowser *textBrowser;
    QWidget *tab_3;
    QLabel *label_message_3;
    QLabel *label_warinIcon_3;
    QTableWidget *tableWidget;

    void setupUi(QWidget *InfoWidget)
    {
        if (InfoWidget->objectName().isEmpty())
            InfoWidget->setObjectName(QStringLiteral("InfoWidget"));
        InfoWidget->resize(526, 348);
        tabWidget = new QTabWidget(InfoWidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setGeometry(QRect(0, 0, 531, 351));
        tab_4 = new QWidget();
        tab_4->setObjectName(QStringLiteral("tab_4"));
        groupBox = new QGroupBox(tab_4);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(60, 20, 381, 267));
        groupBox_36 = new QGroupBox(groupBox);
        groupBox_36->setObjectName(QStringLiteral("groupBox_36"));
        groupBox_36->setGeometry(QRect(20, 170, 341, 41));
        label_8 = new QLabel(groupBox_36);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(20, 5, 151, 31));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\256\213\344\275\223"));
        font.setPointSize(13);
        font.setBold(true);
        font.setWeight(75);
        label_8->setFont(font);
        label_8->setTextFormat(Qt::AutoText);
        label_8->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        checkBox_4 = new QCheckBox(groupBox_36);
        checkBox_4->setObjectName(QStringLiteral("checkBox_4"));
        checkBox_4->setGeometry(QRect(220, 5, 30, 30));
        groupBox_33 = new QGroupBox(groupBox);
        groupBox_33->setObjectName(QStringLiteral("groupBox_33"));
        groupBox_33->setGeometry(QRect(20, 20, 341, 41));
        label_5 = new QLabel(groupBox_33);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(20, 10, 151, 31));
        label_5->setFont(font);
        label_5->setTextFormat(Qt::AutoText);
        label_5->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        checkBox = new QCheckBox(groupBox_33);
        checkBox->setObjectName(QStringLiteral("checkBox"));
        checkBox->setGeometry(QRect(220, 5, 30, 30));
        groupBox_37 = new QGroupBox(groupBox);
        groupBox_37->setObjectName(QStringLiteral("groupBox_37"));
        groupBox_37->setGeometry(QRect(20, 220, 341, 41));
        label_9 = new QLabel(groupBox_37);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setGeometry(QRect(20, 5, 151, 31));
        label_9->setFont(font);
        label_9->setTextFormat(Qt::AutoText);
        label_9->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        checkBox_5 = new QCheckBox(groupBox_37);
        checkBox_5->setObjectName(QStringLiteral("checkBox_5"));
        checkBox_5->setGeometry(QRect(220, 5, 30, 30));
        groupBox_34 = new QGroupBox(groupBox);
        groupBox_34->setObjectName(QStringLiteral("groupBox_34"));
        groupBox_34->setGeometry(QRect(20, 70, 341, 41));
        label_6 = new QLabel(groupBox_34);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(20, 5, 151, 31));
        label_6->setFont(font);
        label_6->setTextFormat(Qt::AutoText);
        label_6->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        checkBox_2 = new QCheckBox(groupBox_34);
        checkBox_2->setObjectName(QStringLiteral("checkBox_2"));
        checkBox_2->setGeometry(QRect(220, 5, 30, 30));
        groupBox_35 = new QGroupBox(groupBox);
        groupBox_35->setObjectName(QStringLiteral("groupBox_35"));
        groupBox_35->setGeometry(QRect(20, 120, 341, 41));
        label_7 = new QLabel(groupBox_35);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(20, 5, 151, 31));
        label_7->setFont(font);
        label_7->setTextFormat(Qt::AutoText);
        label_7->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        checkBox_3 = new QCheckBox(groupBox_35);
        checkBox_3->setObjectName(QStringLiteral("checkBox_3"));
        checkBox_3->setGeometry(QRect(220, 5, 30, 30));
        label = new QLabel(tab_4);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(403, 1, 71, 21));
        label_remanentTime = new QLabel(tab_4);
        label_remanentTime->setObjectName(QStringLiteral("label_remanentTime"));
        label_remanentTime->setGeometry(QRect(482, 1, 21, 21));
        label_3 = new QLabel(tab_4);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(500, 0, 21, 21));
        pushButton = new QPushButton(tab_4);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(440, 292, 75, 31));
        tabWidget->addTab(tab_4, QString());
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        label_message = new QLabel(tab);
        label_message->setObjectName(QStringLiteral("label_message"));
        label_message->setGeometry(QRect(210, 135, 131, 31));
        QFont font1;
        font1.setFamily(QString::fromUtf8("\345\256\213\344\275\223"));
        font1.setPointSize(12);
        label_message->setFont(font1);
        label_message->setAlignment(Qt::AlignCenter);
        label_warinIcon = new QLabel(tab);
        label_warinIcon->setObjectName(QStringLiteral("label_warinIcon"));
        label_warinIcon->setGeometry(QRect(160, 130, 41, 41));
        label_warinIcon->setStyleSheet(QStringLiteral("border-image: url(:/image/msg_error.png);"));
        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        label_message_2 = new QLabel(tab_2);
        label_message_2->setObjectName(QStringLiteral("label_message_2"));
        label_message_2->setGeometry(QRect(200, 25, 131, 31));
        label_message_2->setFont(font1);
        label_message_2->setAlignment(Qt::AlignCenter);
        label_warinIcon_2 = new QLabel(tab_2);
        label_warinIcon_2->setObjectName(QStringLiteral("label_warinIcon_2"));
        label_warinIcon_2->setGeometry(QRect(140, 20, 41, 41));
        label_warinIcon_2->setStyleSheet(QStringLiteral("border-image: url(:/image/msg_error.png);"));
        textBrowser = new QTextBrowser(tab_2);
        textBrowser->setObjectName(QStringLiteral("textBrowser"));
        textBrowser->setGeometry(QRect(80, 90, 341, 201));
        tabWidget->addTab(tab_2, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName(QStringLiteral("tab_3"));
        label_message_3 = new QLabel(tab_3);
        label_message_3->setObjectName(QStringLiteral("label_message_3"));
        label_message_3->setGeometry(QRect(160, 25, 221, 31));
        label_message_3->setFont(font1);
        label_message_3->setAlignment(Qt::AlignCenter);
        label_warinIcon_3 = new QLabel(tab_3);
        label_warinIcon_3->setObjectName(QStringLiteral("label_warinIcon_3"));
        label_warinIcon_3->setGeometry(QRect(110, 20, 41, 41));
        label_warinIcon_3->setStyleSheet(QStringLiteral("border-image: url(:/image/msg_error.png);"));
        tableWidget = new QTableWidget(tab_3);
        if (tableWidget->columnCount() < 3)
            tableWidget->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        if (tableWidget->rowCount() < 6)
            tableWidget->setRowCount(6);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(0, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(1, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(2, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(3, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(4, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(5, __qtablewidgetitem8);
        QFont font2;
        font2.setFamily(QString::fromUtf8("\345\256\213\344\275\223"));
        font2.setPointSize(12);
        font2.setBold(true);
        font2.setWeight(75);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        __qtablewidgetitem9->setTextAlignment(Qt::AlignCenter);
        __qtablewidgetitem9->setFont(font2);
        tableWidget->setItem(0, 0, __qtablewidgetitem9);
        QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
        __qtablewidgetitem10->setTextAlignment(Qt::AlignCenter);
        __qtablewidgetitem10->setFont(font2);
        tableWidget->setItem(1, 0, __qtablewidgetitem10);
        QTableWidgetItem *__qtablewidgetitem11 = new QTableWidgetItem();
        tableWidget->setItem(1, 1, __qtablewidgetitem11);
        QTableWidgetItem *__qtablewidgetitem12 = new QTableWidgetItem();
        tableWidget->setItem(1, 2, __qtablewidgetitem12);
        QTableWidgetItem *__qtablewidgetitem13 = new QTableWidgetItem();
        __qtablewidgetitem13->setTextAlignment(Qt::AlignCenter);
        __qtablewidgetitem13->setFont(font2);
        tableWidget->setItem(2, 0, __qtablewidgetitem13);
        QTableWidgetItem *__qtablewidgetitem14 = new QTableWidgetItem();
        __qtablewidgetitem14->setTextAlignment(Qt::AlignCenter);
        __qtablewidgetitem14->setFont(font2);
        tableWidget->setItem(3, 0, __qtablewidgetitem14);
        QTableWidgetItem *__qtablewidgetitem15 = new QTableWidgetItem();
        __qtablewidgetitem15->setTextAlignment(Qt::AlignCenter);
        __qtablewidgetitem15->setFont(font2);
        tableWidget->setItem(4, 0, __qtablewidgetitem15);
        QTableWidgetItem *__qtablewidgetitem16 = new QTableWidgetItem();
        tableWidget->setItem(4, 1, __qtablewidgetitem16);
        QTableWidgetItem *__qtablewidgetitem17 = new QTableWidgetItem();
        __qtablewidgetitem17->setTextAlignment(Qt::AlignCenter);
        __qtablewidgetitem17->setFont(font2);
        tableWidget->setItem(5, 0, __qtablewidgetitem17);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));
        tableWidget->setGeometry(QRect(20, 80, 481, 221));
        tableWidget->horizontalHeader()->setDefaultSectionSize(159);
        tableWidget->verticalHeader()->setVisible(false);
        tableWidget->verticalHeader()->setDefaultSectionSize(32);
        tabWidget->addTab(tab_3, QString());

        retranslateUi(InfoWidget);

        tabWidget->setCurrentIndex(3);


        QMetaObject::connectSlotsByName(InfoWidget);
    } // setupUi

    void retranslateUi(QWidget *InfoWidget)
    {
        InfoWidget->setWindowTitle(QApplication::translate("InfoWidget", "Form", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("InfoWidget", "\351\200\211\346\213\251\346\227\266\351\227\264\346\272\220", Q_NULLPTR));
        groupBox_36->setTitle(QString());
        label_8->setText(QApplication::translate("InfoWidget", "\347\237\255\346\263\242", Q_NULLPTR));
        checkBox_4->setText(QString());
        groupBox_33->setTitle(QString());
        label_5->setText(QApplication::translate("InfoWidget", "\345\214\227\346\226\227", Q_NULLPTR));
        checkBox->setText(QString());
        groupBox_37->setTitle(QString());
        label_9->setText(QApplication::translate("InfoWidget", "\351\225\277\346\263\242", Q_NULLPTR));
        checkBox_5->setText(QString());
        groupBox_34->setTitle(QString());
        label_6->setText(QApplication::translate("InfoWidget", "IRIG-B", Q_NULLPTR));
        checkBox_2->setText(QString());
        groupBox_35->setTitle(QString());
        label_7->setText(QApplication::translate("InfoWidget", "GPS/GLONASS", Q_NULLPTR));
        checkBox_3->setText(QString());
        label->setText(QApplication::translate("InfoWidget", "\351\200\211\346\213\251\345\211\251\344\275\231\346\227\266\351\227\264", Q_NULLPTR));
        label_remanentTime->setText(QApplication::translate("InfoWidget", "30", Q_NULLPTR));
        label_3->setText(QApplication::translate("InfoWidget", "s", Q_NULLPTR));
        pushButton->setText(QApplication::translate("InfoWidget", "\347\241\256\345\256\232", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_4), QApplication::translate("InfoWidget", "tab_select", Q_NULLPTR));
        label_message->setText(QApplication::translate("InfoWidget", "\350\256\276\345\244\207\346\234\252\350\201\224\351\200\232\357\274\201", Q_NULLPTR));
        label_warinIcon->setText(QString());
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("InfoWidget", "Tab 1", Q_NULLPTR));
        label_message_2->setText(QApplication::translate("InfoWidget", "\351\203\250\345\210\206\346\250\241\345\235\227\344\270\215\345\234\250\347\272\277\357\274\201", Q_NULLPTR));
        label_warinIcon_2->setText(QString());
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("InfoWidget", "Tab 2", Q_NULLPTR));
        label_message_3->setText(QApplication::translate("InfoWidget", "\345\255\230\345\234\250\346\240\207\351\242\221\345\231\250\344\273\266\346\262\241\346\234\211\347\203\255\345\271\263\350\241\241\357\274\201", Q_NULLPTR));
        label_warinIcon_3->setText(QString());
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("InfoWidget", "\346\240\207\351\242\221\345\231\250\344\273\266", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("InfoWidget", "\347\203\255\345\271\263\350\241\241", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("InfoWidget", "\345\212\240\347\203\255\346\227\266\351\227\264", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->verticalHeaderItem(0);
        ___qtablewidgetitem3->setText(QApplication::translate("InfoWidget", "\346\226\260\345\273\272\350\241\214", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget->verticalHeaderItem(1);
        ___qtablewidgetitem4->setText(QApplication::translate("InfoWidget", "\346\226\260\345\273\272\350\241\214", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidget->verticalHeaderItem(2);
        ___qtablewidgetitem5->setText(QApplication::translate("InfoWidget", "\346\226\260\345\273\272\350\241\214", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidget->verticalHeaderItem(3);
        ___qtablewidgetitem6->setText(QApplication::translate("InfoWidget", "\346\226\260\345\273\272\350\241\214", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem7 = tableWidget->verticalHeaderItem(4);
        ___qtablewidgetitem7->setText(QApplication::translate("InfoWidget", "\346\226\260\345\273\272\350\241\214", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem8 = tableWidget->verticalHeaderItem(5);
        ___qtablewidgetitem8->setText(QApplication::translate("InfoWidget", "1", Q_NULLPTR));

        const bool __sortingEnabled = tableWidget->isSortingEnabled();
        tableWidget->setSortingEnabled(false);
        QTableWidgetItem *___qtablewidgetitem9 = tableWidget->item(0, 0);
        ___qtablewidgetitem9->setText(QApplication::translate("InfoWidget", "\344\270\273\346\234\2721\345\216\237\345\255\220\351\222\2371", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem10 = tableWidget->item(1, 0);
        ___qtablewidgetitem10->setText(QApplication::translate("InfoWidget", "\344\270\273\346\234\2721\345\216\237\345\255\220\351\222\2372", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem11 = tableWidget->item(2, 0);
        ___qtablewidgetitem11->setText(QApplication::translate("InfoWidget", "\344\270\273\346\234\2722\345\216\237\345\255\220\351\222\2371", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem12 = tableWidget->item(3, 0);
        ___qtablewidgetitem12->setText(QApplication::translate("InfoWidget", "\344\270\273\346\234\2722\345\216\237\345\255\220\351\222\2371", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem13 = tableWidget->item(4, 0);
        ___qtablewidgetitem13->setText(QApplication::translate("InfoWidget", "\344\270\273\346\234\2721\351\253\230\347\250\263\346\231\266\346\214\257", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem14 = tableWidget->item(5, 0);
        ___qtablewidgetitem14->setText(QApplication::translate("InfoWidget", "\344\270\273\346\234\2722\351\253\230\347\250\263\346\231\266\346\214\257", Q_NULLPTR));
        tableWidget->setSortingEnabled(__sortingEnabled);

        tabWidget->setTabText(tabWidget->indexOf(tab_3), QApplication::translate("InfoWidget", "tab_3", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class InfoWidget: public Ui_InfoWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INFOWIDGET_H
