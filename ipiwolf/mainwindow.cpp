#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>

#include "resampler.h"
#include "frequencyfilter.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->btnOpen, &QPushButton::clicked, this, &MainWindow::slotSelectFile);
    connect(ui->btnProcess, &QPushButton::clicked, this, &MainWindow::slotProcessResampling);
    connect(ui->btnFilter, &QPushButton::clicked, this, &MainWindow::slotProcessFiltering);
    connect(ui->radioGraphX, &QRadioButton::clicked, this, &MainWindow::slotUpdateGraphAxes);
    connect(ui->radioGraphY, &QRadioButton::clicked, this, &MainWindow::slotUpdateGraphAxes);
    connect(ui->radioGraphZ, &QRadioButton::clicked, this, &MainWindow::slotUpdateGraphAxes);
    connect(ui->btnSaveResampled, &QPushButton::clicked, this, &MainWindow::slotSaveResampledFile);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::slotSelectFile()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Open File",
                                                    "",
                                                    tr("Fichiers textes (*.txt);;Tous les fichiers (*)"));

    ui->txtFile->setEditText(fileName);
}

void MainWindow::slotProcessResampling() {
    Resampler r;
    r.setFile(ui->txtFile->currentText());
    r.setEndDate(ui->txtDateEnd->date());
    r.setStartDate(ui->txtDateStart->date());
    r.setFrequency(ui->txtFreq->value());

    _currentDataFile = r.resample();


    ui->_graph->setDataFile(_currentDataFile);

    _currentDataFile->saveInFile(ui->txtFile->currentText() + ".resampled.txt");
}

void MainWindow::slotUpdateGraphAxes() {
    ui->_graph->setAxes(ui->radioGraphX->isChecked(), ui->radioGraphY->isChecked(), ui->radioGraphZ->isChecked());
    ui->_graph->update();
}

void MainWindow::slotSaveResampledFile() {
    if(_currentDataFile.isNull()) return;

    QString filename = QFileDialog::getSaveFileName(this, tr("Save File"),
                               tr("Text (*.txt)"));
    _currentDataFile->saveInFile(filename);

}

void MainWindow::slotProcessFiltering() {
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

    DataFilePtr df = filter.process();

    ui->_graph->setDataFile(df);
    df->saveInFile(ui->txtFile->currentText() + ".filtered.txt");
}
