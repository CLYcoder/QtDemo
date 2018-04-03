#ifndef EQUALIZERDIALOG_H
#define EQUALIZERDIALOG_H

#include <QDialog>

namespace Ui {
class EqualizerDialog;
}

class EqualizerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EqualizerDialog(QWidget *parent = 0);
    ~EqualizerDialog();

private:
    Ui::EqualizerDialog *ui;
};

#endif // EQUALIZERDIALOG_H
