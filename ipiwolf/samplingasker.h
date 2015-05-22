#ifndef SAMPLINGASKER_H
#define SAMPLINGASKER_H

#include <QDialog>

namespace Ui {
class SamplingAsker;
}

/**
 * @brief Simple dialog asking the user for the sampling rate of the signal if it's unknown
 */
class SamplingAsker : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief Constructs the dialog
     * @param parent QWidget parent
     */
    explicit SamplingAsker(QWidget *parent = 0);

    /**
     * @brief Returns the sampling rate given by the user
     * @return the sampling rate
     */
    int getSamplingRate();
    ~SamplingAsker();

private:
    Ui::SamplingAsker *ui;
};

#endif // SAMPLINGASKER_H
