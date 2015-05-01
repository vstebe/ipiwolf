#include "samplingasker.h"
#include "ui_samplingasker.h"

SamplingAsker::SamplingAsker(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SamplingAsker)
{
    ui->setupUi(this);
}

SamplingAsker::~SamplingAsker()
{
    delete ui;
}

int SamplingAsker::getSamplingRate() {
    return ui->spinSamplingRate->value();
}
