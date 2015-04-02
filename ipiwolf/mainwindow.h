#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "resampler.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void slotSelectFile();
    void slotProcess();

private:
    Ui::MainWindow *ui;
    resampler _resampler;
};

#endif // MAINWINDOW_H
