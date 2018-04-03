#include "formclients.h"
#include "ui_formclients.h"

FormClients::FormClients(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormClients)
{
    ui->setupUi(this);
}

FormClients::~FormClients()
{
    delete ui;
}
