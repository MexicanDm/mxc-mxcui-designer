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

public slots:
    void slotDisplayJsonFile(QVector<JsonProperty> vJsonPro);
    void slotOpenPersistentEditor(QTreeWidgetItem* item,int column);
    void slotSelectionChanged();
};

#endif // TREEWIDGET_H
