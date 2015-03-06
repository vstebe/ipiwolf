#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->btnOpen, &QPushButton::clicked, this, &MainWindow::slotSelectFile);
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

    ui->txtFile->setText(fileName);
}
