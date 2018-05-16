#ifndef WIFICUSTOMBUTTONPROPERTY_H
#define WIFICUSTOMBUTTONPROPERTY_H
#include "basecomonentproperty.h"

class WifiCustomButtonProperty : public BaseComonentProperty
{
public:
    WifiCustomButtonProperty() : BaseComonentProperty(),text(""),vflags("AlignBottom"),hflags("AlignLeft")
    {}
    bool parseJsonData(QJsonValue component)
    {
        if(!BaseComonentProperty::parseJsonData(component)) return false;
        QJsonObject compObj = component.toObject();
        QJsonObject::iterator iter = compObj.find("alignment");
        if(iter != compObj.end())
        {
            QJsonObject alignmentObj = iter.value().toObject();
            iter = alignmentObj.find("horizontal");
            if(iter != alignmentObj.end())
            {
                hflags = iter.value().toString();
            }
            iter = alignmentObj.find("vertical");
            if(iter != alignmentObj.end())
            {
                vflags = iter.value().toString();
            }
        }
        iter = compObj.find("text");
        if(iter != compObj.end())
        {
            text = iter.value().toString();
        }
        return true;
    }

    void addTreeWidgetItem(QList<QTreeWidgetItem *> layerList)
    {
        BaseComonentProperty::addTreeWidgetItem(layerList);
        if(bigChildItem == NULL) return ;
        QVector<QStringList> vStrList;
        QStringList list;

        list << "text" << text;
        vStrList.append(list);
        list.clear();

        for(int k = 0;k < vStrList.count();k++)
        {
            new QTreeWidgetItem(bigChildItem,vStrList[k]);
        }

        list << "alignment" << "horizontal" << hflags << "vertical" << vflags;
        addTreeWidgetStrItem(bigChildItem,list);
        list.clear();

    }

    bool setData(const SearchType &st)
    {
        if(!BaseComonentProperty::setData(st))return false;
        QString str = st.item->text(0);
        QString value = st.item->text(1);
        QString cName = st.cpName;

        if(str.compare("text") == 0)
        {
            text = value;
        }
        else if(cName.compare("alignment") == 0)
        {
            if(str.compare("horizontal") == 0)
            {
                hflags = value;
            }
            else if(str.compare("vertical") == 0)
            {
                vflags = value;
            }
        }
        return true;
    }

    void saveJsonData(QJsonObject &obj)
    {
        BaseComonentProperty::saveJsonData(obj);
        obj.insert("text",text);

        QStringList strlist;
        strlist << "alignment" << "horizontal" << hflags << "vertical" << vflags;
        saveJsonStrItem(obj,strlist);
    }

    void draw(QPainter &painter)
    {
        wificustomBtn.setData(x,y,width,height);
        wificustomBtn.setText(text);
        wificustomBtn.setImage(resinActive,resActive);
        wificustomBtn.setTextInfo(fontcolor,&baseFont,vflagMap.value(vflags) | hflagMap.value(hflags));
        wificustomBtn.draw(painter);
    }
public:
    QString text;
    QString vflags;
    QString hflags;
    WifiCustomButton wificustomBtn;
};

#endif // WIFICUSTOMBUTTONPROPERTY_H

