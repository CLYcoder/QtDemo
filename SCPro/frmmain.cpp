#include "frmmain.h"
#include "ui_frmmain.h"
#include "stdlib.h"

#define IGNORE_START  1

QString g_deviceName = "舰船时频基准设备";

FrmMain::FrmMain(QWidget *parent):
    QWidget(parent),
    ui(new Ui::FrmMain)
{
    ui->setupUi(this);
    readConfig();  // 读取配置文件
    b_firstInit = true;
    initMainWidget(); // 界面元素初始化
    ui->label_deviceName->setText(QString(g_deviceName)); // 设置设备名称标签

   // this->setWindowFlags(Qt::FramelessWindowHint);  //
    /********************************************/
    // 开启定时器
    m_timer = new QTimer(this);
    connect(m_timer,SIGNAL(timeout()),this,SLOT(onTimeOut()));
    m_timer->start(1000);
    /********************************************/
    // 加载qss文件
    QFile file(":/qss/dayTime.qss");
    if(file.open(QFile::ReadOnly)){
        qss_str = file.readAll();
#if IGNORE_START
        qApp->setStyleSheet(qss_str);
#endif
    }
    b_firstInit = false;
    qDebug()<<"时区数值"<<g_localTimeZone;
    setTimeZone(g_localTimeZone);

    //ui->groupBox_handModelSetting->hide();
    showClientWidget(8);  // 显示分机图片

    /*******************************************************/
    QString tZ = ui->label_LocalTimeZone->text();
    //qDebug()<<tZ;
    for(int i=0;i<ui->comboBox_timeZoneDirec->count();i++){
        QString str = ui->comboBox_timeZoneDirec->itemText(i);
       // qDebug()<<str.mid(1,tZ.size());
       if(str.mid(1,tZ.size()) == tZ){
           ui->comboBox_timeZoneDirec->setCurrentIndex(i);
          // qDebug()<<str;
           break;
       }
    }
    /*******************************************************/
    m_currentFocusWidget = new QWidget();

    groupClient = new CardInfoGroup(ui->groupBox_page3_clientInfo);
    groupClient->move(307,34);

    timeGroupHost1_page2 = new TimeSourceGroup(ui->groupBox_page2_host1,"host");
    timeGroupHost1_page2->move(8,15);
    timeGroupHost2_page2 = new TimeSourceGroup(ui->groupBox_page2_host2,"host");
    timeGroupHost2_page2->move(8,15);

    timeGroupHost1_page1 = new TimeSourceGroup(ui->groupBox_page1_timesource,"main");
    timeGroupHost1_page1->move(17,20);
    timeGroupHost1_page1->setTitle("主机1时间源");

    timeGroupHost2_page1 = new TimeSourceGroup(ui->groupBox_page1_timesource,"main");
    timeGroupHost2_page1->move(489,20);
    timeGroupHost2_page1->setTitle("主机2时间源");

    ui->groupBox_page1_timeSource_host1->hide();
    ui->groupBox_page1_timeSource_host2->hide();

   m_bAutoSetTimeZone = false;
   /***/
   scrollText = new ScrollTextShow(ui->frame);
   scrollText->move(50,648);


   m_start = new FormStartUp(this);
   m_start->move(0,0);
#if QT_5
   connect(m_start->m_connection,&W_connection::checkData,this,&FrmMain::onCheckData);
   connect(m_start->m_keyModule,&W_keyModule::checkData,this,&FrmMain::onCheckData);
   connect(m_start->m_heatBalance,&W_heatBalance::checkData,this,&FrmMain::onCheckData);
#else
   connect(m_start->m_connection,SIGNAL(checkData()),this,SLOT(onCheckData()));
   connect(m_start->m_keyModule,SIGNAL(checkData()),this,SLOT(onCheckData()));
   connect(m_start->m_heatBalance,SIGNAL(checkData()),this,SLOT(onCheckData()));
#endif

#if IGNORE_START
   m_start->hide();
#else
   ui->tabWidget_FrmMain->hide();
#endif
   currentShow = startup;
   addItemToEventFilter();
   // 串口数据结构测试

  PreBuffer1Size  = 0;
  PreBuffer2Size  = 0;
  PreBuffer3Size  = 0;
  PreBuffer4Size  = 0;

  m_host1 = new DevInfo;
  m_host2 = new DevInfo;

  m_host1->infoChanged = true;
  m_host1->type = hostDev;
  m_host2->infoChanged = true;
  m_host2->type = hostDev;
  m_host1->msg = NULL;
  m_host2->msg = NULL;
  m_host1->id = 0;
  m_host2->id = 1;
  m_devIndex = 2;

  //qDebug()<<QString("QT版本：%1.%2.%3").arg(QT_VERSION_MAJOR).arg(QT_VERSION_MINOR).arg(QT_VERSION_PATCH);

}

FrmMain::~FrmMain()
{
    qDebug()<<"准备写配置文件"<<g_localTimeZone;
    writeConfig();
    // 处理指针
    delete m_host1;
    delete m_host2;
    for(int i=0;i<m_subDevInfoList.count();i++){
        pDevInfo t = m_subDevInfoList.at(i);
        delete t;
    }

    delete ui;
}
// 主界面初始化
void FrmMain::initMainWidget()
{
    ui->comboBox_showModel->insertItems(0,QStringList()<<"   白天模式"<<"   黄昏模式"<<"   黑夜模式");
    ui->comboBox_timeZoneDirec->insertItem(0,"自动确定时区");
    ui->comboBox_timeZoneDirec->insertItems(1,QStringList()<<"(UTC-12:00)国际日期变更线西"
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
                                            <<"(UTC+11:00)所罗门群岛"<<"(UTC+12:00)奥克兰，惠灵顿"<<"(UTC+12:00)斐济"<<"(UTC+12:00)马加丹"<<"(UTC+12:00)协调世界时+12"<<"(UTC+13:00)努库阿洛法"<<"(UTC+13:00)萨摩亚群岛");
#if 0
    for(int i=0;i<TimeZoneList.count();++i){
        QString str = TimeZoneList.at(i);
        ui->comboBox_timeZoneDirec->insertItem(i+1,);
    }
#endif
    //qDebug()<<"列表选项数"<<ui->comboBox_timeZoneDirec->count();
    ui->comboBox_workModel->insertItems(0,QStringList()<<"   自动模式"<<" 手动北斗同步"
                                        <<" 手动长波同步"<<" 手动短波同步"<<" 手动G/G同步"<<" 手动IRIGB同步");
    // 设置初始化时区
    /***********************模拟时钟设置****************************/
#if 0
    const QColor knobColor = QColor( Qt::gray ).light( 110 ); // 中心原点颜色
    for ( int i = 0; i < QwtAnalogClock::NHands; i++ )
    {
        QColor handColor = QColor( Qt::gray ).light( 80 );
        int width = 3;

        if ( i == QwtAnalogClock::SecondHand )
        {
            handColor = Qt::gray;
            width = 2;
        }

        QwtDialSimpleNeedle *hand = new QwtDialSimpleNeedle(
            QwtDialSimpleNeedle::Arrow, true, handColor, knobColor );
        QwtDialSimpleNeedle *hand1 = new QwtDialSimpleNeedle(
            QwtDialSimpleNeedle::Arrow, true, handColor, knobColor );
        hand->setWidth( width );
        hand1->setWidth(width);

        //ui->AnalogClock_1->setHand( static_cast<QwtAnalogClock::Hand>( i ), hand );
      //  ui->AnalogClock_2->setHand( static_cast<QwtAnalogClock::Hand>( i ), hand1 );
    }
    ui->AnalogClock_1->scaleDraw()->setTickLength(QwtScaleDiv::MajorTick,2);
    ui->AnalogClock_1->scaleDraw()->setTickLength(QwtScaleDiv::MinorTick,0.8);
    ui->AnalogClock_2->scaleDraw()->setPenWidth(2);
  //ui->AnalogClock_2->scaleDraw()->setScaleDiv(QwtScaleDiv::MajorTick);
    ui->AnalogClock_2->scaleDraw()->setTickLength(QwtScaleDiv::MajorTick,4);
    qDebug()<<"pen width="<<ui->AnalogClock_2->scaleDraw()->penWidth();
    qDebug()<<"主刻度长度="<<ui->AnalogClock_2->scaleDraw()->tickLength(QwtScaleDiv::MajorTick);
    qDebug()<<"主刻度长度="<<ui->AnalogClock_2->scaleDraw()->tickLength(QwtScaleDiv::MinorTick);
#endif
    m_colock1 = new AnalogClock(ui->groupBox_main_beijingtime,200,200);
    m_colock2 = new AnalogClock(ui->groupBox_main_localtime,200,200);
    m_colock1->move(260,40);
    m_colock2->move(11,40);

    /****************************************************/
    // 故障报警列表
    ui->tableWidget_breakdownInfo->setColumnWidth(0,130);
    ui->tableWidget_breakdownInfo->setColumnWidth(1,200);
    ui->tableWidget_breakdownInfo->horizontalHeader()->setStretchLastSection(true);
    // 分机状态界面
    //FormTimeSource *form = new FormTimeSource(ui->groupBox_page3_clientInfo);
   // form->move(100,100);
    //form->setItemStatus(FormTimeSource::valid);
   // showTimeSourceWidget();
#if 0
    ui->tableWidget_timeRespurce_1->horizontalHeader()->setSectionsClickable(false);
    ui->tableWidget_timeRespurce_2->horizontalHeader()->setSectionsClickable(false);
    // 调整列表列宽
    ui->tableWidget_cardBoardStatus_1->setColumnWidth(0,100);
    ui->tableWidget_cardBoardStatus_1->setColumnWidth(1,80);
    ui->tableWidget_cardBoardStatus_1->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget_cardBoardStatus_1->horizontalHeader()->setSectionsClickable(false);

    ui->tableWidget_cardBoardStatus_2->setColumnWidth(0,100);
    ui->tableWidget_cardBoardStatus_2->setColumnWidth(1,80);
    ui->tableWidget_cardBoardStatus_2->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget_cardBoardStatus_2->horizontalHeader()->setSectionsClickable(false);
#endif
}


void FrmMain::openSerialPort(QSerialPort *port,int num)
{
    QStringList strList;
    switch(num){
    case 0:
        strList = g_serialPortInfo0.split(",",QString::SkipEmptyParts);
        break;
    case 1:
        strList = g_serialPortInfo0.split(",",QString::SkipEmptyParts);
        break;
    case 2:
        strList = g_serialPortInfo0.split(",",QString::SkipEmptyParts);
        break;
    case 3:
        strList = g_serialPortInfo0.split(",",QString::SkipEmptyParts);
        break;
    default:
        writeLogInfo("打开串口时参数传入不正确");
        return;
    }
    if(strList.count() != 5){
        writeLogInfo("串口参数格式不正确，解析串口参数错误");
        return;
    }
    port->setPortName(strList.at(0));
    port->setBaudRate(handleBaudRate(strList.at(1)));
    port->setParity(handleParity(strList.at(2)));
    port->setDataBits(handleDataBits(strList.at(3)));
    port->setStopBits(handleStopBits(strList.at(4)));
    if(port->open(QIODevice::ReadWrite)){
        switch(num){
        case 0:
            connect(port,SIGNAL(readyRead()),this,SLOT(recvSerialData0()));
            break;
        case 1:
            connect(port,SIGNAL(readyRead()),this,SLOT(recvSerialData1()));
            break;
        case 2:
            connect(port,SIGNAL(readyRead()),this,SLOT(recvSerialData2()));
            break;
        case 3:
            connect(port,SIGNAL(readyRead()),this,SLOT(recvSerialData3()));
            break;
        default:
            break;
        }
    }else{
        writeLogInfo("打开串口失败，port="+port->objectName()+" portName="+strList.at(0));
    }

}

// 键盘事件响应
void FrmMain::keyPressEvent(QKeyEvent *event)
{
    handleKeyEvent(event->key());
}

// 处理键盘事件  --
void FrmMain::handleKeyEvent(int index){
    switch (index) {
    case Qt::Key_F1:
        currentShow = major;
        break;
    case Qt::Key_F2:
        currentShow= host;
        break;
    case Qt::Key_F3:
        currentShow= client;
        break;
    case Qt::Key_F4:
        currentShow= setting;
        break;
    case Qt::Key_F5:
        currentShow= help;
        break;
    case Qt::Key_F6:
        currentShow= reserved;
        break;
    case Qt::Key_Left:
        break;
    case Qt::Key_Right:
        break;
    case Qt::Key_Up:
        break;
    case Qt::Key_Down:
        break;
    case Qt::Key_Enter:
        break;
    default:
        break;
    }
    ui->tabWidget_FrmMain->setCurrentIndex(currentShow);
}

// 串口接收函数
void FrmMain::recvSerialData0()
{

    QByteArray tmp = m_serialPort0->readAll();
    recvBuffer0 += tmp;
    //CurBuffer1Size += tmp.size();
}
void FrmMain::recvSerialData1()
{
    QByteArray tmp = m_serialPort1->readAll();
    recvBuffer1 += tmp;
    //CurBuffer2Size += tmp.size();
}
void FrmMain::recvSerialData2()
{
    QByteArray tmp = m_serialPort2->readAll();
    recvBuffer2 += tmp;
    //CurBuffer3Size += tmp.size();
}
void FrmMain::recvSerialData3()
{
    QByteArray tmp = m_serialPort3->readAll();
    recvBuffer3 += tmp;
    //CurBuffer4Size += tmp.size();
}
void FrmMain::parseBuffer(int num)
{
    QByteArray btr ;
    int *size = NULL;
    switch(num){
    case 0:
        btr = recvBuffer0;
        size = &PreBuffer1Size;
        break;
    case 1:
        btr = recvBuffer1;
        size = &PreBuffer2Size;
        break;
    case 2:
        btr = recvBuffer2;
        size = &PreBuffer3Size;
        break;
    case 3:
        btr = recvBuffer3;
        size = &PreBuffer4Size;
        break;
    }
    int start = 0;
    int end1 = 0;
    if(btr.size() != *size){
        // 缓冲之中有新的数据出现
        for(int i = 0 ; i < btr.size();i++){
            char ch = btr.at(i);
            if(ch == '$'){
                start = i;
                continue;
            }
            if(ch == 0x0D){
                end1 = i;
                continue;
            }
            if(ch == 0x0A){
                if((end1 + 1) == i && end1 > start){
                    QByteArray tmp = btr.mid(start,i-start+1);
                    parseMsg(tmp);
                    btr.remove(start,i-start+1);
                    *size = btr.size();
                    start = i + 1;
                }
            }

        }
    }

}
bool checkData(QByteArray btr){
    int length = btr.length();
    if(btr.at(0) != '$' || btr.at(length-5) != '*'){
        return false;
    }
    char sum1 , sum2;
    char sum = 0;
    for(int i=1 ; i < length-5;i++){
        sum ^= btr.at(i);
    }
    sum1 = (sum>>4) & 0x0f;
    sum2 = sum & 0x0f;
    if(sum1 == btr.at(length-4) && (sum2 == btr.at(length - 3)))
        return true;
    else
        return false;
}

void FrmMain::parseMsg(QByteArray btr){
    int len = sizeof(CommonHead)+sizeof(CommonTail);
    if(btr.length() < len)
        return;
#if 0
    // 数据校验
    if(!checkData(btr)){
        return;
    }
#endif
    CommonHead *head = (pCommonHead)btr.data();
    switch (head->type) {
    case 1: //时间报文
        handleTimeInfo(btr);
        break;
    case 2: //  主机信息报文
        handleHostInfo(btr);
        break;
    case 0x03: //分机信息
        handleClientInfo(btr);
        break;
    case 0x04: //设备联通性
        handleDevConnectInfo(btr);
        break;
    case 0x05: //关键模块在线
        handleKeyMoudleInfo(btr);
        break;
    case 0x06: //标频器件热平衡
        handleStdRateInfo(btr);
        break;
    case 0x07: //故障
        handleErrInfo(btr);
        break;
    case 0x08: //
        break;
    case 0x09: //
        break;
    default:
        break;
    }
}

void FrmMain::onTimeOut()
{
    QTime time = QTime::currentTime();
    QDate date = QDate::currentDate();
    //ui->AnalogClock_1->setTime(time);
  //  ui->AnalogClock_2->setTime(time);

    setTime(time,date);
}

void FrmMain::on_comboBox_workModel_currentIndexChanged(int index)
{
    if(index == 0){
       // ui->groupBox_handModelSetting->hide();
       // ui->groupBox_parameterSetting->resize(961,191);
    }else if(index == 1){
       // ui->groupBox_handModelSetting->hide();
       // ui->groupBox_parameterSetting->resize(961,541);
    }
}
//时区选择框，列表选中位置改变
void FrmMain::on_comboBox_timeZoneDirec_currentIndexChanged(int index)
{
    if(b_firstInit)
        return;
    if(index == 0){
        m_bAutoSetTimeZone = true;
        return;
    }else
        m_bAutoSetTimeZone = false;

    g_localTimeZone = getLocalTimeZone(ui->comboBox_timeZoneDirec->itemText(index)); // 获取时区选择
    setTimeZone(g_localTimeZone);
}
void FrmMain::setTime(QTime time, QDate date)
{
    QTime time1;
    time1= time.addSecs(3600*(g_localTimeZone-8));
    QString strTime = time.toString("HH:mm:ss");
    QString strTime1 = time1.toString("HH:mm:ss");

    QString strDate = date.toString("yyyy年MM月dd日");

    m_colock1->setTime(time);
    m_colock2->setTime(time1);

    //ui->lcdNumber_localTime->display(strTime1);
    //ui->label_BeiJingTime_S->setText(strSecond);
   // ui->label_LocalTime_S->setText(strSecond);
    ui->label_BeiJingTime_HM->setText(strTime);
    ui->label_LocalTime_HM->setText(strTime1);
    ui->label_BeijingDate->setText(strDate);
    ui->label_LocalDate->setText(strDate);

    ui->label_subBeijingDate->setText(strDate);
    ui->label_subBeijingDate_2->setText(strDate);
    ui->label_subBeijingDate_3->setText(strDate);
    ui->label_subBeijingDate_4->setText(strDate);
    ui->label_subBeijingDate_5->setText(strDate);

    ui->label_subLocalDate->setText(strDate);
    ui->label_subLocalDate_2->setText(strDate);
    ui->label_subLocalDate_3->setText(strDate);
    ui->label_subLocalDate_4->setText(strDate);
    ui->label_subLocalDate_5->setText(strDate);

    ui->label_subBeijingTime_HM->setText(strTime);
    ui->label_subBeijingTime_HM_2->setText(strTime);
    ui->label_subBeijingTime_HM_3->setText(strTime);
    ui->label_subBeijingTime_HM_4->setText(strTime);
    ui->label_subBeijingTime_HM_5->setText(strTime);

    ui->label_subLocalTime_HM->setText(strTime1);
    ui->label_subLocalTime_HM_2->setText(strTime1);
    ui->label_subLocalTime_HM_3->setText(strTime1);
    ui->label_subLocalTime_HM_4->setText(strTime1);
    ui->label_subLocalTime_HM_5->setText(strTime1);

}

void FrmMain::setTimeZone(float num)
{
    QString str = getTimeZone(num);
    qDebug()<<"当前时区"<<str;
    ui->label_LocalTimeZone->setText(str);
    ui->label_subLocalTimeZone_2->setText(str);
    ui->label_subLocalTimeZone_3->setText(str);
    ui->label_subLocalTimeZone_4->setText(str);
    ui->label_subLocalTimeZone_5->setText(str);
    ui->label_subLocalTimeZone->setText(str);
}
float FrmMain::getLocalTimeZone(QString str){
    float ret = -20; // -20标识时区没有意义
    if(str == "自动确定时区")
        ret = 0;
    else{
        QString tmp = str.left(11);
        qDebug()<<tmp;
        if(tmp.at(4) == ')'){
            // UTC
            ret = 0;
        }else{
           // qDebug()<<tmp.mid(4,3).toFloat();
            int tm1 = tmp.mid(4,3).toInt();
            float tm2 = tmp.mid(8,2).toFloat()/60;
            ret = (tm1/abs(tm1))*tm2+tm1;

        }
    }
    qDebug()<<ret;
    return ret;
}
void FrmMain::showClientWidget(int num)
{
    //int widget_H = 92;
    int widget_W = 93;
    int space_W = 20;
    int space_H = 15;
    for(int i=0;i<num;i++){
        // 开始给子窗口布局
        ClientWidget *widget = new ClientWidget(ui->scrollArea);
        connect(widget,SIGNAL(focusChanged()),this,SLOT(onFocusChanged()));
        widget->move(space_W+(i)*(space_W+widget_W),space_H);
        widget->show();
        widget->setObjectName(QString("00%1").arg(i+1));
        widget->setClientName(QString("00%1").arg(i+1));
        widget->setWidgetID(i);
       // widget->setClientStatus((i%3==0?true:false));
        widget->setClientStatus(true);
        m_ClientWidgetList.append(widget);
    }
    for(int i=0;i<m_ClientWidgetList.count();i++){
        qDebug()<<"name="<<m_ClientWidgetList.at(i)->objectName();
    }
}
// 关机按钮
void FrmMain::on_pushButton_clicked()
{
    QMessageBox box(QMessageBox::Warning,"正准备关闭从机1","确定要关闭从机吗？",QMessageBox::Ok|QMessageBox::Cancel);
    box.setWindowIcon(QIcon(":/image/msg_error.png"));
    int ret = box.exec();
    if(ret == QMessageBox::Ok){
        qDebug()<<"远程关机";
    }else{
        qDebug()<<"关机取消";
    }
}
void FrmMain::addNewClient()
{
    QLabel *label = new QLabel;
    label->resize(120,80);

}

void FrmMain::onFocusChanged()
{
    qDebug()<<"上一次焦点对象"<<m_currentFocusWidget->objectName();
    QWidget * current_focus_widget = QApplication::focusWidget();
    if(m_currentFocusWidget->objectName() != current_focus_widget->objectName()){
        m_currentFocusWidget = current_focus_widget;
        qDebug()<<"焦点对象发生改变"<<m_currentFocusWidget->objectName();
        if(current_focus_widget->inherits("ClientWidget")){
            ClientWidget *w = (ClientWidget*)current_focus_widget;
            if(w->m_onLine){
                ui->label_clientWidgetStatus->setText("（在线）");
            }else{
                ui->label_clientWidgetStatus->setText("（不在线）");
            }
            ui->label_clientWidgetName->setText("分机"+w->objectName());
        }

    }
}
void FrmMain::onUpdateStyleSheet()
{

    //qApp->setStyleSheet(qss_str); // 重新加载qss文件
}
/*
void FrmMain::showTimeSourceWidget()
{
    for(int i=0;i<5;i++){
        FormTimeSource *widget = new FormTimeSource(ui->groupBox_page3_timeSource);
        switch(i){
        case 0:
            widget->setItemText("北斗");
            widget->setItemStatus(FormTimeSource::valid);
            break;
        case 1:
            widget->setItemText("IRIG-B");
            widget->setItemStatus(FormTimeSource::valid);
            break;
        case 2:
            widget->setItemText("G/G");
            widget->setItemStatus(FormTimeSource::invalid);
            break;
        case 3:
            widget->setItemText("短波");
            widget->setItemStatus(FormTimeSource::unknown);
            break;
        case 4:
            widget->setItemText("长波");
            widget->setItemStatus(FormTimeSource::valid);
            break;
        }
        widget->setProperty("deviceType","client");
        //widget->setItemStatus(FormTimeSource::valid);
        widget->setItemUsed((i==0?true:false));
        widget->move(i*(10+78)+10,25);
    }
}
*/
void FrmMain::onSureCloseRemoteDevice(QString name){
    qDebug()<<name+"即将关闭";
}

// 读取缓冲之中的数据
void FrmMain::onCheckData()
{
    // 读取缓冲之中的数据
    parseBuffer(0);
    parseBuffer(1);
    parseBuffer(2);
    parseBuffer(3);
}

void FrmMain::addItemToEventFilter()
{
    ui->comboBox_showModel->installEventFilter(this);
    ui->comboBox_timeZoneDirec->installEventFilter(this);
    ui->comboBox_workModel->installEventFilter(this);
}

bool FrmMain::eventFilter(QObject *watched, QEvent *event)
{
    if(watched->inherits("QComboBox"))
    {
        //qDebug()<<watched->objectName()<<event->type();
        if(event->type() == QEvent::KeyPress){
            qDebug()<<"触发了键盘事件";
            QKeyEvent *e = static_cast<QKeyEvent*>(event);
            qDebug()<<e->key();
            if(e->key() == Qt::Key_Enter || e->key() == Qt::Key_Return){
                QComboBox *com = static_cast<QComboBox*>(watched);
                com->showPopup();
                return true;
            }
        }

    }else{
        qDebug()<<"没有触发下拉列表控件";
    }
    return QWidget::eventFilter(watched,event);
}



/***************************************************************/
// 数据处理函数
// 处理时间信息报文
void FrmMain::handleTimeInfo(QByteArray btr)
{
    pTimeMsg msg = (pTimeMsg)btr.data();
    C_Time time = msg->time;
    m_time.fromString(QString().sprintf("%02d:%02d:%02d",time.hour,time.minute,time.second),
                    "hh:mm:ss");
    m_date.fromString(QString().sprintf("%04d:%02d:%02d",time.year,time.month,time.day),
                    "yyyy-MM-dd");
}
// 处理主机信息报文
void FrmMain::handleHostInfo(QByteArray btr)
{
    pHostMsg msg = (pHostMsg) btr.data();
    //bool flag = false;
    pDevInfo info = msg->hostNum.num == 0 ? m_host1: m_host2;

    if(memcmp(info->msg,msg,sizeof(HostMsg))){
         updateHostInfo(info,msg);
    }

}
// 处理分机信息报文
void FrmMain::handleClientInfo(QByteArray btr)
{
    pClientMsg msg = (pClientMsg)btr.data();
    bool newDev = true;
    for(int i=0 ; i< m_subDevInfoList.count();i++){
        pDevInfo tmp = m_subDevInfoList.at(i);
        if(tmp->devNum == msg->clientNum.num){
            newDev = false;
            updateClientInfo(tmp,msg);
            break;
        }
    }
    if(newDev){
        pDevInfo subdevice = new DevInfo;
        subdevice->id = m_devIndex++;
        updateClientInfo(subdevice,msg);
        m_subDevInfoList.append(subdevice);
    }
}
// 处理设备联通性报文
void FrmMain::handleDevConnectInfo(QByteArray btr)
{
    int nDev = btr.at(4); // 获取未联通设备数量
    char * msg = btr.data();
    int len = btr.length();
    uchar connectFlag = btr.at(len - 6); // 获取是否联通的标志
    if(connectFlag == 0 && nDev == 0) // 标志正确，没有需要处理的设备
    {
        m_bDeviceConnected = true;
        qDebug()<<"设备完全联通";
    }else{
        m_bDeviceConnected = false;
        qDebug()<<"设备未完全联通";
    }
    int size = sizeof(CommonHead)+sizeof(CommonTail)+4;
    // 判断数据长度是否正确
    if(len != nDev+size)
    {
        qDebug()<<"设备联通报文长度有误"<<"理论长度"<<nDev+size<<"实际长度"<<nDev;
    }
    uchar devList[nDev];
    memcpy(devList,msg+sizeof(CommonHead)+2,nDev);
    for(int i = 0; i< nDev ; ++i)
    {
        // 界面上添加未联通的设备信息

    }
}
// 处理关键模块在线报文
void FrmMain::handleKeyMoudleInfo(QByteArray btr)
{
    int nDev = btr.at(4); // 获取不在线的关键模块的数目
    char * msg = btr.data();
    int len = btr.length(); // 数据长度
    uchar connectFlag = btr.at(len - 6); // 获取是否全部在线的标志
    if(connectFlag == 0 && nDev == 0) // 标志正确，没有需要处理的设备
    {
        m_bKeyModuleOnLine = true;  // 更改设备连通性标志
        qDebug()<<"设备未完全联通";
    }else{
        m_bKeyModuleOnLine = false;
        qDebug()<<"设备未完全联通";
    }
    int size = sizeof(CommonHead)+sizeof(CommonTail)+4;

    // 判断数据长度是否正确
    if(len != nDev+size)
    {
        qDebug()<<"设备联通报文长度有误"<<"理论长度"<<nDev+size<<"实际长度"<<nDev;
    }
    uchar keyModule[nDev];
    memcpy(keyModule,msg+size-2,nDev);
    for(int i = 0; i< nDev ; ++i){
        // 界面上显示不在线关键模块信息
    }
}
// 处理标频器件热平衡
void FrmMain::handleStdRateInfo(QByteArray btr)
{
    W_heatBalance * wBalance = m_start->m_heatBalance;
    int nDev = btr.at(4); // 获取标频器件数量
    char * msg = btr.data();
    int len = btr.length(); // 数据长度
    uchar balanceFlag = btr.at(len - 6); // 获取是否全部热平衡的标志
    if(balanceFlag == 0 && nDev == 0) // 标志正确，没有需要处理的设备
    {
       // m_bStdFreqHeatBalance = true; // 更改热平衡标志
        wBalance->setAllDevStatus(true);
        qDebug()<<"设备未完全联通";
    }else{
        // m_bStdFreqHeatBalance = false;
        wBalance->setAllDevStatus(false);
        qDebug()<<"设备未完全联通";
    }
    int size = sizeof(CommonHead)+sizeof(CommonTail)+4;
    // 判断数据长度是否正确
    if(len != nDev+size)
    {
        qDebug()<<"设备联通报文长度有误"<<"理论长度"<<nDev+size<<"实际长度"<<nDev;
    }
    StdRDInfo devInfo[nDev] ;
    memcpy(devInfo,msg+sizeof(CommonHead)+2,nDev*sizeof(StdRDInfo));
    // 遍历标频器件信息更新标频器件数目
    for(int i = 0;i<nDev ; ++i)
    {
        StdRDInfo tmpInfo = devInfo[i];
        W_heatBalance::moudleInfo  info;
        info.id = tmpInfo.num.num + (tmpInfo.num.code<<7); // 确定器件编号 ID
        info.type = tmpInfo.num.code == 0 ? 'H' : 'C'; // 确定器件类型
        info.number = tmpInfo.num.num; // 设备编号
        info.balance = tmpInfo.status.code == 0 ? true : false; // 器件是否热平衡
        info.time = tmpInfo.time; // 器件加热时间  ？？
        info.crystalNum =  info.type == 'H' ?((tmpInfo.num.num & 0x10) > 0 ? 2 : 1) : 0;
        info.tempera = tmpInfo.status.num; // 获取设备温度数值

        int num = wBalance->getStdRateDevsCount(); // 获取标频器件的数
        bool newDevFlag = true;
        for(int i = 0 ; i < num ; i++){
            if(info.id == wBalance->getStdRateDevId(i)){
                // id 相同 更新器件信息
                newDevFlag = false;
                wBalance->updateStdRateDevInfo(i,info);
                break;
            }
        }
        if(newDevFlag){
            // 原有列表之中没有匹配ID的标频器件
            wBalance->addNewStdRateDev(info);
        }
    }
}
// 处理故障报文
void FrmMain::handleErrInfo(QByteArray btr)
{
    pErrMsg msg = (pErrMsg) btr.data();
    C_Time time = msg->time;
    errorInfo info;
    int nHandleErr = 0;
    bool newinfo = true;
    QString strTime = QString().sprintf("%04d-%02d-%02d %02d:%02d:%02d",
                                    time.year,time.month,time.day,
                                    time.hour,time.minute,time.second);
    for(int i=0 ; i<g_errorList.count();i++)
    {
        errorInfo tmp = g_errorList.at(i);
        if(tmp.errCode == msg->errCode)
        {
            newinfo = false;
            // 是同一个故障
            if(tmp.isHandled == false)
            {
                if(msg->handled == 1) // 故障解决
                {
                    tmp.isHandled = true;   // 故障信息
                    tmp.timeEnd = strTime;  // 填入故障解决时间
                    g_errorList.replace(i,tmp); // 替换原有文件
                }else // 故障未解决
                {
                    break;
                }
            }else
            {
                if(msg->handled == 0) // 之间的故障已解决又出现新的故障信息
                {
                    info.id = errorInfoID++;
                    info.isHandled = false;
                    info.timeStart = strTime;
                    info.str = getStrErrInfo(msg->errCode);
                    info.errCode = msg->errCode;
                    info.timeEnd = strTime;
                    g_errorList.append(info);
                }else{
                    break;
                }
            }
        }
    }
    if(newinfo){
        // 故障列表之中添加新的数据
        if(msg->handled == 1){
            return;
        }
        info.id = errorInfoID++;
        info.isHandled = false;
        info.errCode = msg->errCode;
        info.str = getStrErrInfo(msg->errCode);
        info.timeStart = strTime;
        info.timeStart = strTime;

        g_errorList.append(info);
    }
    // 清理故障列表中已经解决的问题
    for(int i = 0 ; i< g_errorList.count();i++){
        if(g_errorList.at(i).isHandled){
            nHandleErr++;
        }
    }
    if(nHandleErr > ErrMsgSizeMAX){
        for(int i = 0;i<g_errorList.count();i++){
            if(g_errorList.at(i).isHandled){
                g_errorList.removeAt(i);
                break;
            }
        }
    }
}

// 更新主机信息界面的数据
void FrmMain::updateHostInfo(pDevInfo info,pHostMsg msg )
{
    // 时间源信息更新
    info->timeSource.source1_status = msg->timeStatus.beidou == 0 ? invalid : valid;
    info->timeSource.source1_used = msg->timeUsed.beidou == 0 ? false : true;
    info->timeSource.source2_status = msg->timeStatus.B_code == 0 ? invalid : valid;
    info->timeSource.source2_used = msg->timeUsed.B_code == 0 ? false : true;
    info->timeSource.source3_status = msg->timeStatus.GPS_G == 0 ? invalid : valid;
    info->timeSource.source3_used = msg->timeUsed.GPS_G == 0 ? false : true;
    info->timeSource.source4_status = msg->timeStatus.sWave == 0 ? invalid : valid;
    info->timeSource.source4_used = msg->timeUsed.sWave == 0 ? false : true;
    info->timeSource.source5_status = msg->timeStatus.lWave == 0 ? invalid : valid;
    info->timeSource.source5_used = msg->timeUsed.lWave == 0 ? false : true;
    // 系统信息
    info->clock_1.crystalLocked = msg->RbclockStatus.clock1_locked == 0 ? false : true;
    info->clock_1.systemLocked = msg->RbclockStatus.clock1_sysLocked == 0 ? false : true;
    info->clock_1.timeOffset = msg->clock1TimeOffset;
    info->clock_1.temperature = msg->clock1Tempera;
    info->clock_2.crystalLocked = msg->RbclockStatus.clock2_locked == 0 ? false : true;
    info->clock_2.systemLocked = msg->RbclockStatus.clock2_sysLocked == 0 ? false : true;
    info->clock_2.timeOffset = msg->clock2TimeOffset;
    info->clock_2.temperature = msg->clock2Tempera;
    // 电源信息
    info->powerFrom = getStrPowerInfo(0,msg->powerInfo);
    info->powerStatus = getStrPowerInfo(1,msg->powerInfo);
    // 板卡信息
   // fillCardInfo(info,msg);
    info->serial1Card.status = msg->serial1.status.status == 0 ? valid: invalid;
    info->serial1Card.tempera = msg->serial1.tempera;
    info->serial1Card.describe = getStrCardInfo(msg->serial1.status.errCode);
    info->serial2Card.status = msg->serial2.status.status == 0 ? valid: invalid;
    info->serial2Card.tempera = msg->serial2.tempera;
    info->serial2Card.describe = getStrCardInfo(msg->serial2.status.errCode);
    info->stdRateCard.status = msg->stdRate.status.status == 0 ? valid: invalid;
    info->stdRateCard.tempera = msg->stdRate.tempera;
    info->stdRateCard.describe = getStrCardInfo(msg->stdRate.status.errCode);
    info->keepTimeCard.status = msg->keepTime.status.status == 0 ? valid: invalid;
    info->keepTimeCard.tempera = msg->keepTime.tempera;
    info->keepTimeCard.describe = getStrCardInfo(msg->keepTime.status.errCode);
    info->rateCutCard.status = msg->shutRate.status.status == 0 ? valid: invalid;
    info->rateCutCard.tempera = msg->shutRate.tempera;
    info->rateCutCard.describe = getStrCardInfo(msg->shutRate.status.errCode);
    info->controlCard.status = msg->control.status.status == 0 ? valid: invalid;
    info->controlCard.tempera = msg->control.tempera;
    info->controlCard.describe = getStrCardInfo(msg->control.status.errCode);
    info->computerCard.status = msg->computer.status.status == 0 ? valid: invalid;
    info->computerCard.tempera = msg->computer.tempera;
    info->computerCard.describe = getStrCardInfo(msg->computer.status.errCode);
    info->networkCard.status = msg->net.status.status == 0 ? valid: invalid;
    info->networkCard.tempera = msg->net.tempera;
    info->networkCard.describe = getStrCardInfo(msg->net.status.errCode);
    info->testCard.status = msg->test.status.status == 0 ? valid: invalid;
    info->testCard.tempera = msg->test.tempera;
    info->testCard.describe = getStrCardInfo(msg->test.status.errCode);

    // 原始数据信息
    memcpy(info->msg,msg,sizeof(HostMsg));
}
void FrmMain::updateClientInfo(pDevInfo info, pClientMsg msg)
{
    info->type = subDev;
    info->devNum = msg->clientNum.num;  // 分机编号
    info->sysLocked = msg->Status.syslocked == 0 ? false :true ;
    info->crstalLocked = msg->Status.crystalStatus == 0 ? false : true;
    info->isOnline = msg->Status.online == 0 ? false : true ;
    info->refSrc = getStrSubDevRefSrc(msg->Status.timeRefSrc);
    info->timeOffset = msg->clockTimeOffset;
    info->tempera = msg->clockTempera;
    info->powerFrom = getStrPowerInfo(0,msg->powerInfo);
    info->powerStatus = getStrPowerInfo(1,msg->powerInfo);
    // 板卡信息
    //fillCardInfo(info,msg);
    info->serial1Card.status = msg->serial1.status.status == 0 ? valid: invalid;
    info->serial1Card.tempera = msg->serial1.tempera;
    info->serial1Card.describe = getStrCardInfo(msg->serial1.status.errCode);
    info->serial2Card.status = msg->serial2.status.status == 0 ? valid: invalid;
    info->serial2Card.tempera = msg->serial2.tempera;
    info->serial2Card.describe = getStrCardInfo(msg->serial2.status.errCode);
    info->stdRateCard.status = msg->stdRate.status.status == 0 ? valid: invalid;
    info->stdRateCard.tempera = msg->stdRate.tempera;
    info->stdRateCard.describe = getStrCardInfo(msg->stdRate.status.errCode);
    info->keepTimeCard.status = msg->keepTime.status.status == 0 ? valid: invalid;
    info->keepTimeCard.tempera = msg->keepTime.tempera;
    info->keepTimeCard.describe = getStrCardInfo(msg->keepTime.status.errCode);
    info->rateCutCard.status = msg->shutRate.status.status == 0 ? valid: invalid;
    info->rateCutCard.tempera = msg->shutRate.tempera;
    info->rateCutCard.describe = getStrCardInfo(msg->shutRate.status.errCode);
    info->controlCard.status = msg->control.status.status == 0 ? valid: invalid;
    info->controlCard.tempera = msg->control.tempera;
    info->controlCard.describe = getStrCardInfo(msg->control.status.errCode);
    info->computerCard.status = msg->computer.status.status == 0 ? valid: invalid;
    info->computerCard.tempera = msg->computer.tempera;
    info->computerCard.describe = getStrCardInfo(msg->computer.status.errCode);
    info->networkCard.status = msg->net.status.status == 0 ? valid: invalid;
    info->networkCard.tempera = msg->net.tempera;
    info->networkCard.describe = getStrCardInfo(msg->net.status.errCode);
    info->testCard.status = msg->test.status.status == 0 ? valid: invalid;
    info->testCard.tempera = msg->test.tempera;
    info->testCard.describe = getStrCardInfo(msg->test.status.errCode);
}


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
