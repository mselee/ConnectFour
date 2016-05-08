#ifndef LOADDIALOG_H
#define LOADDIALOG_H

#include <QDialog>
#include <QDir>

namespace Ui {
class LoadDialog;
}

class LoadDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoadDialog(QWidget *parent = 0);
    QString filename;
    ~LoadDialog();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::LoadDialog *ui;
};

#endif // LOADDIALOG_H
