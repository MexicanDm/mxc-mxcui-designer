#ifndef TREEWIDGET_H
#define TREEWIDGET_H

#include <QWidget>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include "publicfunc.h"
#include <QCheckBox>



class TreeWidget : public QTreeWidget
{
    Q_OBJECT
public:
    explicit TreeWidget(QWidget *parent = 0);
private:
    QTreeWidgetItem *lastOpen;
    QList<QString> vCpCompareStr;
    void updateCheckedSta(SearchType st);
signals:
    void sigUpdateSta(SearchType sType);
    void sigUpdateCheckSta(SearchType sType);
    void sigDisplayJsonProperty();
public slots:
    void slotDisplayJsonFile();
    void slotOpenPersistentEditor(QTreeWidgetItem* item,int column);
    void slotItemChanged(QTreeWidgetItem* changedItem,int column);
    void slotSeleteChanged();
};

#endif // TREEWIDGET_H
