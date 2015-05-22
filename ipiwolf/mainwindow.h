#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "datafile.h"
#include "spectrum.h"

namespace Ui {
class MainWindow;
}

enum FileType {RAW, RESAMPLED};

/**
 * @brief Main Window of the application, containing all elements of the page.
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief Constructs the window
     * @param parent
     */
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    /**
     * @brief Opens a raw file. Should be triggered when the users clicks on the "open raw" button
     */
    void slotOpenRaw();

    /**
     * @brief Opens a resampled file.
     * Should be triggered when the users clicks on the "open raw" button.
     * The sampling rate should be found in the name of the file, otherwise the user will be asked
     */
    void slotOpenResampled();

    /**
     * @brief Starts the resampling of a raw file with the parameters given by the user.
     */
    void slotProcessResampling();
    /**
     * @brief Starts the resampling of a raw file with the parameters given by the user.
     */
    void slotProcessFiltering();
    /**
     * @brief Updates the graph (triggered when the user clicks on a checkbox)
     */
    void slotUpdateGraphAxes();
    /**
     * @brief Save the current file, and asks the user for the location.
     */
    void slotSaveResampledFile();
    /**
     * @brief Computes the spectrum of the current file, and updates the graph
     */
    void slotProcessSpectrum();

protected:
    void updateFileInfo();
    void setMainFormEnabled(bool enabled);

private:
    Ui::MainWindow *ui;
    DataFilePtr _currentDataFile;
    SpectrumPtr _currentSpectrum;
    QString _currentFileName;
    FileType _currentFileType;
};

#endif // MAINWINDOW_H
