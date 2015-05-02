#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "datafile.h"
#include "histogram.h"

namespace Ui {
class MainWindow;
}

enum FileType {RAW, RESAMPLED};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void slotOpenRaw();
    void slotOpenResampled();
    void slotProcessResampling();
    void slotProcessFiltering();
    void slotUpdateGraphAxes();
    void slotSaveResampledFile();
    void slotProcessHistogram();

protected:
    void updateFileInfo();

private:
    Ui::MainWindow *ui;
    DataFilePtr _currentDataFile;
    HistogramPtr _currentHistogram;
    QString _currentFileName;
    FileType _currentFileType;
};

#endif // MAINWINDOW_H
