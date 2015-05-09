#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>

#include "resampler.h"
#include "frequencyfilter.h"
#include "samplingasker.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->btnOpenRaw, &QPushButton::clicked, this, &MainWindow::slotOpenRaw);
    connect(ui->btnOpenResampled, &QPushButton::clicked, this, &MainWindow::slotOpenResampled);
    connect(ui->btnProcess, &QPushButton::clicked, this, &MainWindow::slotProcessResampling);
    connect(ui->btnFilter, &QPushButton::clicked, this, &MainWindow::slotProcessFiltering);
    connect(ui->radioGraphX, &QRadioButton::clicked, this, &MainWindow::slotUpdateGraphAxes);
    connect(ui->radioGraphY, &QRadioButton::clicked, this, &MainWindow::slotUpdateGraphAxes);
    connect(ui->radioGraphZ, &QRadioButton::clicked, this, &MainWindow::slotUpdateGraphAxes);
    connect(ui->radioGraphXYZ, &QRadioButton::clicked, this, &MainWindow::slotUpdateGraphAxes);
    connect(ui->btnSaveResampled, &QPushButton::clicked, this, &MainWindow::slotSaveResampledFile);
    connect(ui->btnProcessSpectrum, &QPushButton::clicked, this, &MainWindow::slotProcessSpectrum);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::slotOpenRaw()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Open File",
                                                    "",
                                                    tr("Fichiers textes (*.txt);;Tous les fichiers (*)"));
    if(!fileName.isEmpty()) {
        _currentFileName = fileName;
        _currentFileType = RAW;
        updateFileInfo();
        ui->mainForm->setEnabled(true);
        _currentDataFile = DataFilePtr();
        _currentSpectrum = SpectrumPtr();
    }
}

void MainWindow::slotOpenResampled()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Open File",
                                                    "",
                                                    tr("Fichiers textes (*.txt);;Tous les fichiers (*)"));
    if(!fileName.isEmpty()) {
        _currentFileName = fileName;
        _currentFileType = RESAMPLED;
        updateFileInfo();
        ui->mainForm->setEnabled(true);
        _currentSpectrum = SpectrumPtr();

        _currentDataFile = DataFile::openFile(_currentFileName);

        if(_currentDataFile.isNull()) {
            QMessageBox::critical(this, "Error", "An error occured while opening the file");
            return;
        }
        SamplingAsker asker(this);
        if(asker.exec() == QDialog::Accepted)
            _currentDataFile->setSamplingRate(asker.getSamplingRate());
        else
            return;


        ui->_graph->setDataFile(_currentDataFile);
    }
}

void MainWindow::updateFileInfo() {
    QString info = "Fichier ouvert : \"" + _currentFileName + "\"";

    if(_currentFileType == RAW)
        info += " (not resampled)";
    else
        info += " (resampled)";

    ui->lblFileInfo->setText(info);
}

void MainWindow::slotProcessResampling() {
    Resampler r;
    r.setFile(_currentFileName);
    r.setEndDate(ui->txtDateEnd->date());
    r.setStartDate(ui->txtDateStart->date());
    r.setFrequency(ui->txtFreq->value());

    _currentDataFile = r.resample();


    ui->_graph->setDataFile(_currentDataFile);

    _currentFileType = RESAMPLED;
    updateFileInfo();
}

void MainWindow::slotUpdateGraphAxes() {
    ui->_graph->setAxes(ui->radioGraphX->isChecked(), ui->radioGraphY->isChecked(), ui->radioGraphZ->isChecked(), ui->radioGraphXYZ);
    ui->_graph->update();
}

void MainWindow::slotSaveResampledFile() {
    if(_currentDataFile.isNull()) return;

    QString filename = QFileDialog::getSaveFileName(this, tr("Save File"),
                               tr("Text (*.txt)"));
    _currentDataFile->saveInFile(filename);


}

void MainWindow::slotProcessFiltering() {
    if(_currentFileType == RAW) {
        QMessageBox::critical(this, "Error", "You must first resample the file");
        return;
    }

    FrequencyFilter filter;
    if(ui->radioX->isChecked())
        filter.setAxes(FrequencyFilter::X);
    else if(ui->radioY->isChecked())
        filter.setAxes(FrequencyFilter::Y);
    else if(ui->radioZ->isChecked())
        filter.setAxes(FrequencyFilter::Z);
    else
        filter.setAxes(FrequencyFilter::XYZ);

    filter.setDatafile(_currentDataFile);

    filter.setThreshold(ui->txtThreshold->value());
    filter.setDirection(ui->radioLow->isChecked() ? FrequencyFilter::LOW : FrequencyFilter::HIGH);

    filter.process();

    ui->_graph->setDataFile(_currentDataFile);
    _currentDataFile->saveInFile(_currentFileName + ".filtered.txt");
}


void MainWindow::slotProcessSpectrum() {
    if(_currentFileType == RAW) {
        QMessageBox::critical(this, "Error", "You must first resample the file");
        return;
    }
    FrequencyFilter filter;
    filter.setDatafile(_currentDataFile);

    MultiSpectrum histo = filter.getSpectrum(ui->radioSpectrumGraphX->isChecked(), ui->radioSpectrumGraphY->isChecked(), ui->radioSpectrumGraphZ->isChecked(), ui->radioSpectrumGraphXYZ->isChecked());

    std::cout << (*(histo.y)) << std::endl;

    ui->_spectrumGraph->setSpectrum(histo);
}
