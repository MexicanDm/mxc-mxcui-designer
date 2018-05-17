#ifndef LISTBOXPROPERTY_H
#define LISTBOXPROPERTY_H

#include "basecomonentproperty.h"
class ListBoxProperty : public BaseComonentProperty
{
public:
    ListBoxProperty() : BaseComonentProperty(),listnum(1)
    {}
    bool parseJsonData(QJsonValue component)
    {
        if(!BaseComonentProperty::parseJsonData(component)) return false;
        QJsonObject compObj = component.toObject();
        QJsonObject::iterator iter = compObj.find("listnum");
        if(iter != compObj.end())
        {
            listnum = iter.value().toInt();
        }
        return true;
    }

    void addTreeWidgetItem(QList<QTreeWidgetItem *>layerList)
    {
        BaseComonentProperty::addTreeWidgetItem(layerList);
        if(bigChildItem == NULL) return ;
        QStringList list;
        list << "listnum" << QString("%1").arg(listnum);

        addTreeWidgetStrListItem(bigChildItem,list,false);
        list.clear();
    }

    bool setData(const SearchType &st)
    {
        if(!BaseComonentProperty::setData(st)) return false;
        QString str = st.item->text(0);
        QString value = st.item->text(1);
        if(str.compare("listnum") == 0)
        {
            listnum = value.toInt();

        }
        return true;
    }

    void saveJsonData(QJsonObject &obj)
    {
        BaseComonentProperty::saveJsonData(obj);
        obj.insert("listnum",listnum);
    }

    void draw(QPainter &painter)
    {
        Q_UNUSED(painter);
        //listbox.setData(x,y);
        //listbox.initWithSize(listnum);
        //listbox.setVisible(true);
        //listbox.draw(painter);
    }
public:
    int listnum;
    ListBox listbox;
};

#endif // LISTBOXPROPERTY_H

