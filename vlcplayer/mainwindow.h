#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <VLCQtCore/Instance.h>
#include <VLCQtCore/Media.h>
#include <VLCQtCore/MediaPlayer.h>
#include <VLCQtCore/Common.h>
#include <QPushButton>
#include <QMenu>
#include <QEvent>
#include <VLCQtWidgets/WidgetSeek.h>
#include "formstatus.h"

#include <QTimer>

#define appName  "Media Player"


namespace Ui {
class MainWindow;
}
/*
class VlcInstance;
class VlcMedia;
class VlcMediaPlayer;
*/
class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    enum TYPE{
        LOCAL,NET,NoMedia
    };
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    /**
     * @brief eventFilter 事件处理器
     * @param watched 发生事件的控件
     * @param event 事件类型
     * @return 事件处理结果
     */
    bool eventFilter(QObject *watched, QEvent *event);

    /**
     * @brief mouseDoubleClickEvent 重写鼠标双击事件函数
     * @param event 未使用
     */
    void mouseDoubleClickEvent(QMouseEvent *event);

    /**
     * @brief readUrlFromConfig 从配置文件中读取rtsp服务器地址
     * @return 读取到的url地址
     */
    QString readUrlFromConfig();

    /**
     * @brief writeUrlToConfig 将远程地址写到配置文件中
     * @param url  rtsp服务器的远程地址
     */
    void writeUrlToConfig(QString url);
private:
    Ui::MainWindow *ui;

    VlcInstance *m_pInstance;
    VlcMedia *m_pMedia;
    VlcMediaPlayer *m_pPlayer;
    VlcWidgetSeek *m_pPlayerSeek;  /* 播放进度控制 */

    QString m_strLoalFile;
    QString m_strURL;

    QPushButton *m_pause;
    QPushButton *m_stop;

    FormStatus *m_statusCtrl;
    TYPE m_curType;

    bool m_isFillScreen;
public slots:
    /**
     * @brief 打开本地视频文件的槽函数
     */
    void openLocalMediaFile();
    /**
     * @brief 打开网络串流
     */
    void openUrl();
    /**
     * @brief 暂停播放
     */
    void pause();
    /**
     * @brief 停止播放
     */
    void stop();
    /**
     * @brief 退出播放器
     */
    void occurError();

    /**
     * @brief playEnd 视频正常结束处理槽函数
     */
    void playEnd(){
        this->setWindowTitle(appName); /* 设置窗口标题 */
        m_statusCtrl->stopPlay();
    }

    /**
     * @brief TimerOut 定时器处理槽函数
     */
    void TimerOut(){
        qDebug()<<"instance status = "<<m_pInstance->status();
    }
signals:
    /**
     * @brief 停止视频播放的信号，发送给视频控制控件
     */
    void stopMediaPlay();

    void pauseMediaPlay();

};

#endif // MAINWINDOW_H
