#ifndef LISTITEMPROPERTY_H
#define LISTITEMPROPERTY_H
#include "basecomonentproperty.h"
class ListItemProperty : public BaseComonentProperty
{
public:
    ListItemProperty(QPoint parentPos) : BaseComonentProperty()
    {
        parentPosition = parentPos;
    }
    bool parseJsonData(QJsonValue component)
    {
        if(!BaseComonentProperty::parseJsonData(component)) return false;

        return true;
    }

    void addTreeWidgetItem(QList<QTreeWidgetItem *>layerList)
    {
        BaseComonentProperty::addTreeWidgetItem(layerList);

    }

    bool setData(const SearchType &st)
    {
        if(!BaseComonentProperty::setData(st)) return false;

        return true;
    }

    void saveJsonData(QJsonObject &obj)
    {
        BaseComonentProperty::saveJsonData(obj);

    }

    void draw(QPainter &painter)
    {
        listitem.setData(x,y,width,height);
        listitem.setImage(selectDefaultName(resinActive),selectDefaultName(resActive));
        listitem.draw(painter,parentPosition);
    }
public:
    QPoint parentPosition;
    ListItem listitem;
};

#endif // LISTITEMPROPERTY_H

