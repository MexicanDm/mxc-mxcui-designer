#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QObject::connect(ui->pBtnOpenFile,SIGNAL(clicked(bool)),this,SLOT(slotOpenFile()));
    QObject::connect(ui->pBtnSaveFile,SIGNAL(clicked(bool)),this,SLOT(slotSaveFile()));
    QObject::connect(this,SIGNAL(sigDisplayJsonProperty()),ui->treeWidget,SLOT(slotDisplayJsonFile()));
    QObject::connect(ui->treeWidget,SIGNAL(sigDisplayJsonProperty()),ui->disWidget,SLOT(slotGetComProperty()));
    QObject::connect(ui->treeWidget,SIGNAL(sigUpdateSta(SearchType)),ui->disWidget,SLOT(slotUpdateSta(SearchType)));
}

void MainWindow::slotOpenFile()
{
    QStringList files = QFileDialog::getOpenFileNames(this,"Select one or more files to open","/home/raise3d","Json (*.json *.mxcui)");
    if(files.isEmpty())return;
    bool bReadFile = false;
    QVector<JsonProperty> &vMainJsonPro = PublicFunc::vPublicJsonPro;
    //vMainJsonPro.clear();
    for(int i = 0;i < files.count();i++)
    {
        JsonProperty tempvJsonPro;
        bReadFile = PublicFunc::readUIFile(files[i],tempvJsonPro);
        vMainJsonPro.append(tempvJsonPro);
    }

    if(bReadFile)
    {
        emit sigDisplayJsonProperty();
    }
}


void MainWindow::slotSaveFile()
{
    QVector<JsonProperty> &jsonPro = PublicFunc::vPublicJsonPro;
    bool writeB = false;
    for(int i = 0;i < jsonPro.count();i++)
    {
        writeB = PublicFunc::writeUIFile(jsonPro[i]);
    }
    if(writeB)
    {
        QMessageBox::about(NULL, "Prompt", "Json Files Save OK!");
    }
    else
    {
        QMessageBox::about(NULL, "Prompt", "Json Files Save ERROR!");
    }

}

MainWindow::~MainWindow()
{
    delete ui;
}
