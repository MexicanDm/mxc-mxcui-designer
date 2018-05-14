#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>
#include "publicfunc.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    bool layerSta0;
    bool layerSta1;
    bool layerSta2;

signals:
    void sigDisplayJsonProperty();
    void sigLayerSta(bool s0,bool s1,bool s2);
public slots:
    void slotOpenFile();
    void slotSaveFile();
};

#endif // MAINWINDOW_H
