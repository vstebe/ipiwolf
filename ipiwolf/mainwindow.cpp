#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->btnOpen, &QPushButton::clicked, this, &MainWindow::slotSelectFile);
    connect(ui->btnProcess, &QPushButton::clicked, this, &MainWindow::slotProcess);
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

void MainWindow::slotProcess() {
    resampler r;
    r.setFile(ui->txtFile->currentText());
    r.setEndDate(ui->txtDateEnd->date());
    r.setStartDate(ui->txtDateStart->date());
    r.setFrequency(ui->txtFreq->value());

    DataFile *df = r.resample();

    std::cout << "size : " << df->size()  << std::endl;

    ui->_graph->setDataFile(df);
}
