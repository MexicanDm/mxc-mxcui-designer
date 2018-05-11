#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
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


signals:
    void sigDisplayJsonProperty();
public slots:
    void slotOpenFile();
    void slotSaveFile();
};

#endif // MAINWINDOW_H
