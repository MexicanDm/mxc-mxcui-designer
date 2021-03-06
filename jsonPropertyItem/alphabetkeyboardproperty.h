#ifndef ALPHABETKEYBOARDPROPERTY_H
#define ALPHABETKEYBOARDPROPERTY_H

#include "basecomonentproperty.h"

class AlphabetKeyboardProperty : public BaseComonentProperty
{
public:
    AlphabetKeyboardProperty() : BaseComonentProperty()
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
        alKeyboard.init(&baseFont);
        alKeyboard.draw(painter);
    }
public:
    AlphabetKeyboard alKeyboard;


};

#endif // ALPHABETKEYBOARDPROPERTY_H

