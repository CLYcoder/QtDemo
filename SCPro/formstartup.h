#ifndef FORMSTARTUP_H
#define FORMSTARTUP_H

// 程序启动过程函数

#include <QWidget>
#include "define.h"

#define singleWidgetShowMaxTime  20    // 时间源选择时长  s
#define timeSourceSlectTime      30    // 时间源选择时长限定 s
#define timerTimeOut             200   // 定时器周期  ms

namespace Ui {
class FormStartUp;
}

class W_timeSource;
class  W_connection;
class W_keyModule;
class W_heatBalance;

class FormStartUp : public QWidget
{
    Q_OBJECT

public:
    explicit FormStartUp(QWidget *parent = 0);
    ~FormStartUp();
    W_timeSource *m_timeSource;
    W_connection *m_connection;
    W_keyModule *m_keyModule;
    W_heatBalance *m_heatBalance;
    void setSubWidgetHideStatus(int);
public slots:
    void onTimeSourceSelectChanged(qint8);
    //void onTimerOut();
    void onWidgetHideStatusChanged(int);

    /* 设备状态发生改变 */
    void onDevStatusChanged(int index, bool status);
    /* 显示下一个设备信息界面 */
    void showNextWidget(int index);
private:
    Ui::FormStartUp *ui;


    //qint32 m_second;
    QTimer *m_timer;

    bool m_bTimeSource;
    bool m_bConnect;
    bool m_bKeyMoudle;
    bool m_bHeatBalance;

    uchar m_showOrder;
    int  m_curShowWidget;

    QList<QWidget *> m_widgetLoop;
signals:
    void updateData();  // 更新数据
};

class  TimeSourceFrame : public QWidget
{
    Q_OBJECT
public:
    enum TimeType{ // 事件源类型
        beidou,Bcode,GPS,ShortWave,LongWave
    };

    TimeSourceFrame(QWidget * parent = 0,TimeType type = beidou ,bool start = false);

    void setItemChecked(bool);  // 设置元素是否被选定
    void setItemUsed(bool);  // 设置元素是否正在使用
    void setItemValid(bool);  // 设置元素是否有效

    bool m_isInStartUP;  // 元素是否是在启动界面  -- 启动界面字体较大
    bool m_itemChecked; // 元素是否被选中
    bool m_itemUsed;    // 元素是否正在使用
    bool m_itemValid;   // 元素是否有效

    showModle m_curModle;

    TimeType m_itemType;

    QLabel *m_icon;
public slots:
    void onShowModleChanged(int);
signals:

};
// 时间源信息显示
class W_timeSource :public QWidget
{
    Q_OBJECT
public:
    W_timeSource(QWidget *parent);
    ~W_timeSource();
    void setSourceState(qint8);
    QTimer *m_timer;
    void showLastTime();

    bool eventFilter(QObject *, QEvent *);
public slots:
   // void onCheckedStateChanged(int arg1);
    void onTimeOut(); // 时间倒数完毕

    void onConfirmBtnClicked(); // 确认按钮点击
signals:
    void selectChanged(int index);

    void checkData(); // 检查缓冲之中的数据
private:
    //QCheckBox *m_check[5];
    QLabel *m_label;
    qint8 m_state;
    qint8 m_second;

    TimeSourceFrame *m_item0;
    TimeSourceFrame *m_item1;
    TimeSourceFrame *m_item2;
    TimeSourceFrame *m_item3;
    TimeSourceFrame *m_item4;

    QPushButton     *m_confirmBtn;

    //int time_count; // 倒计时变量
};

// 联通性表示元素 -- 显示的元素都是没有联通的，联通在之后会在界面上消失
class DevConnectFrame : public QWidget{
    Q_OBJECT
public:
    DevConnectFrame(QWidget * parent,int id,QString name):
        QWidget(parent),m_devId(id),m_info(name)
    {
        this->setStyleSheet("");
        this->resize(50,50);
        m_x = 5;
        m_y = 20;
    }
    void paintEvent(QPaintEvent *e){
        Q_UNUSED(e);
        QPainter painter(this);
        QFont font;
        font.setPointSize(11);
        painter.setFont(font);
        painter.drawText(m_x,m_y,m_info);
    }

    int m_devId;
    int m_x;
    int m_y;
    QString m_info;
};

// 联通性信息显示
class W_connection :public QWidget
{
    Q_OBJECT
public:
    W_connection(QWidget *parent);
    ~W_connection();


    QTimer *m_timer; // 倒计时定时器

public slots:
    void onTimeOut(){

        emit checkData();  // 请求去读取缓冲之中的数据

        addCount++;
        if(addCount % (1000/timerTimeOut) == 0){
            time_count--;
        }
        if(time_count <= 0){
            time_count = singleWidgetShowMaxTime;
            m_timer->stop();
            emit allDevHasBeenConnected(false); // 倒计时结束
        }
    }

signals:
    void allDevHasBeenConnected(bool);

    void checkData(); // 检查缓冲之中的数据
private:
    int time_count; // 倒计时变量
    int addCount;

};

class KeyModuleFrame : public QWidget{
    Q_OBJECT
public:
    KeyModuleFrame(QWidget * parent,int id):
        QWidget(parent),m_devId(id)
    {
        this->resize(50,50);
        m_x = 5;
        m_y = 20;
        this->setStyleSheet("");
    }
    void paintEvent(QPaintEvent *e){
        Q_UNUSED(e); QPainter painter(this);
        QFont font;
        font.setPointSize(11);
        painter.setFont(font);
        painter.drawText(m_x,m_y,m_info);
    }
    int m_devId;
    QString m_info;
    int m_x;
    int m_y;
};

class W_keyModule : public QWidget
{
    Q_OBJECT
public:
    W_keyModule(QWidget *parent);
    ~W_keyModule();
    typedef struct keyMoudleInfo{
        int id; // 模块编号
        QString name; // 模块名称
        QString describe; // 描述
        int time_second;
        int startTime; // 不在线时间
        int endTime;  // 在线时间
    }KeyMouduleInfo;
    QTimer *m_timer;
    void addNewKeyMoudle();
    void updateKeyMoudleInfo();
public slots:
    void onTimeOut(){

        emit checkData();

        addCount++;
        if(addCount % (1000/timerTimeOut) == 0){
            time_count--;
        }
        if(time_count <= 0){
            time_count = singleWidgetShowMaxTime;
            m_timer->stop();
            emit allKeyModuleOnline(false); // 倒计时结束
        }
    }

signals:
    void allKeyModuleOnline(bool); // 标频器件全部在线信号

    void checkData(); // 检查缓冲之中的数据
private:
     int time_count; // 倒计时变量
     int addCount;
};
//标频器件对象
class StdRateModuleFrame :public QWidget
{
    Q_OBJECT
public:
    StdRateModuleFrame(QWidget *parent,QString str,int id) :
        QWidget(parent),
        m_DevId(id)
    {
        // 定时器 记录加热时间
       // Timer = new QTimer;
       // connect(Timer,SIGNAL(timeout()),this,SLOT(onTimeOut()));
    }
    // 元素实现
    void paintEvent(QPaintEvent *e){
        Q_UNUSED(e);
        QPainter painter(this);
        QFont font;
        font.setPointSize(11);
        painter.setFont(font);
        painter.drawText(m_x,m_y,m_info);
    }

    void setFrameColor(bool status)
    {
         if(status){
             frame->setStyleSheet(".QFrame{border:2px solid #0000ff;border-radius:6px;}");
         }else{
             frame->setStyleSheet(".QFrame{border:2px solid #ff0000;border-radius:6px;}");
         }
    }

    QTimer *Timer;
    int second;
    int m_DevId; // 设备编号
    int showNumber; // 显示编号
    QString m_info;
    int m_x;
    int m_y;
    int m_heatTime;
public slots:
    void onTimeOut()
    {
        second++;
        edit->setText(QString("%1").arg(second));
    }
};

// 热平衡信息显示
class W_heatBalance :public QWidget
{
    Q_OBJECT
public:
    W_heatBalance(QWidget *parent);
    ~W_heatBalance();
#pragma pack(1)
    typedef struct moudleInfo{
        int id;  // 类型+编号  类型bit8,其余七个字节编号
        char type;  // H 主机  C 分机
        int number; // 编号
        int crystalNum;
        bool balance; // 是否热平衡
        int time; // 加热时间
        int tempera; // 温度
    }MoudleInfo ,*pMoudleInfo;
#pragma pack()
    // 添加标频模块


    int getStdRateDevsCount(){
        return m_MoudleList.count();
    }
    int getStdRateDevId(int index){
        return m_MoudleList.at(index)->m_DevId;
    }

    bool updateStdRateDevInfo(int,MoudleInfo); // 更新原有模块信息
    void addNewStdRateDev(MoudleInfo); // 添加新模块

    // 设定所有标频器件的平衡状态，已平衡、未平衡
    void setAllDevStatus(bool balance){
        if(balance){
            emit allStdRateDevHeatBalance(true);
        }
    }
    QTimer *m_timer;
public slots:
    // 标频模块的状态发生了改变
    void StdRateMoudleStatusChanged(int,QByteArray);
    void onTimeOut(){
        // 读取接收到的标频模块信息并更新
        emit checkData();

        addCount++;
        if(addCount % (1000/timerTimeOut) == 0){
            time_count--;
        }
        if(time_count <= 0){
            time_count = singleWidgetShowMaxTime;
            m_timer->stop();
            emit allStdRateDevHeatBalance(false); // 倒计时结束
        }
    }

signals:
    void allStdRateDevHeatBalance(bool); // 所有器件热平衡的信号

    void checkData();
private:
    // 模块图片摆放位置
    int pos_x;
    int pos_y;

    int time_count; // 倒计时变量
    int addCount;

    int m_devNum; // 标频器件数量
    QList<StdRateModuleFrame*> m_MoudleList;
};

class MsgConfirmWidget : public QMessageBox
{
    Q_OBJECT
public:
    MsgConfirmWidget(QString msginfo):msg(msginfo){
        this->setWindowFlags(Qt::FramelessWindowHint); // 无边框
        btn_OK = new QPushButton(this);
        btn_cancel = new QPushButton(this);

        this->addButton(btn_OK,QMessageBox::AcceptRole);
        this->addButton(btn_cancel,QMessageBox::RejectRole);

        btn_OK->setStyleSheet("");
        btn_cancel->setStyleSheet("");

        btn_OK->setFocus();

        //connect(btn_OK,SIGNAL(clicked()),this,SLOT(onBtnOKClicked()));
        //connect(btn_cancel,SIGNAL(clicked()),this,SLOT(onBtnCancelClicked()));
    }
    void keyPressEvent(QKeyEvent *event){
        if(event->key() == Qt::Key_Left || event->key() == Qt::Key_Right){
            // 切换屏幕焦点
            if(this->focusWidget() == btn_OK){
                btn_cancel->setFocus();
            }else{
                btn_OK->setFocus();
            }
        }else if(event->key() == Qt::Key_Enter){
            QPushButton *btn = (QPushButton *)this->focusWidget();
            //emit btn->clicked();
            btn->click();
        }
    }
    QPushButton *btn_OK;
    QPushButton *btn_cancel;
    QString msg;
public slots:
    void onBtnOKClicked(){
        emit accepted(); //
    }
    void onBtnCancelClicked(){
        emit rejected();
    }

signals:
};
#endif // FORMSTARTUP_H

