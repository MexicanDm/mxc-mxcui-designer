#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>
#include <QButtonGroup>
#include <QTimer>
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

    QList<int> cBtnSta;

signals:
    void sigDisplayJsonProperty();
    void sigLayerSta(QList<int> layerSta);
public slots:
    void slotOpenFile();
    void slotSaveFile();
    void slotcBtnSta();
    void slotReadBtnSta();
    void slotClear();
};

#endif // MAINWINDOW_H
