#ifndef PACKMANAGE_H
#define PACKMANAGE_H

// 串口数据接收数据结构定义

#include <QString>
//#include <>


#pragma pack(1)

/******************************************/
// 通用数据头
typedef struct commonHead{
    char start;       // 报文起始标志 $
    char type;        // 数据类型
    char breakPoint;  // 字段分隔符  ,
}CommonHead,*pCommonHead;
// 通用数据结尾
typedef struct commonTail{
    unsigned char breakpoint;
    char sum1;  // 校验和1
    char sum2;  // 校验和2
    unsigned char end1;  // 结束标志1 <cr> 0x0D
    unsigned char end2;  // 结束标志2 <lf> 0x0A
}CommonTail,*pCommonTail;
// 时间信息
typedef struct c_Time{
    unsigned short year;  // 时间信息
    unsigned char month;
    unsigned char day;
    unsigned char hour;
    unsigned char minute;
    unsigned char second;
    unsigned char reserved;
}C_Time,*pTime;

// 主机编号
typedef struct hostDeviceNum{
    unsigned char num  : 6;
    unsigned char online :1;
    unsigned char type : 1;
}HostDeviceNum,*pHostDeviceNum;
// 时间源信息
typedef struct timeSourceStatus{
    unsigned char beidou : 1;
    unsigned char B_code : 1;
    unsigned char GPS_G : 1;
    unsigned char sWave : 1;
    unsigned char lWave : 1;
    unsigned char reserved : 3;
}TimeSrcStatus;
// 时间源使用状态
typedef struct timeSourceUsed{
    unsigned char beidou : 1;
    unsigned char B_code : 1;
    unsigned char GPS_G : 1;
    unsigned char sWave : 1;
    unsigned char lWave : 1;
    unsigned char reserved : 3;
}TimeSrcUsed;

// 铷钟状态
typedef struct RbClock{
    unsigned char clock1_online : 1;
    unsigned char clock1_locked : 1;
    unsigned char clock1_sysLocked : 1;
    unsigned char reserved1 : 1;
    unsigned char clock2_online : 1;
    unsigned char clock2_locked : 1;
    unsigned char clock2_sysLocked : 1;
    unsigned char reserved2 : 1;
}RbClockStatus;

// 电源信息
typedef struct powerInfo{
    unsigned char statusCode : 4;
    unsigned char powerFromCode : 4;
}PowerInfo;

typedef struct _cardInfo{
    unsigned char errCode : 7;
    unsigned char status : 1;
}CInfo;

// 板卡信息
typedef struct CardInfo{
    CInfo status;
    unsigned char tempera;
}CardInfo,*pCardInfo;

// 设备编号
typedef struct DeviceNum{
    unsigned char num : 7;    // 低7位代表代码
    unsigned char code : 1;  // 最高位代表状态
}DevNum;

// 标频器件信息
typedef struct stdRateDevInfo{
    DevNum num;     // 器件编号
    DevNum  status;   // 标频器状态，bit7 是否平衡，bit0-bit6 温度
    unsigned short time; // 加热时间
}StdRDInfo;

// 参考来源+在线状态
typedef struct refSrcAndOnline{
    unsigned char timeRefSrc :3;
    unsigned char reserved : 2;
    unsigned char syslocked : 1;
    unsigned char crystalStatus : 1;
    unsigned char online : 1 ;
}RefAndOnline;

//
/******************************************/
// 时间信息报文
typedef struct timeMeg{
    CommonHead head;
    C_Time time;
    CommonTail tail; // 报文尾部
}TimeMsg, *pTimeMsg;

/******************************************/
//主机信息报文
typedef struct hostMsg{
    CommonHead head;
    HostDeviceNum hostNum;
    TimeSrcStatus timeStatus;
    TimeSrcUsed timeUsed;
    RbClockStatus RbclockStatus;
    unsigned char clock1TimeOffset;
    unsigned char clock2TimeOffset;
    unsigned char clock1Tempera;
    unsigned char clock2Tempera;
    PowerInfo powerInfo;
    CardInfo serial1;          // 串口板卡1
    CardInfo serial2;          // 串口卡2
    CardInfo keepTime;
    CardInfo shutRate;
    CardInfo stdRate;
    CardInfo control;
    CardInfo computer;
    CardInfo net;
    CardInfo test;
    CommonTail tail;
}HostMsg,*pHostMsg;

/******************************************/
//分机信息报文
typedef struct clientMsg{
    CommonHead head;
    DeviceNum clientNum;       // 分机编号
    RefAndOnline Status;       // 分机参考来源和在线状态
    unsigned char clockTimeOffset; // 瞬时时差
    unsigned char clockTempera;    // 晶振温度
    PowerInfo powerInfo;           // 电源状态
    CardInfo serial1;          // 串口板卡1
    CardInfo serial2;          // 串口卡2
    CardInfo keepTime;
    CardInfo shutRate;
    CardInfo stdRate;
    CardInfo control;
    CardInfo computer;
    CardInfo net;
    CardInfo test;
    CommonTail tail;
}ClientMsg,*pClientMsg;
/******************************************/
// 故障信息报文
typedef struct errMeg{
    CommonHead head;
    unsigned char errCode;
    unsigned char handled;
    unsigned char pointBreak;
    C_Time time;
    CommonTail tail;
}ErrMsg,*pErrMsg;

/******************************************/


/******************************************/
/******************************************/
/******************************************/
/******************************************/
/******************************************/

#endif // PACKMANAGE_H
