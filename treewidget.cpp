#include "treewidget.h"

TreeWidget::TreeWidget(QWidget *parent) : QTreeWidget(parent)
{
    QStringList head;
    head << "components" << "value";
    this->setColumnCount(2);
    this->setHeaderLabels(head);
    this->setColumnWidth(0,200);
    this->setStyleSheet("QTreeWidget::item{height:20px}");

    QObject::connect(this,SIGNAL(itemDoubleClicked ( QTreeWidgetItem*, int)),this,SLOT(slotOpenPersistentEditor(QTreeWidgetItem*,int)));
    QObject::connect(this,SIGNAL(itemChanged(QTreeWidgetItem*,int)),this,SLOT(slotSelectionChanged(QTreeWidgetItem*,int)));
    lastOpen = NULL;
}

void TreeWidget::slotDisplayJsonFile()
{
    //this->clear();
    const QList<JsonProperty> &vJsonPro = PublicFunc::vPublicJsonPro;
    for(int i = 0;i < vJsonPro.count();i++)
    {
        QString filename = vJsonPro[i].fileName;
        const JsonProperty &jsonpro = vJsonPro[i];
        QTreeWidgetItem *fatherItem = new QTreeWidgetItem(this,QStringList(QString(filename)));
        QTreeWidgetItem *layerItem0 = new QTreeWidgetItem(fatherItem,QStringList(QString("Layer_0")));
        QTreeWidgetItem *layerItem1 = new QTreeWidgetItem(fatherItem,QStringList(QString("Layer_1")));
        QTreeWidgetItem *layerItem2 = new QTreeWidgetItem(fatherItem,QStringList(QString("Layer_2")));
        QList<QTreeWidgetItem*> layerList;
        layerList << layerItem0 << layerItem1 << layerItem2;
        for(int j = 0;j < jsonpro.vTotalJsonProperty.count();j++)
        {
            BaseComonentProperty *pro = jsonpro.vTotalJsonProperty[j];
            pro->addTreeWidgetItem(layerList);
        }
    }
    emit sigDisplayJsonProperty();
}



void TreeWidget::slotOpenPersistentEditor(QTreeWidgetItem* item,int column)
{
    if( 1 == column  )
    {
        if(item->child(0) != NULL || (item->text(0).compare("type") == 0)) return;
        this->openPersistentEditor(item,column);
        lastOpen = item;
    }
}
void TreeWidget::slotSelectionChanged(QTreeWidgetItem* changedItem,int column)
{
    Q_UNUSED(column);
    if( NULL!= lastOpen )
    {
        this->closePersistentEditor(lastOpen,1);
        lastOpen = NULL;
        SearchType st;
        QTreeWidgetItem* parentItem = changedItem->parent();
        QString pText = changedItem->text(0);
        if(pText.compare("R") == 0 || pText.compare("G") == 0 || pText.compare("B") == 0)
        {
            st.colorName = parentItem->text(0);
            parentItem = parentItem->parent();
            pText = parentItem->text(0);
        }
        else
        {
            st.colorName = "";
        }

        st.fileName = parentItem->parent()->parent()->text(0);
        st.structName = parentItem->text(0);
        st.structType = parentItem->child(0)->text(1);
        st.item = *changedItem;
        emit sigUpdateSta(st);
    }
}





