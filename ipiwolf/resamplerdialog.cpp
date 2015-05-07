#include "resamplerdialog.h"
#include "ui_resamplerdialog.h"

ResamplerDialog::ResamplerDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ResamplerDialog)
{
    ui->setupUi(this);
    //movetoThread
    //connect(&dateThread, SIGNAL(finished() )

    //dateThread.start();
}

ResamplerDialog::~ResamplerDialog()
{
    delete ui;
}

void ResamplerDialog::changeDate(QDate date)
{
    ui->lblDate->setText(date.toString());
}
