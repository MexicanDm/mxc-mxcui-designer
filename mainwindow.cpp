#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QObject::connect(ui->pBtnOpenFile,SIGNAL(clicked(bool)),this,SLOT(slotOpenFile()));
    QObject::connect(ui->pBtnSaveFile,SIGNAL(clicked(bool)),this,SLOT(slotSaveFile()));
    QObject::connect(this,SIGNAL(sigDisplayJsonProperty(QVector<JsonProperty>)),ui->treeWidget,SLOT(slotDisplayJsonFile(QVector<JsonProperty>)));
    QObject::connect(this,SIGNAL(sigDisplayJsonProperty(QVector<JsonProperty>)),ui->disWidget,SLOT(slotGetComProperty(QVector<JsonProperty>)));
}

void MainWindow::slotOpenFile()
{
    QStringList files = QFileDialog::getOpenFileNames(this,"Select one or more files to open","/home/raise3d","Json (*.json *.mxcui)");
    if(files.isEmpty())return;
    bool bReadFile = false;
    vJsonPro.clear();
    for(int i = 0;i < files.count();i++)
    {
        JsonProperty tempvJsonPro;
        bReadFile = PublicFunc::readUIFile(files[i],tempvJsonPro);
        vJsonPro.append(tempvJsonPro);
    }
    if(bReadFile)
    {
        emit sigDisplayJsonProperty(vJsonPro);
    }
}


void MainWindow::slotSaveFile()
{

}

MainWindow::~MainWindow()
{
    delete ui;
}
