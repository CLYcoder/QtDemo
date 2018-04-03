#ifndef CLIENTWIDGET_H
#define CLIENTWIDGET_H

#include <QWidget>
#include "define.h"
namespace Ui {
class ClientWidget;
}

class ClientWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ClientWidget(QWidget *parent = 0);
    ~ClientWidget();
    void setClientStatus(bool);// 设置分机在线状态
    void setClientName(QString); //设置设备名称
    void setWidgetID(int);
    virtual void focusOutEvent(QFocusEvent *event);
    virtual void focusInEvent(QFocusEvent *event);
    bool m_onLine;
public slots:
    // 槽函数接受状态变化信号
    void onClientNameChanged(QString);
    void onClientStatusChanged(bool);
signals:
    void focusChanged();// 焦点改变时发射信号，供父对象对焦点做出判断
private:
    Ui::ClientWidget *ui;

    QPixmap *m_valid;
    QPixmap *m_invalid;
    int m_widgetID;

};

#endif // CLIENTWIDGET_H
