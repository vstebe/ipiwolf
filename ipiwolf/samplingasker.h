#ifndef SAMPLINGASKER_H
#define SAMPLINGASKER_H

#include <QDialog>

namespace Ui {
class SamplingAsker;
}

class SamplingAsker : public QDialog
{
    Q_OBJECT

public:
    explicit SamplingAsker(QWidget *parent = 0);
    int getSamplingRate();
    ~SamplingAsker();

private:
    Ui::SamplingAsker *ui;
};

#endif // SAMPLINGASKER_H
