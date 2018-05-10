#include "treewidget.h"

TreeWidget::TreeWidget(QWidget *parent) : QTreeWidget(parent)
{
    QStringList head;
    head << "components" << "value";
    this->setColumnCount(2);
    this->setHeaderLabels(head);
    this->setColumnWidth(0,200);

    QObject::connect(this,SIGNAL(itemDoubleClicked ( QTreeWidgetItem*, int)),
            this,SLOT(slotOpenPersistentEditor(QTreeWidgetItem*,int)));

    QObject::connect(this,SIGNAL(itemSelectionChanged ()),
            this,SLOT(slotSelectionChanged()));
    lastOpen = NULL;
}

void TreeWidget::slotDisplayJsonFile(QVector<JsonProperty> vJsonPro)
{
    this->clear();
    for(int i = 0;i < vJsonPro.count();i++)
    {
        QString filename = vJsonPro[i].fileName;
        QTreeWidgetItem *fatherItem = new QTreeWidgetItem(this,QStringList(QString(filename)));
        for(int j = 0;j < vJsonPro[i].vCircleProBar.count();j++)
        {
            CircleProBarProperty circleProperty = vJsonPro[i].vCircleProBar[j];
            circleProperty.addTreeWidgetItem(fatherItem);
        }
    }
}



void TreeWidget::slotOpenPersistentEditor(QTreeWidgetItem* item,int column)
{
    if( 1 == column  )
    {
        this->openPersistentEditor(item,column);
        lastOpen = item;
    }
}
void TreeWidget::slotSelectionChanged()
{
    if( NULL!= lastOpen )
    {
        this->closePersistentEditor(lastOpen,1);
        lastOpen = NULL;
    }
}

