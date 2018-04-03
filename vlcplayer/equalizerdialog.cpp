#include "equalizerdialog.h"
#include "ui_equalizerdialog.h"

EqualizerDialog::EqualizerDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EqualizerDialog)
{
    ui->setupUi(this);
}

EqualizerDialog::~EqualizerDialog()
{
    delete ui;
}
