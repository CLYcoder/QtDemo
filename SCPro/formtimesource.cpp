#include "formtimesource.h"
#include "ui_formtimesource.h"
#include <QDebug>
#include <QPixmap>

FormTimeSource::FormTimeSource(QWidget *parent, QString belongWidget) :
    QWidget(parent),
    ui(new Ui::FormTimeSource)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::Widget);
   // ui->frame->setProperty("itemType","timeSource");
   // ui->label->setProperty("itemType","timeSource");
    ui->frame->setProperty("timeStatus",1);
    ui->label_2->setPixmap(QPixmap(":/image/timeIcon3.png"));
    ui->label_2->setScaledContents(true);
    this->setProperty("belongWidget",belongWidget);
    ui->label_3->hide();
    ui->label->move(7,42);
}

FormTimeSource::~FormTimeSource()
{
    delete ui;
}

void FormTimeSource::setItemText(QString text)
{

    if(text == "G/G"){
        ui->label->setText("GPS");
        ui->label_3->setText("GLONASS");
        ui->label_3->show();
        ui->label->move(7,35);
    }else{
        ui->label->setText(text);
    }
}

QString FormTimeSource::ItemText()
{
    return ui->label->text();
}

void FormTimeSource::setItemStatus(Status status){
    if(status == valid){
        ui->frame->setProperty("timeStatus",2);
        ui->label->setStyleSheet("color:#000080;");
        ui->label_3->setStyleSheet("color:#000080;");
    }else if(status == invalid){
        ui->frame->setProperty("timeStatus",0);
        ui->label->setStyleSheet("color:#939393;");
        ui->label_3->setStyleSheet("color:#939393;");
    }else{
        ui->frame->setProperty("timeStatus",1);
        ui->label->setStyleSheet("color:#000000;");
    }
}

FormTimeSource::Status FormTimeSource::ItemStatus()
{
    return static_cast<Status>(ui->frame->property("timeStatus").toInt());
}

void FormTimeSource::setItemUsed(bool used)
{
    if(used){
        ui->label_2->show();
    }else{
        ui->label_2->hide();
    }
}
bool FormTimeSource::isItemUsed()
{
    return !ui->label_2->isHidden();
}
