#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "calchash.h"
#include "keybox.h"
#include "calcproc.h"
#include "common.h"

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
    void slotAppend(QString);

private slots:
    void on_btnOpenCap_clicked();


private:
    Ui::MainWindow *ui;
    hccap_t hccap;
    CalcHash* calcHash;
    KeyBox* keyBox;
    CalcProc* calcProc;
};

#endif // MAINWINDOW_H
