#ifndef FORMTIMESOURCE_H
#define FORMTIMESOURCE_H

#include <QWidget>
#include "define.h"

namespace Ui {
class FormTimeSource;
}

class FormTimeSource : public QWidget
{
    Q_OBJECT

public:
    explicit FormTimeSource(QWidget *parent = 0,QString belongWidget="");
    ~FormTimeSource();

    enum Status{
        invalid = 0,unknown,valid
    };

    void setItemText(QString);
    QString ItemText();
    void setItemStatus(Status);
    Status ItemStatus();
    void setItemUsed(bool);
    bool isItemUsed();
signals:
    void updateStytleSheet();
private:
    Ui::FormTimeSource *ui;
};

#endif // FORMTIMESOURCE_H
