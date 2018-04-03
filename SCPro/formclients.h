#ifndef FORMCLIENTS_H
#define FORMCLIENTS_H

#include <QWidget>

namespace Ui {
class FormClients;
}

class FormClients : public QWidget
{
    Q_OBJECT

public:
    explicit FormClients(QWidget *parent = 0);
    ~FormClients();

private:
    Ui::FormClients *ui;
};

#endif // FORMCLIENTS_H
