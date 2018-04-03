#include "clientwidget.h"
#include "ui_clientwidget.h"

ClientWidget::ClientWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ClientWidget)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);
    //this->setStyleSheet("background-color:blue");
    m_valid = new QPixmap;
    m_invalid = new QPixmap;
    m_invalid->load(":/image/clientInvalid.png");
    m_valid->load(":/image/clientValid.png");
    ui->label_icon->setPixmap(*m_invalid);
    ui->label_icon->setScaledContents(true);
    ui->label->setText("001");
    this->setFocusPolicy(Qt::StrongFocus);
    ui->frame->setFrameShape(QFrame::NoFrame);
    m_widgetID = 0;
    m_onLine = false;
}

ClientWidget::~ClientWidget()
{
    delete ui;
}
//设置窗口名称
void ClientWidget::setClientName(QString name)
{
    ui->label->setText(name);
}
// 设置窗口状态
void ClientWidget::setClientStatus(bool valid)
{
    m_onLine = valid;
    if(valid){
        ui->label_icon->setPixmap(*m_valid);
    }else{
        ui->label_icon->setPixmap(*m_invalid);
    }
}
// 设置序号
void ClientWidget::setWidgetID(int index){
    m_widgetID = index;
}

// 焦点集中在本对象
void ClientWidget::focusInEvent(QFocusEvent *event)
{
    qDebug()<<this->objectName()<<event->type();
   ui->frame->setFrameShape(QFrame::Box);
   ui->frame->setStyleSheet("background-color:rgb(80, 163, 241)");
   emit focusChanged();
}
// 焦点离开本对象
void ClientWidget::focusOutEvent(QFocusEvent *event)
{
     qDebug()<<this->objectName()<<event->type();
    ui->frame->setFrameShape(QFrame::NoFrame);
    ui->frame->setStyleSheet("background-color:rgb(203, 203, 203)");
}

void ClientWidget::onClientNameChanged(QString name)
{
    ui->label->setText(name);
}
void ClientWidget::onClientStatusChanged(bool status)
{
    if(status){
        ui->label_icon->setPixmap(*m_valid);
    }else{
        ui->label_icon->setPixmap(*m_invalid);
    }
}
