#ifndef WIFIALPHABETKEYBOARDPROPERTY_H
#define WIFIALPHABETKEYBOARDPROPERTY_H
#include "basecomonentproperty.h"

class WifiAlphabetKeyboardProperty : public BaseComonentProperty{
public:
    WifiAlphabetKeyboardProperty() : BaseComonentProperty()
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
        wifiKeyboard.init(&baseFont);
        wifiKeyboard.draw(painter);
    }
public:
    WifiAlphabetKeyboard wifiKeyboard;
};

#endif // WIFIALPHABETKEYBOARDPROPERTY_H

