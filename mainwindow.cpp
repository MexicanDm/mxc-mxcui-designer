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
    QObject::connect(this,SIGNAL(sigPaintWidgetRect(int,int)),ui->disWidget,SLOT(slotPaintWidgetRect(int,int)));
    QObject::connect(ui->btn_HV,SIGNAL(clicked(bool)),this,SLOT(slotBtnHV()));

    QTimer::singleShot(500, this, SLOT(slotReadBtnSta()));
    bHV = false;
    QTimer::singleShot(500, this, SLOT(slotBtnHV()));

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

#if 1
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
#endif
#if 0
void MainWindow::slotSaveFile()
{
    QTreeWidgetItemIterator it(ui->treeWidget);
    QString sAppPath = QCoreApplication::applicationDirPath();
    QFile fileW;
    QJsonDocument doc;
    QList<QJsonObject> objList;
    objList.reserve(10);
    QJsonArray array;
    int objnum = 0;
    QTreeWidgetItem *item1 = NULL;
    QTreeWidgetItem *item2 = NULL;
    while(*it)
    {
        QString leftStr;
        QCheckBox *cb = (QCheckBox*)ui->treeWidget->itemWidget((*it),0);
        if(cb == NULL)
        {
            leftStr = (*it)->text(0);
        }
        else
        {
            leftStr = cb->text();
        }
        //创建新文件
        if(leftStr.indexOf(".mxcui") > 0)
        {
            fileW.close();
            //mainObj.remove("components");
            objList.clear();
            QString filePath = sAppPath + "/json/" + leftStr;
            if(!PublicFunc::confirmFile(filePath)) return ;
            fileW.setFileName(filePath);
            if(!fileW.open(QIODevice::WriteOnly))
            {
                qDebug() << QString("[MXCUI] open file %1 failed!").arg(filePath);
                return ;
            }
            continue;
        }
        if(cb == NULL)
        {
            objList[objnum++].insert(leftStr,objList[objnum]);
        }
        else
        {
            objList[objnum]
        }


        qDebug() << (*it)->text(0);
        it++;
    }
    //mainObj.insert("components",array);
    //doc.setObject(mainObj);
}
#endif
void MainWindow::slotClear()
{
    QList<JsonProperty> &jsonPro = PublicFunc::vPublicJsonPro;
    jsonPro.clear();
    ui->treeWidget->clear();
    ui->disWidget->update();
}

void MainWindow::slotBtnHV()
{
    if(bHV)
    {
        emit sigPaintWidgetRect(600,1024);
        bHV = false;
    }
    else
    {
        emit sigPaintWidgetRect(1024,600);
        bHV = true;
    }

}

MainWindow::~MainWindow()
{
    delete ui;
}
