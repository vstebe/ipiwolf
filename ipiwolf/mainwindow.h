#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "datafile.h"

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
    void slotProcessResampling();
    void slotProcessFiltering();
    void slotUpdateGraphAxes();

private:
    Ui::MainWindow *ui;
    DataFilePtr _currentDataFile;
};

#endif // MAINWINDOW_H
