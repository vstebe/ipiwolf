#ifndef RESAMPLERDIALOG_H
#define RESAMPLERDIALOG_H

#include <QDialog>
#include <QThread>
#include <QDateTime>
#include <resampler.h>

namespace Ui {
class ResamplerDialog;
}

/**
 * @brief Class used to display the progress of the resampling.
 */
class ResamplerDialog : public QDialog
{
    Q_OBJECT
    QThread _dateThread;

public:
    /**
     * @brief The constructor of the ResamplerDialog
     * @param parent Qwidget parent
     */
    explicit ResamplerDialog(QWidget *parent = 0);
    ~ResamplerDialog();

    /**
     * @brief Returns a pointer on the resampler
     * @return a pointer on the resampler
     */
    Resampler* getResampler();

    /**
     * @brief Begins the thread of the resampling.
     */
    void startResampling();


private:
    Ui::ResamplerDialog *ui;
    QThread _thread;
    Resampler *_rs;

public slots:
    /**
     * @brief Changes the displayed date.
     * Is called when the date changes.
     * @param date the new date
     */
    void changeDate(QDateTime date);

    /**
     * @brief Cancel the thread during the process.
     */
    void cancel();

    /**
     * @brief Is called at the end of the process.
     */
    void finished();
};

#endif // RESAMPLERDIALOG_H
