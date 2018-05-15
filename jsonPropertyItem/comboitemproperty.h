#ifndef COMBOITEM_H
#define COMBOITEM_H
#include "basecomonentproperty.h"

class ComboBoxProperty : public BaseComonentProperty
{
public:
    ComboBoxProperty() : BaseComonentProperty()
    {}
    bool parseJsonData(QJsonValue component)
    {
        if(!BaseComonentProperty::parseJsonData(component)) return false;

         return true;
    }

    bool setData(const SearchType &st)
    {
        if(!BaseComonentProperty::setData(st)) return false;

        return true;
    }

    void addTreeWidgetItem(QList<QTreeWidgetItem *> layerList)
    {
        BaseComonentProperty::addTreeWidgetItem(layerList);
    }

    void saveJsonData(QJsonObject &obj)
    {
        BaseComonentProperty::saveJsonData(obj);
    }

    void draw(QPainter &painter)
    {
        Q_UNUSED(painter);
    }

public:
    ComboBox combox;
};

#endif // COMBOITEM_H
