#ifndef NUMBERKEYBOARDPROPERTY_H
#define NUMBERKEYBOARDPROPERTY_H

#include "basecomonentproperty.h"

class NumberKeyboardProperty : public BaseComonentProperty
{
public:
    NumberKeyboardProperty() : BaseComonentProperty()
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
        numKeyboard.init(&baseFont);
        numKeyboard.draw(painter);
    }
public:
    NumberKeyboard numKeyboard;

};

#endif // NUMBERKEYBOARDPROPERTY_H

