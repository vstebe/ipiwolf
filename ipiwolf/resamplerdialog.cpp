#include "resamplerdialog.h"
#include "ui_resamplerdialog.h"

ResamplerDialog::ResamplerDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ResamplerDialog)
{
    ui->setupUi(this);
    _rs = new Resampler();
    _rs->moveToThread(&_dateThread);
    connect(_rs, &Resampler::dateChanged, this, &ResamplerDialog::changeDate);
    connect(_rs, &Resampler::finished, this, &ResamplerDialog::finished);
    connect(&_dateThread, &QThread::started, _rs, &Resampler::resample);

}

ResamplerDialog::~ResamplerDialog()
{
    delete ui;
}

void ResamplerDialog::changeDate(QDateTime date)
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
    exec();
}


void ResamplerDialog::finished() {
    _dateThread.quit();
    _dateThread.wait();
    accept();
}
