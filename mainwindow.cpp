#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    cBtnSta << -1 << -1 << -1;
    QObject::connect(ui->pBtnOpenFile,SIGNAL(clicked(bool)),this,SLOT(slotOpenFile()));
    QObject::connect(ui->pBtnSaveFile,SIGNAL(clicked(bool)),this,SLOT(slotSaveFile()));
    QObject::connect(this,SIGNAL(sigDisplayJsonProperty()),ui->treeWidget,SLOT(slotDisplayJsonFile()));
    QObject::connect(ui->treeWidget,SIGNAL(sigDisplayJsonProperty()),ui->disWidget,SLOT(update()));
    QObject::connect(ui->treeWidget,SIGNAL(sigUpdateSta(SearchType)),ui->disWidget,SLOT(slotUpdateSta(SearchType)));
    QObject::connect(ui->cBox0,SIGNAL(clicked(bool)),this,SLOT(slotcBtnSta()));
    QObject::connect(ui->cBox1,SIGNAL(clicked(bool)),this,SLOT(slotcBtnSta()));
    QObject::connect(ui->cBox2,SIGNAL(clicked(bool)),this,SLOT(slotcBtnSta()));
    QObject::connect(this,SIGNAL(sigLayerSta(QList<int>)),ui->disWidget,SLOT(slotSetLayerSta(QList<int>)));
    QObject::connect(ui->btnClear,SIGNAL(clicked(bool)),this,SLOT(slotClear()));
    QTimer::singleShot(500, this, SLOT(slotReadBtnSta()));


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

void MainWindow::slotcBtnSta()
{
    if(QCheckBox *btn = qobject_cast<QCheckBox*>(sender()))
    {
        if(btn == ui->cBox0)
        {
            if(ui->cBox0->isChecked())
                cBtnSta[0] = 0;
            else
                cBtnSta[0] = -1;
        }
        else if(btn == ui->cBox1)
        {
            if(ui->cBox1->isChecked())
                cBtnSta[1] = 1;
            else
                cBtnSta[1] = -1;
        }
        else if(btn == ui->cBox2)
        {
            if(ui->cBox2->isChecked())
                cBtnSta[2] = 2;
            else
                cBtnSta[2] = -1;
        }
        emit sigLayerSta(cBtnSta);
    }
}

void MainWindow::slotReadBtnSta()
{
    if(ui->cBox0->isChecked())
        cBtnSta[0] = 0;
    else
        cBtnSta[0] = -1;

    if(ui->cBox1->isChecked())
        cBtnSta[1] = 1;
    else
        cBtnSta[1] = -1;

    if(ui->cBox2->isChecked())
        cBtnSta[2] = 2;
    else
        cBtnSta[2] = -1;

    emit sigLayerSta(cBtnSta);
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

void MainWindow::slotClear()
{
    QList<JsonProperty> &jsonPro = PublicFunc::vPublicJsonPro;
    jsonPro.clear();
    ui->treeWidget->clear();
    ui->disWidget->update();
}

MainWindow::~MainWindow()
{
    delete ui;
}
