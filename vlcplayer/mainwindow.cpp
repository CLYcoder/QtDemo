#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QInputDialog>
#include <QIcon>
#include <QMessageBox>
#include <QSettings>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle(appName);
    this->setWindowIcon(QIcon(":/icos/mediaplayer.ico"));
    ui->mainToolBar->hide();
    m_pMedia = NULL;
    m_curType = NoMedia;
    m_isFillScreen = false;
    m_pInstance = new VlcInstance(VlcCommon::args(),this);
    m_pPlayer = new VlcMediaPlayer(m_pInstance);

    m_pPlayer->setVideoWidget(ui->video);  /* 界面控件播放器控件指定显示位置 */
    ui->video->setMediaPlayer(m_pPlayer);

    m_statusCtrl = new FormStatus(m_pPlayer,this);

    QMenu *menu = new QMenu("Media",this);
    menu->addAction(ui->action_openlocal);
    menu->addAction(ui->action_openUrl);
    menu->addAction(ui->action_quit);
    ui->menuBar->addMenu(menu);

    ui->statusBar->addWidget(m_statusCtrl,1);  /* 添加填充 */

    connect(ui->action_openlocal,&QAction::triggered,this,&MainWindow::openLocalMediaFile);
    connect(ui->action_openUrl,&QAction::triggered,this,&MainWindow::openUrl);
    connect(ui->action_quit,&QAction::triggered,this,&MainWindow::close);
    connect(m_pPlayer,&VlcMediaPlayer::end,this,&MainWindow::playEnd);
    connect(m_pPlayer,&VlcMediaPlayer::error,this,&MainWindow::occurError);
    connect(m_statusCtrl,&FormStatus::playerStop,this,&MainWindow::stop);
}

MainWindow::~MainWindow()
{
    writeUrlToConfig(m_strURL);

    delete m_pPlayer;
    delete m_pMedia;
    delete m_pInstance;
    delete ui;
}

void MainWindow::openLocalMediaFile()
{
    m_strLoalFile = QFileDialog::getOpenFileName(this, tr("Open file"),
                                         QDir::homePath(),
                                         tr("Multimedia files(*)"));

    if (m_strLoalFile.isEmpty())
        return;

    m_pMedia = new VlcMedia(m_strLoalFile, true, m_pInstance);

    m_pPlayer->open(m_pMedia); /* 开始播放视频 */
    m_statusCtrl->setBtnStatus(true);
    this->setWindowTitle(m_strLoalFile);
    m_curType = LOCAL;
    m_statusCtrl->setBtnEnable(true);  /* 设置按钮可点击 */
}

void MainWindow::openUrl()
{
    //const QString str = ;
    QString str = readUrlFromConfig();
    //qDebug()<<"server="<<str;
    m_strURL = QInputDialog::getText(this, tr("Open Url"), tr("Enter the URL you want to play"),QLineEdit::Normal,str);
    //qDebug()<<m_strURL;

    if (m_strURL.isEmpty()){

        QMessageBox::warning(this,"input url wrong!","the url is empty !\r\n you should input url just like :rtsp://192.168.1.168/0!",QMessageBox::Ok);
        return;
    }else if(m_strURL != str){
        writeUrlToConfig(m_strURL); /* 地址发生改变时更新到配置文件中 */
    }

    m_pMedia = new VlcMedia(m_strURL, m_pInstance);
    m_pPlayer->open(m_pMedia);

    m_statusCtrl->setBtnStatus(true);
    this->setWindowTitle(m_strURL);
    m_curType = NET;
    m_statusCtrl->setBtnEnable(true);  /* 设置按钮可点击 */
}
void MainWindow::pause()
{

}
/**
 * @brief 接收停止信号，将窗口标题清除
 */
void MainWindow::stop()
{
    this->setWindowTitle(appName);
}

void MainWindow::occurError()
{
     qDebug()<<"play media error!";
     QString str;
     if(m_curType == LOCAL){
        str = "can't open "+m_strLoalFile;
     }else if(m_curType == NET){
        str = "failed to connect "+m_strURL;
     }
     QMessageBox msgBox;
     msgBox.resize(300,200);
     msgBox.setText(str);               /* 设置主要提示信息 */
     msgBox.setWindowTitle("play media failed");        /* 设置消息框的窗口显示信息 */
     msgBox.setWindowIcon(QIcon(":/icos/error.ico"));         /* 设置消息框的窗口图标 */
     //msgBox.setInformativeText(str);            /* 设置具体显示信息，对提示信息的解释 */
     msgBox.setIcon(QMessageBox::NoIcon);  /* 设置消息框的图标 */
     msgBox.setStandardButtons(QMessageBox::Ok|QMessageBox::Cancel);  /* 设置显示按钮 */
     msgBox.setDefaultButton(QMessageBox::Ok);
     msgBox.exec();

     m_statusCtrl->stopPlay();
}

bool MainWindow::eventFilter(QObject *watched, QEvent *event)
{
    return QMainWindow::eventFilter(watched,event);
}

void MainWindow::mouseDoubleClickEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    qDebug()<<"mouse double clicked !!";
    if(!m_isFillScreen){
        this->showFullScreen();
        this->menuBar()->hide();
        this->statusBar()->hide();
        m_isFillScreen = true;
    }else{
        m_isFillScreen = false;
        this->showNormal();
        this->menuBar()->show();
        this->statusBar()->show();
    }

}

QString MainWindow::readUrlFromConfig()
{
    QSettings *config = new QSettings("rtspServer.ini",QSettings::IniFormat);

    /* 设置默认rtsp服务器地址为  rtsp://192.168.1.168/0 */
    return config->value("server","rtsp://192.168.1.168/0").toString();
}

void MainWindow::writeUrlToConfig(QString url)
{
    QSettings *config = new QSettings("rtspServer.ini",QSettings::IniFormat);

    config->setValue("server",url);

    config->sync();
}
