#include "formstartup.h"
#include "ui_formstartup.h"

QStringList g_timeSoureNameList;

FormStartUp::FormStartUp(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormStartUp)
{
    ui->setupUi(this);
    // 时间源名称
    g_timeSoureNameList<<"北斗"<<"B时间码"<<"GPS/GLONASS"<<"短波"<<"长波";
    m_connection = new W_connection(ui->groupBox_infoShow);
    m_keyModule = new W_keyModule(ui->groupBox_infoShow);
    m_timeSource = new W_timeSource(ui->groupBox_infoShow);
    m_heatBalance = new W_heatBalance(ui->groupBox_infoShow);

    // 窗口循环初始化
    m_widgetLoop.append(m_connection);
    m_widgetLoop.append(m_keyModule);
    m_widgetLoop.append(m_heatBalance);

    //m_second = 0;
    //m_timer = new QTimer();
    // connect(m_timer,&QTimer::timeout,this,&FormStartUp::onTimerOut);
    //m_timer->start(1000);

    // 时间源标签清空
    ui->label_timeSource->clear();

    m_bConnect = false;
    m_bHeatBalance = false;
    m_bTimeSource = false;
    m_bConnect = false;
    m_showOrder = 0x0f;  // 00001111B 四个bit分别标志四个界面 0 隐藏 1 显示

    m_connection->hide();
    m_keyModule->hide();
    m_heatBalance->hide();
    m_timeSource->hide();

    m_curShowWidget = 0; // 当前正在显示的窗口
    showNextWidget(0);

}

FormStartUp::~FormStartUp()
{
    delete ui;
}
// 选择时间源
void FormStartUp::onTimeSourceSelectChanged(qint8 time)
{
    int flag = 5;
    for(int i=0;i<5;++i){
        if(time & 0x01<<i){
            flag = i;
            break;
        }
    }
    if(flag == 5){
        qDebug()<<"时间源选择完成信号不真确，时间源信息 = "<<time;
        return;
    }

    m_showOrder &= 0x0E;  // 最低位置0;
    m_bTimeSource = true;
    ui->label_timeSource->setText(g_timeSoureNameList.at(flag));

    /* 时间源选择报文发送 */

    // 时间源选择界面隐藏
    //m_timeSource->hide();
    showNextWidget(1);  // 从bit1开始检查标志位的信息
}
void FormStartUp::onWidgetHideStatusChanged(int index){
    Q_UNUSED(index);

}
// 接收到全部子界面满足要求或者当前界面显示时间结束，进行下一个界面显示
void FormStartUp::onDevStatusChanged(int index ,bool arg){
    if(!arg){
        //showNextWidget(m_curShowWidget+1);   // 标志false 定时器时间到了
        // 标志位为false不做处理
        showNextWidget(index+1);
    }else{

        if(index>3)
        {
            qDebug()<<"接收到了未知的信号";
        }else{
            setSubWidgetHideStatus(index);
        }
    }
}
// 设置子界面的状态
void FormStartUp::setSubWidgetHideStatus(int index)
{
    switch(index){
    case 1:
        m_bConnect = true;
        //m_connection->hide(); // 隐藏设备连接界面
        m_showOrder &= 0x0D;
        if(m_bTimeSource && m_curShowWidget == 1)   // 时间源选择完毕+当前界面正在显示
            showNextWidget(2);  // 从bit2开始检查标志位的信息
        break;
    case 2:
        m_bKeyMoudle = true;
       // m_keyModule->hide();  // 隐藏关键模块界面
        m_showOrder &= 0x0b;
        if(m_bTimeSource && m_curShowWidget == 2 )
            showNextWidget(3);  // 从bit3开始检查标志位的信息
        break;
    case 3:
        m_bHeatBalance = true;
        //m_heatBalance->hide(); // 隐藏热平衡界面
        m_showOrder &= 0x07;
        if(m_bTimeSource && m_curShowWidget == 3)
            showNextWidget(1); // 从bit1开始检查标志位的信息
        break;
    default:
        break;
    }
}

// index 下标的起点
void FormStartUp::showNextWidget(int index)
{
    int flag = 4;
    for(int i=index ;  i< 4+index ; ++i){
        if(m_showOrder & (0x01 << (i % 4)))
        {
            flag = i % 4;
            break;
        }
    }
    // 根据标志判断下一个应该显示的界面
    switch (flag) {
    case 0:
        m_timeSource->show();
        m_timeSource->m_timer->start(); // 开启内置定时器
        m_connection->hide();
        m_keyModule->hide();
        m_heatBalance->hide();
        break;
    case 1:
        m_timeSource->hide();
        m_connection->show();
        m_connection->m_timer->start();
        m_keyModule->hide();
        m_heatBalance->hide();
        break;
    case 2:
        m_timeSource->hide();
        m_connection->hide();
        m_keyModule->show();
        m_keyModule->m_timer->start();
        m_heatBalance->hide();
        break;
    case 3:
        m_timeSource->hide();
        m_connection->hide();
        m_keyModule->hide();
        m_heatBalance->show();
        m_heatBalance->m_timer->start();
        break;
    case 4:
        // 说明启动条件全部满足进行下一项主界面显示
        break;
    default:
        qDebug()<<"界面显示标志出错，flag = "<<flag;
        break;
    }
}


/***************************************************************/
// 时间源对象
TimeSourceFrame::TimeSourceFrame(QWidget * parent ,TimeType type ,bool start )
    :QWidget(parent),m_isInStartUP(start),m_itemType(type)
{
     m_curModle = day;  // 默认模式为白天模式
     QPixmap pix; // 加载图片

    if(m_isInStartUP){
        // 在启动阶段
        switch (m_itemType) {
        case 0:
            pix.load("");
            break;
        case 1:
            pix.load("");
            break;
        case 2:
            pix.load("");
            break;
        case 3:
            pix.load("");
            break;
        case 4:
            pix.load("");
            break;
        default:
            break;
        }
    }else{
        switch (m_itemType) {
        case 0:
            pix.load("");
            break;
        case 1:
            pix.load("");
            break;
        case 2:
            pix.load("");
            break;
        case 3:
            pix.load("");
            break;
        case 4:
            pix.load("");
            break;
        default:
            break;
        }
    }
    m_icon = new QLabel(this);
    m_icon->move(0,0);
    m_icon->setPixmap(pix);
    m_icon->setScaledContents(true);


}
void TimeSourceFrame::onShowModleChanged(int index){
    if(index < 0 || index > 2){
        qDebug()<<QString("showModle num wrong ,num = %1").arg(index);
    }
    m_curModle = static_cast<showModle>(index);

    // setItemChecked(m_itemChecked);
    // 重新设置时间源图标的样子
    setItemUsed(m_itemUsed);
    setItemValid(m_itemValid);
}

void TimeSourceFrame::setItemChecked(bool state){
    if(!m_isInStartUP)
        return ;  // 只有启动阶段才有选中状态
    this->setStyleSheet("");  // 更换背景图片
}
void TimeSourceFrame::setItemUsed(bool state){
    if(m_isInStartUP)
        return;  // 启动阶段没有该状态
    QPixmap pix;
    switch (m_curModle) {
    case day:
        pix.load("");
        break;
    case dusk:
        pix.load("");
        break;
    case night:
        pix.load("");
        break;
    default:
        break;
    }
    m_icon->setPixmap(pix);
    m_icon->setScaledContents(true);
}

void TimeSourceFrame::setItemValid(bool state){
    if(m_isInStartUP)
        return ;  // 启动阶段没有必要使用本方法

    QPixmap pix;
    switch (m_curModle) {
    case day:
        pix.load("");
        break;
    case dusk:
        pix.load("");
        break;
    case night:
        pix.load("");
        break;
    default:
        break;
    }
    m_icon->setPixmap(pix);
    m_icon->setScaledContents(true);
}
/***************************************************************/
// 时间源选择界面
W_timeSource::W_timeSource(QWidget *parent):
    QWidget(parent)
{
    // 显示页面标题框
    // 添加五个时间源
    m_item0 = new TimeSourceFrame(this,TimeSourceFrame::beidou,true);
    m_item1 = new TimeSourceFrame(this,TimeSourceFrame::Bcode,true);
    m_item2 = new TimeSourceFrame(this,TimeSourceFrame::GPS,true);
    m_item3 = new TimeSourceFrame(this,TimeSourceFrame::ShortWave,true);
    m_item4 = new TimeSourceFrame(this,TimeSourceFrame::LongWave,true);
    //添加时间过滤
    m_item0->installEventFilter(this);
    m_item1->installEventFilter(this);
    m_item2->installEventFilter(this);
    m_item3->installEventFilter(this);
    m_item4->installEventFilter(this);
    // 初始化参数
    this->setFocusProxy(m_item0);  // 默认选择北斗作为时间源
    m_item0->setItemChecked(true);
    m_state = 0x01;
    // 添加确认按钮
    m_confirmBtn = new QPushButton(this);
    m_confirmBtn->move(0,0);  // 按钮摆放位置

    connect(m_confirmBtn,SIGNAL(clicked()),this,SLOT(onConfirmBtnClicked()));

}
// 显示选择时间剩余的时间
void W_timeSource::showLastTime()
{

}

W_timeSource::~W_timeSource()
{}

bool W_timeSource::eventFilter(QObject *watcher, QEvent *event){
    if(watcher->inherits("TimeSourceFrame")){
        // 只处理时间源元素的事件
        TimeSourceFrame *frame = dynamic_cast<TimeSourceFrame*>(watcher);
        if(frame == m_item0){
            if(event->type() == QEvent::FocusIn){
                // 选中元素
                m_item0->setItemChecked(true);
                m_state  = 0x01;
            }else if(event->type() == QEvent::FocusOut){
                // 没有选中
                m_item0->setItemChecked(false);
            }
            return true;
        }else if(frame == m_item1){
            if(event->type() == QEvent::FocusIn){
                m_item1->setItemChecked(true);
                m_state  = 0x02;
            }else if(event->type() == QEvent::FocusOut){
                m_item1->setItemChecked(false);
            }
            return true;
        }else if(frame == m_item2){
            if(event->type() == QEvent::FocusIn){
                m_item2->setItemChecked(true);
                m_state  = 0x04;
            }else if(event->type() == QEvent::FocusOut){
                m_item2->setItemChecked(false);
            }
            return true;
        }else if(frame == m_item3){
            if(event->type() == QEvent::FocusIn){
                m_item3->setItemChecked(true);
                m_state  = 0x08;
            }else if(event->type() == QEvent::FocusOut){
                m_item3->setItemChecked(false);
            }
            return true;
        }else if(frame == m_item4){
            if(event->type() == QEvent::FocusIn){
                m_item4->setItemChecked(true);
                m_state  = 0x10;
            }else if(event->type() == QEvent::FocusOut){
                m_item4->setItemChecked(false);
            }
            return true;
        }
    }
    return QWidget::eventFilter(watcher,event);
}

void W_timeSource::onConfirmBtnClicked(){
    // 显示确认框？

    emit selectChanged(m_state);
    m_timer->stop();
    m_second = timeSourceSlectTime;
}

void W_timeSource::onTimeOut()
{
    // 显示时间源选择确认信息？

    m_second --;
    if(m_second == 0){
        this->hide();
        m_timer->stop(); // 停止定时器
        m_second = timeSourceSlectTime;
        emit selectChanged(m_state);
    }
}
// 连接性判断
W_connection::W_connection(QWidget *parent):
    QWidget(parent)
{
    time_count = singleWidgetShowMaxTime;  // 倒计时时长设定
    m_timer = new QTimer(this);
    connect(m_timer,SIGNAL(timeout()),this,SLOT(onTimeOut()));
    m_timer->setInterval(timerTimeOut);
}
W_connection::~W_connection()
{

}

// 关键模块在线判断
W_keyModule::W_keyModule(QWidget *parent):
    QWidget(parent)
{
    time_count = singleWidgetShowMaxTime;
    m_timer = new QTimer(this);
    connect(m_timer,SIGNAL(timeout()),this,SLOT(onTimeOut()));
    m_timer->setInterval(timerTimeOut);
}
W_keyModule::~W_keyModule()
{}

// 热平衡界面
W_heatBalance::W_heatBalance(QWidget *parent):
    QWidget(parent)
{
    time_count = singleWidgetShowMaxTime;
    m_timer = new QTimer(this);
    connect(m_timer,SIGNAL(timeout()),this,SLOT(onTimeOut()));
    m_timer->setInterval(timerTimeOut);

    m_devNum = 0;
    pos_x = 21;
    pos_y = 101;
    QFont font1;
    font1.setFamily("微软雅黑");
    QFrame *fram1 = new QFrame(this);
    fram1->resize(21,21);
    fram1->move(30,60);
    fram1->setStyleSheet("background-color:#0000ff");
    QFrame *fram2 = new QFrame(this);
    fram2->resize(21,21);
    fram2->move(120,60);
    fram2->setStyleSheet("background-color:#ff0000");
    QLabel *lab1 = new QLabel(this);
    lab1->resize(171,31);
    lab1->move(173,15);
    lab1->setText("标频器件热平衡");
    font1.setPointSize(13);
    lab1->setFont(font1);
#if 0
    QLabel *lab2 = new QLabel(this);
    lab2->resize(51,16);
    lab2->move(56,63);
    lab2->setText("已热平衡");
    font1.setPointSize(9);
    lab2->setFont(font1);
    QLabel *lab3 = new QLabel(this);
    lab3->resize(51,16);
    lab3->move(146,63);
    lab3->setText("未热平衡");
    lab3->setFont(font1);
#endif
}
W_heatBalance::~W_heatBalance()
{}

void W_heatBalance::StdRateMoudleStatusChanged(int index, QByteArray btr)
{
    QList<QByteArray> list = btr.split(',');
    for(int i=0;i<m_MoudleList.count();i++)
    {
        QFrame *frame = (QFrame*)m_MoudleList.at(i);
        if(frame->property("ID").toInt() == index){

        }
    }
}

#if 0
void W_heatBalance::addStdRateMoudle(int index, moudleInfo info)
{
    itemNum ++;
    QList<QByteArray> list = btr.split(',');

    QString name;
    if(info.type == 'H')
        name.sprintf("主机%d原子钟%d",info.number,info.crystalNum);
    else
        name.sprintf("分机%d高稳晶振",info.number);
    modelFrame *module = new modelFrame(this,name);

    module->move(pos_x,pos_y);
    module->setProperty("ID",index);
    qDebug()<<info.balance;
    module->setFrameColor(info.balance);
    m_MoudleList.append(module);

    if(itemNum %3 == 0){
        pos_x = 21;
        pos_y += 80;
    }else{
        pos_x += 171;
    }
}
#endif
// 添加标频器件元素
void W_heatBalance::addNewStdRateDev(MoudleInfo info)
{
    m_devNum ++;
    QString name;
    if(info.type == 'H')
        name.sprintf("主机%d原子钟%d",info.number,info.crystalNum);
    else
        name.sprintf("分机%d高稳晶振",info.number);
    StdRateModuleFrame *module = new StdRateModuleFrame(this,name,info.id);
    module->move(pos_x,pos_y);
    module->setProperty("ID",info.id);
    qDebug()<<info.balance;
    module->setFrameColor(info.balance);
    m_MoudleList.append(module);
    if(m_devNum %3 == 0){
        pos_x = 21;
        pos_y += 80;
    }else{
        pos_x += 171;
    }
}
// 更新标频器件元素
bool W_heatBalance::updateStdRateDevInfo(int index, MoudleInfo info)
{
    //int ret = false;
    if(index > m_MoudleList.count()-1){
        return false; // 判断代号是否越界
    }
    StdRateModuleFrame *frame = m_MoudleList.at(index);
    // 更新图标信息
    frame->setFrameColor(info.balance);

    return true;
}
