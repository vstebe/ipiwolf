#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>

#include "resamplerdialog.h"
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

        QRegExp exp(".+([0-9]+)Hz.+");
        if(exp.indexIn(_currentFileName) >= 0) {
            _currentDataFile->setSamplingRate(exp.cap(1).toInt());
            qDebug() << _currentDataFile->getSamplingRate() << "  " << exp.cap(0);
        } else {
            SamplingAsker asker(this);
            if(asker.exec() == QDialog::Accepted)
                _currentDataFile->setSamplingRate(asker.getSamplingRate());
            else
                return;
        }

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
    ResamplerDialog rd;
    rd.getResampler()->setFile(_currentFileName);
    rd.getResampler()->setEndDate(ui->txtDateEnd->dateTime());
    rd.getResampler()->setStartDate(ui->txtDateStart->dateTime());
    rd.getResampler()->setFrequency(ui->txtFreq->value());

    rd.startResampling();

    DataFilePtr result = rd.getResampler()->getResult();

    if(!result.isNull()) {
        _currentDataFile = result;
        ui->_graph->setDataFile(_currentDataFile);

        _currentFileType = RESAMPLED;
        updateFileInfo();
    }


}

void MainWindow::slotUpdateGraphAxes() {
    ui->_graph->setAxes(ui->radioGraphX->isChecked(), ui->radioGraphY->isChecked(), ui->radioGraphZ->isChecked(), ui->radioGraphXYZ->isChecked());
    ui->_graph->replot();
}

void MainWindow::slotSaveResampledFile() {
    if(_currentDataFile.isNull()) return;

    QFileInfo fi(_currentFileName);

    QString filename = QFileDialog::getSaveFileName(this, tr("Save File"),fi.absolutePath() + fi.completeBaseName() + "." + QString::number(_currentDataFile->getSamplingRate()) + "Hz.txt",
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

    ui->_spectrumGraph->setSpectrum(histo);
    ui->_spectrumGraph->replot();
}
