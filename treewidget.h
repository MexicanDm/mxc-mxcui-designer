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
    QVector<JsonProperty> vTreeJsonPro;

signals:
    void sigUpdateSta(SearchType sType);
public slots:
    void slotDisplayJsonFile(QVector<JsonProperty> vJsonPro);
    void slotOpenPersistentEditor(QTreeWidgetItem* item,int column);
    void slotSelectionChanged(QTreeWidgetItem* changedItem,int column);
};

#endif // TREEWIDGET_H
