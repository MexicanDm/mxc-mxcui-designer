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
    QObject::connect(ui->treeWidget,SIGNAL(sigDisplayJsonProperty()),ui->disWidget,SLOT(update()));
    QObject::connect(ui->treeWidget,SIGNAL(sigUpdateSta(SearchType)),ui->disWidget,SLOT(slotUpdateSta(SearchType)));
    QObject::connect(ui->cBox0,SIGNAL(clicked(bool)),ui->disWidget,SLOT(slotSetLayerSta(bool,bool,bool)));
}

void MainWindow::slotOpenFile()
{
    QStringList files = QFileDialog::getOpenFileNames(this,"Select one or more files to open","/home/raise3d","Json (*.json *.mxcui)");
    if(files.isEmpty())return;
    bool bReadFile = false;
    QList<JsonProperty> &vMainJsonPro = PublicFunc::vPublicJsonPro;
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
    QList<JsonProperty> &jsonPro = PublicFunc::vPublicJsonPro;
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
