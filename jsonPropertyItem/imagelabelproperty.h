#ifndef IMAGELABELPROPERTY_H
#define IMAGELABELPROPERTY_H
#include "basecomonentproperty.h"

class ImageLabelProperty : public BaseComonentProperty
{
public:
    ImageLabelProperty() : BaseComonentProperty()
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

    void initData()
    {
        if(x != INVAILD_DATA && y != INVAILD_DATA && (!resActive.isEmpty()))
        {
            imagelabel.setData(selectDefaultName(resActive),x,y);
            imagelabel.setPos(x,y);
        }
    }

    void draw(QPainter &painter)
    {
        imagelabel.draw(painter);
    }
public:
    //QString imageFilePath;
    ImageLabel imagelabel;
};

#endif // IMAGELABELPROPERTY_H

