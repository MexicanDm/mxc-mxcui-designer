#ifndef SOLIDLINEPROPERTY_H
#define SOLIDLINEPROPERTY_H
#include "basecomonentproperty.h"
class RealLineProperty : public BaseComonentProperty
{
public:
    RealLineProperty() : BaseComonentProperty()
    {}
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
        sl.setData(x,y,width,height);
        sl.draw(painter);
    }
public:
    RealLine sl;
};

#endif // SOLIDLINEPROPERTY_H

