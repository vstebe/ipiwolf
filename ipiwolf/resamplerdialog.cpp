#include "resamplerdialog.h"
#include "ui_resamplerdialog.h"

ResamplerDialog::ResamplerDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ResamplerDialog)
{
    ui->setupUi(this);
    _rs = new Resampler();
    _rs->moveToThread(&_dateThread);
    this->connect(_rs, &Resampler::dateChanged, this, &ResamplerDialog::changeDate);
    this->connect(&_dateThread, &QThread::finished, this, &ResamplerDialog::accepted);
}

ResamplerDialog::~ResamplerDialog()
{
    delete ui;
}

void ResamplerDialog::changeDate(QDate date)
{
    ui->lblDate->setText(date.toString());
}

Resampler * ResamplerDialog::getResampler()
{
    return _rs;
}

void ResamplerDialog::startResampling()
{
        _dateThread.start();
}
