#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QTextStream>
#include <QTime>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete calcHash;
}

void MainWindow::on_btnOpenCap_clicked()
{
    QTime time;
    QString str_file = QFileDialog::getOpenFileName(0, "Open Dialog", "", "");
    QString str;
    QFile file;

    calcHash = new CalcHash();
    keyBox = new KeyBox();

    file.setFileName(str_file);
    file.open(QIODevice::ReadOnly);
    file.read((char*)&hccap, sizeof(hccap));
    ui->teMain->append(hccap.essid);
    ui->teMain->append("BSSID: ");
    for(unsigned int i = 0; i < sizeof(hccap.bssid); i++)
    {
        str.sprintf("%02X ", hccap.bssid[i]);
        ui->teMain->insertPlainText(str);
    }
    ui->teMain->append("STMAC: ");
    for(unsigned int i = 0; i < sizeof(hccap.stmac); i++)
    {
        str.sprintf("%02X ", hccap.stmac[i]);
        ui->teMain->insertPlainText(str);
    }

    calcProc = new CalcProc(keyBox, &hccap, calcHash);
    connect(calcProc, SIGNAL(resultReady()), this, SLOT(slotAppend()), Qt::AutoConnection);
    calcProc->start();
   // char *key = "9653652827";
    ui->teMain->append("111");
}

void MainWindow::slotAppend()
{
    ui->teMain->append("XXX");
}

