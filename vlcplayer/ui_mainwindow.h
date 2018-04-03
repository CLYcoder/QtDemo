/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>
#include <VLCQtWidgets/WidgetVideo.h>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *action_openlocal;
    QAction *action_openUrl;
    QAction *action_quit;
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    VlcWidgetVideo *video;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1305, 875);
        action_openlocal = new QAction(MainWindow);
        action_openlocal->setObjectName(QStringLiteral("action_openlocal"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/icos/movie.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_openlocal->setIcon(icon);
        action_openUrl = new QAction(MainWindow);
        action_openUrl->setObjectName(QStringLiteral("action_openUrl"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/icos/net.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_openUrl->setIcon(icon1);
        action_quit = new QAction(MainWindow);
        action_quit->setObjectName(QStringLiteral("action_quit"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(0);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        video = new VlcWidgetVideo(centralWidget);
        video->setObjectName(QStringLiteral("video"));

        gridLayout->addWidget(video, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1305, 23));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        action_openlocal->setText(QApplication::translate("MainWindow", "Open Local Media", Q_NULLPTR));
        action_openUrl->setText(QApplication::translate("MainWindow", "Open Net media", Q_NULLPTR));
        action_quit->setText(QApplication::translate("MainWindow", "quit", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        action_quit->setToolTip(QApplication::translate("MainWindow", "\351\200\200\345\207\272\347\250\213\345\272\217", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
