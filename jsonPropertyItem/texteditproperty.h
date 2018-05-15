#ifndef TEXTEDITPROPERTY_H
#define TEXTEDITPROPERTY_H
#include "basecomonentproperty.h"

class TextEditProperty : public BaseComonentProperty{
public:
    TextEditProperty() : BaseComonentProperty(),text(""),vflags(""),hflags(""),backgroundColor(QColor(255,255,255))
    {

    }

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

        iter = compObj.find("backgroundcolor");
        if(iter != compObj.end())
        {

            backgroundColor = parseColor(iter);
        }
        return true;
    }

    bool setData(const SearchType &st)
    {
        if(!BaseComonentProperty::setData(st)) return false;
        QString str = st.item.text(0);
        QString value = st.item.text(1);
        QString cName = st.parentName;

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
        else if(cName.compare("backgroundcolor") == 0)
        {
            setColorData(str,backgroundColor,value);
        }
        return true;
    }

    void saveJsonData(QJsonObject &obj)
    {
        BaseComonentProperty::saveJsonData(obj);
        obj.insert("text",text);

        QJsonObject alignmentObj;
        alignmentObj.insert("horizontal",hflags);
        alignmentObj.insert("vertical",vflags);
        obj.insert("alignment",alignmentObj);

        obj.insert("color",saveColorData(backgroundColor));
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

        list << "alignment";
        QTreeWidgetItem *itemAlignment = new QTreeWidgetItem(bigChildItem,list);
        list.clear();
        vStrList.clear();
        list << "horizontal" << hflags;
        vStrList.append(list);
        list.clear();

        list << "vertical" << vflags;
        vStrList.append(list);
        list.clear();

        for(int k = 0;k < vStrList.count();k++)
        {
            new QTreeWidgetItem(itemAlignment,vStrList[k]);
        }

        list << "backgroundcolor";
        QTreeWidgetItem *itembgColor = new QTreeWidgetItem(bigChildItem,list);
        addColorItem(itembgColor,backgroundColor);
    }

    void draw(QPainter &painter)
    {
        textedit.setData(x,y,width,height,fontcolor,backgroundColor,&baseFont,vflagsMap.value(vflags) | hflagsMap.value(hflags),text);
        textedit.draw(painter);
    }

public:
    QString text;
    QString vflags;
    QString hflags;
    QColor backgroundColor;
    TextEdit textedit;
};

#endif // TEXTEDITPROPERTY_H

