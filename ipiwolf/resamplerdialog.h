#ifndef RESAMPLERDIALOG_H
#define RESAMPLERDIALOG_H

#include <QDialog>
#include <QThread>
#include <QDate>
#include <resampler.h>

namespace Ui {
class ResamplerDialog;
}

class ResamplerDialog : public QDialog
{
    Q_OBJECT
    QThread _dateThread;

public:
    explicit ResamplerDialog(QWidget *parent = 0);
    ~ResamplerDialog();
    Resampler* getResampler();
    void startResampling();


private:
    Ui::ResamplerDialog *ui;
    QThread _thread;
    Resampler *_rs;

public slots:
    void changeDate(QDate date);
    void finished();
};

#endif // RESAMPLERDIALOG_H
