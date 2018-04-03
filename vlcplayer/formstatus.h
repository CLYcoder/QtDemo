#ifndef FORMSTATUS_H
#define FORMSTATUS_H

#include <QWidget>
#include <QDebug>
#include <VLCQtWidgets/WidgetSeek.h>
#include <VLCQtCore/MediaPlayer.h>
namespace Ui {
class FormStatus;
}

class FormStatus : public QWidget
{
    Q_OBJECT

public:
    explicit FormStatus(VlcMediaPlayer* player,QWidget *parent = 0);
    ~FormStatus();
    bool isPlaying;
    void setBtnStatus(bool);
    void stopPlay();
    void setBtnEnable(bool);
private slots:
    void on_btn_stop_clicked();

    void on_btn_pause_clicked();

private:
    Ui::FormStatus *ui;
    VlcMediaPlayer* m_pPlayer ;
signals:
    void playerStop();
    void playerPaused();
};

#endif // FORMSTATUS_H
