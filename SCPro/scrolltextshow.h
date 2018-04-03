#ifndef SCROLLTEXTSHOW_H
#define SCROLLTEXTSHOW_H

#include <QWidget>
#include <QPainter>
#include <QFontMetrics>
#include "define.h"

class ScrollTextShow : public QWidget
{
    Q_OBJECT
public:
    explicit ScrollTextShow(QWidget *parent);
    void setTextFont(const QFont &);
    void addText();
    void addNewText(errorInfo info); // 添加错误信息到Label列表中
    bool setErrorInfoStatus(int id,bool isHandled);
    void condenseShowList();
signals:

public slots:
    void onTimerOut();
private:
    QColor m_textColor;
    QFont m_font;
    QStringList m_showStr;
    QString m_normalStr;
    QTimer *m_timer;

    int offset;
    int currentIndex; // 当前证正在显示的字符串序列
    int m_fontHeight;
    int m_yPos;
    QList<QLabel*> m_showTextList;
    QLabel *m_normalText1;
    QLabel *m_normalText2;
    QLabel *m_showText1;
    QLabel *m_showText2;
};

#endif // SCROLLTEXTSHOW_H
