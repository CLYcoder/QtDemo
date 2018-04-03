#include "formcard.h"
#include "ui_formcard.h"

FormCard::FormCard(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormCard)
{
    ui->setupUi(this);
}

FormCard::~FormCard()
{
    delete ui;
}

void FormCard::setCardName(QString name)
{
    ui->label_cardName->setText(name);
}
QString FormCard::getCardName()
{
    return ui->label_cardName->text();
}
void FormCard::setCardStatus(QString str)
{
    Q_UNUSED(str);
}
QString FormCard::getCardStatus()
{
    QString ret;
    return ret;
}
void FormCard::setCardTempValue(float temp)
{
    ui->label_Temp->setText(QString("%1").arg(temp));
}
float FormCard::getCardTemp()
{
    return ui->label_Temp->text().toFloat();
}
