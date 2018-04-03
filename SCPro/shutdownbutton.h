#ifndef SHUTDOWNBUTTON_H
#define SHUTDOWNBUTTON_H

#include "define.h"
#include <QPushButton>

/*************************************************/
// 远程关机按钮
/*************************************************/


class ShutDownButton : public QPushButton
{
    Q_OBJECT
public:
    ShutDownButton(QWidget *parent=Q_NULLPTR,QString name = "",bool status = false);
    bool getDeviceStatus();
    void setBtnStatus(bool);
    QString getDeviceName();
    void setDeviceName(QString name);
signals:
    void sureShutDownDevice(QString);
public slots:
    void onClicked();  // 按钮被点击
private:
    QString m_sDeviceName;
    bool m_bDeviceStatus;
};

#endif // SHUTDOWNBUTTON_H
