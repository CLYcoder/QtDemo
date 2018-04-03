#include "formstatus.h"
#include "ui_formstatus.h"

FormStatus::FormStatus(VlcMediaPlayer* player,QWidget *parent) :
    QWidget(parent),m_pPlayer(player),
    ui(new Ui::FormStatus)
{
    ui->setupUi(this);
    ui->player_seek->setMediaPlayer(m_pPlayer);
    isPlaying = false;
    connect(ui->btn_pause,&QPushButton::clicked,m_pPlayer,&VlcMediaPlayer::togglePause);
    connect(ui->btn_stop,&QPushButton::clicked,m_pPlayer,&VlcMediaPlayer::stop);
    setBtnEnable(false);  /* 设置按钮不可点击 */
}

FormStatus::~FormStatus()
{
    delete ui;
}

void FormStatus::on_btn_stop_clicked()
{
    emit playerStop();
    setBtnStatus(false);
    setBtnEnable(false);  /* 失能两个按钮 */
}

void FormStatus::on_btn_pause_clicked()
{
    if(isPlaying){
        ui->btn_pause->setIcon(QIcon(":/icos/play.ico"));
        isPlaying = false;
    }else{
        ui->btn_pause->setIcon(QIcon(":/icos/pause.ico"));
        isPlaying = true;
    }
    qDebug()<<"播放视频状态"<<isPlaying;
}

void FormStatus::setBtnStatus(bool status)
{
    isPlaying = status;
    qDebug()<<"播放视频状态"<<isPlaying;
    if(status){
        ui->btn_pause->setIcon(QIcon(":/icos/pause.ico"));
    }else{
        ui->btn_pause->setIcon(QIcon(":/icos/play.ico"));
    }
}
void FormStatus::stopPlay()
{
    ui->btn_stop->click();  /* 关闭视频播放 */
    ui->btn_pause->click(); /* 改变暂停的错误 */
    setBtnEnable(false);  /* 设置按钮不可点击 */
}
void FormStatus::setBtnEnable(bool enable)
{
    ui->btn_pause->setEnabled(enable);
    ui->btn_stop->setEnabled(enable);
}
