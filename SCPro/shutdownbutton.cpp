#include "shutdownbutton.h"

ShutDownButton::ShutDownButton(QWidget *parent, QString name, bool status):
    QPushButton(parent)
{
    m_sDeviceName = name;
    m_bDeviceStatus = status;

    this->resize(g_buttonSize,g_buttonSize);
    this->setIcon(QIcon(":/image/power1.png"));
    this->setIconSize(QSize(g_buttonSize,g_buttonSize));
    this->setStyleSheet("border-radius:5px");
    connect(this,SIGNAL(clicked()),this,SLOT(onClicked()));
}


void ShutDownButton::onClicked()
{
    QMessageBox box(QMessageBox::Warning,"","确定要关闭"+m_sDeviceName+"吗？");
    box.addButton("确定",QMessageBox::YesRole);
    box.addButton("取消",QMessageBox::NoRole);
    int ret = box.exec();
    qDebug()<<ret;
    if(ret == 0){
        // 确定要关机 ,显示关机信息（倒计时？）
        emit sureShutDownDevice(m_sDeviceName);
    }else{
        // 不做处理
    }
}
void ShutDownButton::setDeviceName(QString name)
{
    m_sDeviceName = name;
    this->setText(m_sDeviceName);
}
void ShutDownButton::setBtnStatus(bool status)
{
    m_bDeviceStatus = status;
    this->setEnabled(m_bDeviceStatus);
}
bool ShutDownButton::getDeviceStatus()
{
    return m_bDeviceStatus;
}
QString ShutDownButton::getDeviceName()
{
    return m_sDeviceName;
}
