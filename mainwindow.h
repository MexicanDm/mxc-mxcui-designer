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
    bool bHV;

signals:
    void sigDisplayJsonProperty();
    void sigLayerSta(QList<int> layerSta);
    void sigPaintWidgetRect(int w,int h);
public slots:
    void slotOpenFile();
    void slotSaveFile();
    void slotcBtnSta();
    void slotReadBtnSta();
    void slotClear();
    void slotBtnHV();
};

#endif // MAINWINDOW_H
