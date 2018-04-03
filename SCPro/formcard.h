#ifndef FORMCARD_H
#define FORMCARD_H

#include <QWidget>

namespace Ui {
class FormCard;
}

class FormCard : public QWidget
{
    Q_OBJECT

public:
    explicit FormCard(QWidget *parent = 0);
    ~FormCard();
    void setCardName(QString);
    QString getCardName();
    QString getCardStatus();
    void setCardStatus(QString);
    void setCardTempValue(float);
    float getCardTemp();
private:
    Ui::FormCard *ui;
};

#endif // FORMCARD_H
