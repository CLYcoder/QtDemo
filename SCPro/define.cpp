#include "define.h"

int g_widthScreen; // 屏幕宽度
int g_heightScreen; // 屏幕高度
int g_checkTimerInterval; // 启动检查定时器周期
float g_localTimeZone; // 当前时区
showModle g_ShowModle = day;
//char* g_deviceName = "舰船时频基准设备"; // 设备名称

QString g_serialPortInfo0;
QString g_serialPortInfo1;
QString g_serialPortInfo2;
QString g_serialPortInfo3;

#ifdef Q_OS_WIN
QString appFontName = "Microsoft YaHei";
#else
QString appFontName = "wqy-zenhei";
#endif

//接收数据缓冲
QByteArray recvBuffer0;
QByteArray recvBuffer1;
QByteArray recvBuffer2;
QByteArray recvBuffer3;

char g_timeSourceSelected = 0x01;
int g_checkSourceLimitTime;
// 手动模式选项


int errorInfoID = 0;
QList<errorInfo> g_errorList;
//QList<DeviceInfo> g_deviceInfo;
/********************************************************************/
// 处理函数
// 读配置文件
void readConfig()
{
    QSettings *read = new QSettings("config.ini",QSettings::IniFormat);
    read->setIniCodec(QTextCodec::codecForName("UTF8"));
    read->beginGroup("screen");
         g_heightScreen = read->value("height",768).toInt();
         g_widthScreen = read->value("width",1024).toInt();
    read->endGroup();
    read->beginGroup("checkTimer");
         g_checkTimerInterval = read->value("timerInterval",100).toInt();
    read->endGroup();
    read->beginGroup("serialPort");
         g_serialPortInfo0 = read->value("serialPort0","COM2,115200,N,8,1").toString();
         g_serialPortInfo1 = read->value("serialPort1","COM3,115200,N,8,1").toString();
         g_serialPortInfo2 = read->value("serialPort2","COM4,115200,N,8,1").toString();
         g_serialPortInfo3 = read->value("serialPort3","COM5,115200,N,8,1").toString();
    read->endGroup();
    read->beginGroup("Time");
         g_localTimeZone = read->value("localTimeZone",8).toFloat();
         g_checkSourceLimitTime = read->value("checkTimelimitTime",30).toInt();
    read->endGroup();
#if 0
    read->beginGroup("Device");
         g_deviceName.fromUtf8(read->value("DevName").toString().toLatin1());
    read->endGroup();
#endif
}
// 写配置文件
void writeConfig()
{
    QSettings *write = new QSettings("config.ini",QSettings::IniFormat);
#if 0
    write->beginGroup("Devive");
         write->setValue("DevName",g_deviceName);
    write->endGroup();
#endif
    write->beginGroup("screen");
         write->setValue("height",g_heightScreen);
         write->setValue("width",g_widthScreen);
    write->endGroup();
    write->beginGroup("checkTimer");
         write->setValue("timerInterval",g_checkTimerInterval);
    write->endGroup();
    write->beginGroup("serialPort");
         write->setValue("serialPort0",g_serialPortInfo0);
         write->setValue("serialPort1",g_serialPortInfo1);
         write->setValue("serialPort2",g_serialPortInfo2);
         write->setValue("serialPort3",g_serialPortInfo3);
    write->endGroup();
    write->beginGroup("Time");
         write->setValue("localTimeZone",QString("%1").arg(g_localTimeZone));
         write->setValue("checkTimelimitTime",g_checkSourceLimitTime);
    write->endGroup();
    write->sync(); // 配置文件同步
}
// 写日志
void writeLogInfo(QString str)
{
    QString date = QDate::currentDate().toString("yyyy-MM-dd");
    QString time = QTime::currentTime().toString("HH:mm:ss.zzz");
    QFile file("log.txt");
    if(file.open(QIODevice::Append | QIODevice::Text)){
        QString temp = date+" "+time+":\n   "+str+"\n\n";
        QTextStream out(&file);
        out.setCodec("UTF-8");
        out<<temp;
    }else
        qDebug()<<"打开日志文件失败";

}
// 处理校验位
QSerialPort::Parity handleParity(QString str)
{
    if(str == "N"){
        return QSerialPort::NoParity;
    }else if(str == "O"){
        return QSerialPort::OddParity;
    }else if(str == "E"){
        return QSerialPort::EvenParity;
    }else if(str == "S"){
        return QSerialPort::SpaceParity;
    }else if(str == "M"){
        return QSerialPort::MarkParity;
    }else
        return QSerialPort::UnknownParity;

}
QSerialPort::BaudRate handleBaudRate(QString str)
{
    switch (str.toInt()) {
    case 1200:
        return QSerialPort::Baud1200;
        break;
    case 2400:
        return QSerialPort::Baud2400;
        break;
    case 4800:
        return QSerialPort::Baud4800;
        break;
    case 9600:
        return QSerialPort::Baud9600;
        break;
    case 19200:
        return QSerialPort::Baud19200;
        break;
    case 38400:
        return QSerialPort::Baud38400;
        break;
    case 57600:
        return QSerialPort::Baud57600;
        break;
    case 115200:
        return QSerialPort::Baud115200;
        break;
    default:
        return QSerialPort::UnknownBaud;
        break;
    }
}
QSerialPort::StopBits handleStopBits(QString str)
{
    if(str == "1"){
        return QSerialPort::OneStop;
    }else if(str == "1.5"){
        return QSerialPort::OneAndHalfStop;
    }else if(str == "2"){
        return QSerialPort::TwoStop;
    }else
        return QSerialPort::UnknownStopBits;
}
QSerialPort::DataBits handleDataBits(QString str)
{
    switch (str.toInt()) {
    case 5:
        return QSerialPort::Data5;
    case 6:
        return QSerialPort::Data6;
    case 7:
        return QSerialPort::Data7;
    case 8:
        return QSerialPort::Data8;
    default:
        return QSerialPort::UnknownDataBits;
    }

}

QString getTimeZone(float num){
    QString str = "";
    if(num > 0 && num < 14){
        if(num == (int)num)
            str.sprintf("UTC+%02d:00",(int)num);
        else
            str.sprintf("UTC+%02d:30",(int)num);
    }else if(num < 0 && num > -13){
        if(num == (int)num)
            str.sprintf("UTC-%02d:00",0-(int)num);
        else
            str.sprintf("UTC-%02d:30",0-(int)num);
    }else if(num == 0){
         str.sprintf("UTC");
    }
    qDebug()<<"计算时区"<<str;
    return str;
}
#if 0
int getTimeZone(QString str){
    if(str.size() == 3){
        if(str.at(0) == "东"){
            return str.mid(1,1).toInt();
        }else if(str.at(0) == "西"){
            return 0-str.mid(1,1).toInt();
        }else if(str.at(0) == "零"){
            return 0;
        }
    }else if(str.size() == 5){
        return 12;
    }else{
        if(str.at(0) == "东"){
            return str.mid(1,2).toInt();
        }else if(str.at(0) == "西"){
            return 0-str.mid(1,2).toInt();
        }
    }
}
#endif
// 时区列表
#if 0
QStringList TimeZoneList = QStringList()<<"(UTC-12:00)国际日期变更线西"
<<"(UTC-11:00)协调世界时-11"<<"(UTC-10:00)夏威夷"<<"(UTC-09:00)阿拉斯加"<<"(UTC-08:00)太平洋时间（美国和加拿大）"<<"(UTC-07:00)奇瓦瓦，拉巴斯，马萨特兰"
<<"(UTC-06:00)瓜达拉哈拉，墨西哥城，蒙特雷"<<"(UTC-06:00)萨斯喀彻温"<<"(UTC-06:00)中部时间（美国和加拿大）"<<"(UTC-06:00)中美洲"
<<"(UTC-05:00)波哥大，利马基多"<<"(UTC-05:00)东部时间(美国和加拿大)"<<"(UTC-05:00)印第安纳州（东部）"<<"(UTC-04:30)加拉加斯"
<<"(UTC-04:00)西太平洋时间（加拿大）"<<"(UTC-04:00)库亚巴"<<"(UTC-04:00)乔治敦，拉巴斯，玛瑙斯，圣胡安"<<"(UTC-04:00)圣地亚哥"
<<"(UTC-04:00)亚松森"<<"(UTC-03:30)纽芬兰"<<"(UTC-03:00)巴西亚利"<<"(UTC-03:00)布宜诺斯艾利斯"<<"(UTC-03:00)格陵兰""(UTC-03:00)卡宴，福塔雷萨"
<<"(UTC-03:00)蒙得维的亚"<<"(UTC-03:00)萨尔瓦多"<<"(UTC-02:00)协调世界时-02"<<"(UTC-01:00)佛得角群岛"<<"(UTC-01:00)亚速尔群岛"<<"(UTC)都柏林，爱丁堡，里斯本，伦敦"
<<"(UTC)卡萨布兰卡"<<"(UTC)蒙罗威维，雷克雅未克"<<"(UTC)协调世界时"<<"(UTC+01:00)阿姆斯特丹，柏林，伯尔尼"<<"(UTC+01:00)罗马，斯德哥尔摩，维也纳"<<"(UTC+01:00)贝尔格莱德，布拉迪斯拉发"
<<"(UTC+01:00)布达佩斯，卢布尔雅那，布拉格"<<"(UTC+01:00)布鲁塞尔，哥本哈根，马德里，巴黎"<<"(UTC+01:00)萨拉热窝，斯科普里，华沙，萨格勒布"<<"(UTC+01:00)温得和克"<<"(UTC+01:00)中非西部"
<<"(UTC+02:00)贝鲁特，大马士革，的黎波里"<<"(UTC+02:00)东欧，哈拉雷，比勒陀利亚"<<"(UTC+02:00)赫尔辛基，基辅"<<"(UTC+02:00)里加，索菲亚，塔林，维尔纽斯"<<"(UTC+02:00)开罗"<<"(UTC+02:00)雅典，布加勒斯特"
<<"(UTC+02:00)耶路撒冷"<<"(UTC+02:00)伊斯坦布尔"<<"(UTC+03:00)安曼"<<"(UTC+03:00)巴格达"<<"(UTC+03:00)加里宁格勒，明斯克"<<"(UTC+03:00)科威特，利雅得"<<"(UTC+03:00)内毕罗"<<"(UTC+03:30)德黑兰"
<<"(UTC+04:00)阿布扎比，玛斯喀特"<<"(UTC+04:00)埃里温"<<"(UTC+04:00)巴库"<<"(UTC+04:00)基比利斯"<<"(UTC+04:00)路易港"<<"(UTC+04:00)莫斯科，圣彼得堡，伏尔加格勒"<<"(UTC+04:30)喀布尔"<<"(UTC+05:00)阿什哈巴德，塔什干"
<<"(UTC+05:30)钦奈，加尔各答，孟买，新德里"<<"(UTC+05:30)斯里加亚渥登普拉"<<"(UTC+05:45)加德满都"<<"(UTC+06:00)阿斯塔纳，达卡"<<"(UTC+06:00)叶卡捷琳堡"<<"(UTC+06:30)仰光"<<"(UTC+07:00)曼谷，河内，雅加达"<<"(UTC+07:00)新西伯利亚"
<<"(UTC+08:00)北京，重庆，香港特别行政区，乌鲁木齐"<<"(UTC+08:00)吉隆坡，新加坡"<<"(UTC+08:00)克拉斯诺亚尔斯克"<<"(UTC+08:00)珀斯"<<"(UTC+08:00)台北"<<"(UTC+08:00)乌兰巴托"<<"(UTC+09:00)大阪，札幌，东京"<<"(UTC+09:00)首尔"
<<"(UTC+09:00)伊尔库茨克"<<"(UTC+09:30)阿德莱德"<<"(UTC+09:30)达尔文"<<"(UTC+10:00)布里斯班"<<"(UTC+10:00)关岛，莫尔兹比港，霍巴特"<<"(UTC+10:00)堪培拉，墨尔本，悉尼"<<"(UTC+10:00)雅库茨克"<<"(UTC+11:00)弗拉迪沃斯托克"
<<"(UTC+11:00)所罗门群岛"<<"(UTC+12:00)奥克兰，惠灵顿"<<"(UTC+12:00)斐济"<<"(UTC+12:00)马加丹"<<"(UTC+12:00)协调世界时+12"<<"(UTC+13:00)努库阿洛法"<<"(UTC+13:00)萨摩亚群岛";
#endif
// 根据错误代码获取错误信息
QString getStrErrInfo(unsigned char errcode)
{
    QString str = "";
    switch (errcode) {
    case 0x01:
        str = "";
        break;
    case 0x02:
        str = "";
        break;
    case 0x03:
        str = "";
        break;
    case 0x04:
        str = "";
        break;
    default:
        break;
    }
    return str;
}
// 根据信息代码获取信息 index = 1 状态 ， 0 来源
QString getStrPowerInfo(int index,PowerInfo info)
{
    QString str ;
    if(index)
    {
        // 获取电源状态
        switch (info.statusCode) {
        case 0x01:
            str = "";
            break;
        default:
            break;
        }
    }else
    {
        // 获取电源来源信息
        switch (info.powerFromCode) {
        case 0x01:
            str = "";
            break;
        default:
            break;
        }
    }
    return str;
}
// 根据故障代码获取故障信息
QString getStrCardInfo(uchar errcode){
    QString str = "";
    switch (errcode) {
    case 0x01:
        str = "";
        break;
    case 0x02:
        str = "";
        break;
    case 0x03:
        str = "";
        break;
    case 0x04:
        str = "";
        break;
    default:
        break;
    }
    return str;
}

// 根据模块代码获取未连接模块信息
QString getModuleInfo(uchar moduleCode)
{
    QString str = "";
    switch(moduleCode){
    case 0x01:
        str = "";
        break;
    case 0x02:
        break;
    default:
        break;
    }
    return str;
}

QString getStrSubDevRefSrc(uchar refCode)
{
    QString str ;
    switch (refCode) {
    case 0x01:
        str = "主机1原子钟1";
        break;
    case 0x02:
        str = "主机1原子钟2";
        break;
    case 0x03:
        str = "主机2原子钟1";
        break;
    case 0x04:
        str = "主机2原子钟2";
        break;
    default:
        break;
    }
    return str;
}
/***************************************************/
// 函数功能：串口报文校验
// 参数： btr 需要校验的数据内容   sum1、sum2 校验和高4位、低4位
// 返回值： true 数据校验正确   false 数据校验出错
/***************************************************/
bool msgNMEACheck(QByteArray btr,char sum1,char sum2)
{
    if(sum1 >= 'a' && sum1 <='z'){
        sum1 -= 32;
    }
    if(sum2 >= 'a' && sum2 <='z'){
        sum2 -= 32;
    }
    uchar sum = 0;
    for(int i = 0;i<btr.size();++i){
        sum ^= btr.at(i);
    }
    char str1[3] = {0};
    char str2[3] = {sum1,sum2,0};
    sprintf(str1,"%X%X",(sum>>4)&0x0f,sum&0x0f);
   // qDebug()<<"校验和="<<str1<<"计算结果="<<str2;
    return  strcmp(str1,str2)?false:true;
}
