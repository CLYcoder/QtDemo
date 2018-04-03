#ifndef DEFINE_H
#define DEFINE_H

/* 界面控件 */
#include <QtCore>
#include <QtGui>
#include <QWidget>
#include <QDialog>
#include <QMessageBox>
#include <QLabel>
#include <QLineEdit>
#include <QGroupBox>
#include <QLine>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QListWidget>
#include <QCheckBox>
#include <QCoreApplication>
#include <QHeaderView>
#include <QLCDNumber>
#include <QComboBox>

/* 拓展控件  */
#if 0
#include "qwt_analog_clock.h"
#include "qwt_dial_needle.h"
#include "qwt_point_polar.h"
#include "qwt_round_scale_draw.h"
#endif
/* 功能组件 */
#include <QThread>
#include <QTimer>
#include <QPixmap>
#include <QImage>
#include <QPalette>
#include <QPainter>
#include <QSettings>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QTime>
#include <QDate>
#include <QDateTime>
//#include <QTimeZone>
#include <QDebug>
#include <QFocusEvent>
#include <QFont>
#include <QPainter>
#include <QPaintEvent>

#include "assert.h"

/* 数据相关 */
#include <QString>
#include <QByteArray>
#include <QStringList>
#include <QList>
#include <QLinkedList>
#include <QVector>
#include "math.h"

#include "packmanage.h"

/***************************************/
#define g_groupBoxTitleSize 9
#define g_buttonSize   40
#define ErrMsgSizeMAX  50

#define QT_5  (QT_VERSION_MAJOR == 5 ? 1 : 0)


#if QT_5
#include<QtSerialPort>
#include<QSerialPortInfo>
#else

#include<QtSerialPort/QSerialPort>
#include<QtSerialPort/QSerialPortInfo>

#endif

extern QString appFontName;  // 程序显示字体

/***************************************/
extern int g_widthScreen;
extern int g_heightScreen;

extern int g_checkTimerInterval;
extern float g_localTimeZone;

//extern char* g_deviceName;

extern QString g_serialPortInfo0;
extern QString g_serialPortInfo1;
extern QString g_serialPortInfo2;
extern QString g_serialPortInfo3;

extern QByteArray recvBuffer0;   // 串口1数据缓冲
extern QByteArray recvBuffer1;   // 串口2数据缓冲
extern QByteArray recvBuffer2;   // 串口3数据缓冲
extern QByteArray recvBuffer3;   // 串口4数据缓冲

extern char g_timeSourceSelected;
extern int g_checkSourceLimitTime;

void readConfig();
void writeConfig();
void writeLogInfo(QString);

QString getStrErrInfo(unsigned char errcode);
QString getStrPowerInfo(int index,PowerInfo info);
QString getStrCardInfo(uchar errcode);
QString getModuleInfo(uchar moduleCode);
QString getStrSubDevRefSrc(uchar refCode);

QString getTimeZone(float num); // 获取时区描述
int getTimeZone(QString str);

bool msgNMEACheck(QByteArray btr,char sum1,char sum2); // 数据校验

QSerialPort::Parity handleParity(QString str);
QSerialPort::BaudRate handleBaudRate(QString str);
QSerialPort::StopBits handleStopBits(QString str);
QSerialPort::DataBits handleDataBits(QString str);
//extern QStringList TimeZoneList;

// 设备种类,主机从机
enum MachineType{
    hostDev = 0,subDev
};
// 状态指示
enum Status{
    invalid = 0,unknown,valid
};
// 显示模式  白天，黄昏，夜晚
enum showModle{
    day = 0,dusk,night
};

//时间源信息
typedef struct TimeSource{
    Status source1_status;  // 北斗
    bool source1_used;
    Status source2_status;  // IRIG-B
    bool source2_used;
    Status source3_status;  // GPS/GLONASS
    bool source3_used;
    Status source4_status;  // 短波
    bool source4_used;
    Status source5_status;  // 长波
    bool source5_used;
}TimeSource;
// 铷钟状态（主机单元）
typedef struct clockStatus{
    bool crystalLocked;
    bool systemLocked;
    int timeOffset;
    int temperature;
}ClockStatus;

//板卡状态
typedef struct cardStatus{
    Status status;
    int tempera;
    QString  describe; // 状态描述
}CardStatus;

// 设备信息
typedef struct DeviceInfo{
    int id;
    MachineType type; // 设备类型 -- 主机、从机
    unsigned char devNum;  // 设备编号
    QString name; // 设备名称 -- 主机12，从机1234
/*********************************/
    // 主机特有信息
    TimeSource timeSource;

    ClockStatus clock_1;  // host
    ClockStatus clock_2;
/*********************************/
    // 分机特有信息
    bool sysLocked; // 系统锁定
    bool crstalLocked; // 晶振锁定
    bool isOnline;  // 在线状态
    int  timeOffset; // 晶振瞬时时差
    int  tempera;       // 晶振温度
/*********************************/
    QString refSrc;   // 参考来源  主机1/主机2

    CardStatus serial1Card;
    CardStatus serial2Card;
    CardStatus stdRateCard;
    CardStatus keepTimeCard;
    CardStatus rateCutCard;
    CardStatus controlCard;
    CardStatus computerCard;
    CardStatus networkCard;
    CardStatus testCard;

    QString powerStatus;
    QString powerFrom;

    pHostMsg msg;   // 主机原始数据
    bool infoChanged; // 信息发生了改变

}DevInfo,*pDevInfo;

// 错误ID
extern  int errorInfoID;
typedef struct errorInfo{
    int id;
    QString str;
    unsigned char errCode;
    bool isHandled;
    QString timeStart;
    QString timeEnd;
}errorInfo;

extern QList<errorInfo> g_errorList;  // 故障信息列表
//extern QList<pDevInfo> g_subDeviceInfo;  // 设备信息列表

//g_checkTimeInterval

extern showModle g_ShowModle; // 程序当前的显示模式

#endif // DEFINE_H
