#ifndef FRMMAIN_H
#define FRMMAIN_H

#include <QWidget>
#include "define.h"
#include "clientwidget.h"
#include "formtimesource.h"
#include "cardinfogroup.h"
#include "timesourcegroup.h"
#include "shutdownbutton.h"
#include "scrolltextshow.h"
#include "formstartup.h"
#include "analogclock.h"
#include "data.h"

namespace Ui {
class FrmMain;

class C_ErrMsg;
class C_HostMsg;
class C_ClientMsg;
class C_StdRateMoudleMsg;
class C_KeyMoudleMsg;
class C_DevConnectMsg;
}

extern QStringList TimeZoneList;

class FrmMain : public QWidget
{
    Q_OBJECT

public:
    explicit FrmMain(QWidget *parent = 0);
    ~FrmMain();
    //显示屏幕类型
    enum widgetType{
        major = 0,host,client,setting,help,reserved,startup
    };

    void initMainWidget(); // 初始化信息显示界面
    void openSerialPort(QSerialPort *port,int num); //打开指定串口
    int m_currentStytle;

    enum stytle{
        dayTime = 0,duskTime,nightTime
    };
    void keyPressEvent(QKeyEvent *event);
    //void keyReleaseEvent(QKeyEvent *event);
    void handleKeyEvent(int);
    static void setAppStytle(QString);
    void setTime(QTime time,QDate date);   // 设置时间信息
    void setTimeZone(float);
    float getLocalTimeZone(QString str);
    void showClientWidget(int);// 显示分机状态界面的分机状态
    /****************************************************/
    // 动态添加分机图标
    void addNewClient();
    int m_num_client; // 分机数量
    /****************************************************/
    // 添加时间源图元
    void showTimeSourceWidget();
    /****************************************************/
    CardInfoGroup *groupHost1;
    CardInfoGroup *groupHost2;
    CardInfoGroup *groupClient;
    TimeSourceGroup *timeGroupHost1_page1;
    TimeSourceGroup *timeGroupHost2_page1;
    TimeSourceGroup *timeGroupHost1_page2;
    TimeSourceGroup *timeGroupHost2_page2;
    TimeSourceGroup *timeGroupClient;
    // 滚动条
    ScrollTextShow *scrollText;
    /*  控制函数 */
    void addItemToEventFilter();
    bool eventFilter(QObject *watched, QEvent *event);
    // 数据处理函数
    void parseBuffer(int num);  // 处理串口数据
    void parseMsg(QByteArray);
    int PreBuffer1Size;
    int PreBuffer2Size;
    int PreBuffer3Size;
    int PreBuffer4Size;
    // 处理时间信息报文
    void handleTimeInfo(QByteArray btr);
    // 处理主机信息报文
    void handleHostInfo(QByteArray btr);
    // 处理分机信息报文
    void handleClientInfo(QByteArray btr);
    // 处理设备联通性报文
    void handleDevConnectInfo(QByteArray btr);
    // 处理关键模块在线报文
    void handleKeyMoudleInfo(QByteArray btr);
    // 处理标频器件热平衡
    void handleStdRateInfo(QByteArray btr);
    // 处理故障报文
    void handleErrInfo(QByteArray btr);

    void updateHostInfo(pDevInfo info, pHostMsg msg);
    void updateClientInfo(pDevInfo info, pClientMsg msg);

signals:
    void SCreenFocusPointChanged(int); // 屏幕焦点变化
    void keyPressOccured(int);  // 发生了按键点击事件

public slots:
    void recvSerialData0(); // 串口接收槽函数 -- 分别接收串口数据
    void recvSerialData1();
    void recvSerialData2();
    void recvSerialData3();

    void onTimeOut(); // 定时器中断处理槽函数
    /****************************************************/
    void onFocusChanged(); // 屏幕焦点发生了改变
    /****************************************************/
    void onUpdateStyleSheet();
    /****************************************************/
    void onSureCloseRemoteDevice(QString);
    /****************************************************/
    void onCheckData();  // 从缓冲中读取数据信息，并更新界面显示
    /****************************************************/
private slots:
    void on_comboBox_workModel_currentIndexChanged(int index);

    void on_comboBox_timeZoneDirec_currentIndexChanged(int index);

    void on_pushButton_clicked();
private:
    Ui::FrmMain *ui;
    QTimer *m_timer; // 定时器1处理软件启动阶段的联通和设备在线问题

    // 需要操作的串口
    QSerialPort *m_serialPort1;
    QSerialPort *m_serialPort2;
    QSerialPort *m_serialPort3;
    QSerialPort *m_serialPort0;

    FormStartUp *m_start;
    // 主界面显示之前
    bool m_bDeviceConnected; // 设备联通标志
    bool m_bKeyModuleOnLine; // 关键模块在线标志
    bool m_bStdFreqHeatBalance; // 标频模块热平衡
    /* tabWidget 相关控件 */
    /* 列表控件 */
    QTableWidget *m_breakdownInfo; // 远程关机列表
    //QTableWidget *m_timeSourceInfo;

    bool b_firstInit; // 界面初始化标志
    // 分机图片列表
    QList<ClientWidget*> m_ClientWidgetList;
    QWidget *m_currentFocusWidget;
    QString qss_str; // 样式表内容
    /*  自动确定时区标志    */
    bool m_bAutoSetTimeZone;
    /*  设备信息列表 */
    QList<pDevInfo> m_subDevInfoList; // 分机信息列表
    pDevInfo m_host1;
    pDevInfo m_host2;
    int m_devIndex;
    QList<QWidget>  m_widgetList;  // 控件列表 -- 关键字 ObjectName

    /*  当前正在显示的界面标志 */
    widgetType currentShow;
    /*  模拟时钟控件 */
    AnalogClock *m_colock1;
    AnalogClock *m_colock2;
    /* 时间日期变量 */
    QTime m_time;
    QDate m_date;


};

#ifdef MSG_CLASS
// 错误信息报文
class C_ErrMsg : public DATA{

    C_ErrMsg(int type ,int length,char *data):DATA(type,length,data){

    }
    virtual void handleData(){
    }
};
// 主机信息报文
class C_HostMsg : public DATA{
    C_HostMsg(int type ,int length,char *data):DATA(type,length,data){

    }
    virtual void handleData(){

    }
};
// 分机信息报文
class C_ClientMsg : public DATA {
    C_ClientMsg(int type ,int length,char *data):DATA(type,length,data){

    }
    virtual void handleData(){

    }
};
// 设备联通性判断报文
class C_DevConnectMsg : public DATA{
    C_DevConnectMsg(int type ,int length,char *data):DATA(type,length,data){

    }
    virtual void handleData(){

    }
};
// 关键模块在线判断报文
class C_KeyMoudleMsg : public DATA{
    C_KeyMoudleMsg(int type ,int length,char *data):DATA(type,length,data){

    }
    virtual void handleData(){

    }
};
// 标频模块
class C_StdRateMoudleMsg : public DATA{
    C_StdRateMoudleMsg(int type ,int length,char *data):DATA(type,length,data){

    }
    virtual void handleData(){

    }
};
class C_TimeMSg : public DATA{
    C_TimeMSg(int type ,int length,char *data):DATA(type,length,data){

    }
    virtual void handleData(){
        pCommonHead head = (pCommonHead)malloc(sizeof(CommonHead));
        pCommonTail tail = (pCommonTail)malloc(sizeof(CommonTail));
        memcpy(head,m_data,3);
        memcpy(tail,m_data+m_length-6,5);
        if(head->start != '$' || tail->breakpoint != '*'
                || tail->end1 != 0x0D || tail->end2 != 0x0A )
            return;
        if(m_length == sizeof(TimeMsg)){
            pTimeMsg msg = (pTimeMsg)m_data;
            QTime time1;
            QDate date;
            C_Time time = msg->time;
            time1.fromString(QString().sprintf("%02d:%02d:%02d",time.hour,time.minute,time.second),
                            "hh:mm:ss");
            date.fromString(QString().sprintf("%04d:%02d:%02d",time.year,time.month,time.day),
                            "yyyy-MM-dd");
           // FrmMain::setTime(time,date);
        }else{
            // 数据长度不匹配
        }
        free(head);
        free(tail);
    }
};
#endif
#endif // FRMMAIN_H
