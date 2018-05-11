#ifndef TREEWIDGET_H
#define TREEWIDGET_H

#include <QWidget>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include "publicfunc.h"



class TreeWidget : public QTreeWidget
{
    Q_OBJECT
public:
    explicit TreeWidget(QWidget *parent = 0);
private:
    QTreeWidgetItem *lastOpen;


signals:
    void sigUpdateSta(SearchType sType);
    void sigDisplayJsonProperty();
public slots:
    void slotDisplayJsonFile();
    void slotOpenPersistentEditor(QTreeWidgetItem* item,int column);
    void slotSelectionChanged(QTreeWidgetItem* changedItem,int column);
};

#endif // TREEWIDGET_H
