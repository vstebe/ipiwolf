#ifndef RESAMPLERDIALOG_H
#define RESAMPLERDIALOG_H

#include <QDialog>
#include <QThread>
#include <QDate>

namespace Ui {
class ResamplerDialog;
}

class ResamplerDialog : public QDialog
{
    Q_OBJECT
    QThread dateThread;

public:
    explicit ResamplerDialog(QWidget *parent = 0);
    ~ResamplerDialog();


private:
    Ui::ResamplerDialog *ui;
    QThread thread;

public slots:
    void changeDate(QDate date);
};

#endif // RESAMPLERDIALOG_H
