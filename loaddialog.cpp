#include "loaddialog.h"
#include "ui_loaddialog.h"

LoadDialog::LoadDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoadDialog)
{
    ui->setupUi(this);
    connect(this, SIGNAL(accepted()), this, SLOT(on_buttonBox_accepted()));
    QStringList files = QDir("games").entryList(QStringList() << "*.txt", QDir::Files | QDir::NoDotAndDotDot | QDir::NoSymLinks);
    ui->listFiles->addItems(files);

}

LoadDialog::~LoadDialog()
{
    delete ui;
}

void LoadDialog::on_buttonBox_accepted()
{
    if (ui->listFiles->selectedItems().count() > 0)
        filename = ui->listFiles->selectedItems()[0]->text();
}
