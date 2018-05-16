#ifndef INFOCONFIRMPANELPROPERTY_H
#define INFOCONFIRMPANELPROPERTY_H

#include "basecomonentproperty.h"
class InfoConfirmPanelProperty : public BaseComonentProperty
{
public:
    InfoConfirmPanelProperty() : BaseComonentProperty(),wholeW(0),wholeH(0),text("")
    {}
    bool parseJsonData(QJsonValue component)
    {
        if(!BaseComonentProperty::parseJsonData(component)) return false;
        QJsonObject compObj = component.toObject();
        QJsonObject::iterator iter = compObj.find("wholeWidth");
        if(iter != compObj.end())
        {
            wholeW = iter.value().toInt();
        }
        iter = compObj.find("wholeHeight");
        if(iter != compObj.end())
        {
            wholeH = iter.value().toInt();
        }
        iter = compObj.find("text");
        if(iter != compObj.end())
        {
            text = iter.value().toString();
        }
        return true;
    }

    void addTreeWidgetItem(QList<QTreeWidgetItem *>layerList)
    {
        BaseComonentProperty::addTreeWidgetItem(layerList);
        QVector<QStringList> vStrList;
        QStringList list;
        list << "wholeWidth" << QString("%1").arg(wholeW);
        vStrList.append(list);
        list.clear();

        list << "wholeHeight" << QString("%1").arg(wholeH);
        vStrList.append(list);
        list.clear();

        list << "text" << text;
        vStrList.append(list);
        list.clear();

        for(int k = 0;k < vStrList.count();k++)
        {
            new QTreeWidgetItem(bigChildItem,vStrList[k]);
        }
    }

    bool setData(const SearchType &st)
    {
        if(!BaseComonentProperty::setData(st)) return false;
        QString str = st.item.text(0);
        QString value = st.item.text(1);
        //QString cName = st.cpName;
        if(str.compare("wholeWidth") == 0)
        {
            wholeW = value.toInt();

        }
        else if(str.compare("wholeHeight") == 0)
        {
            wholeH = value.toInt();
        }
        else if(str.compare("text") == 0)
        {
            text = value;
        }
        return true;
    }

    void saveJsonData(QJsonObject &obj)
    {
        BaseComonentProperty::saveJsonData(obj);
        obj.insert("wholeWidth",wholeW);
        obj.insert("wholeHeight",wholeH);
        obj.insert("text",text);
    }

    void draw(QPainter &painter)
    {
        infoConfirmPanel.init(&baseFont);
        infoConfirmPanel.setData(x,y,width,height,wholeW,wholeH);
        infoConfirmPanel.setText(text);
        infoConfirmPanel.setTextInfo(&baseFont,fontcolor);

        infoConfirmPanel.draw(painter);
    }
public:
    int wholeW;
    int wholeH;
    QString text;
    InfoConfirmPanel infoConfirmPanel;
};
#endif // INFOCONFIRMPANELPROPERTY_H

