#ifndef TEXTEDITPROPERTY_H
#define TEXTEDITPROPERTY_H
#include "basecomonentproperty.h"

class TextEditProperty : public BaseComonentProperty{
public:
    TextEditProperty() : BaseComonentProperty(),text(""),vflags("AlignVCenter"),hflags("AlignHCenter"),backgroundColor(QColor(255,255,255))
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

        iter = compObj.find("backgroundColor");
        if(iter != compObj.end())
        {

            backgroundColor = parseColor(iter);
        }
        return true;
    }

    bool setData(const SearchType &st)
    {
        if(!BaseComonentProperty::setData(st)) return false;
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
        else if(cName.compare("backgroundColor") == 0)
        {
            setColorData(str,backgroundColor,value);
        }
        return true;
    }

    void saveJsonData(QJsonObject &obj)
    {
        BaseComonentProperty::saveJsonData(obj);
        obj.insert("text",text);
        QStringList list;

        list << "alignment" << "horizontal" << hflags << "vertical" << vflags;
        saveJsonStrItem(obj,list);
        list.clear();

        list << "backgroundColor" << "R" << QString("%1").arg(backgroundColor.red()) << "G" << QString("%1").arg(backgroundColor.green()) << "B" << QString("%1").arg(backgroundColor.blue());
        saveJsonStrItem(obj,list);

    }

    void addTreeWidgetItem(QList<QTreeWidgetItem *> layerList)
    {
        BaseComonentProperty::addTreeWidgetItem(layerList);
        if(bigChildItem == NULL) return ;
        QStringList list;

        list << "text" << text;
        addTreeWidgetStrListItem(bigChildItem,list,false);
        list.clear();


        list << "alignment" << "horizontal" << hflags << "vertical" << vflags;
        addTreeWidgetHaveChildStrItem(bigChildItem,list);
        list.clear();

        list << "backgroundColor" << "R" << QString("%1").arg(backgroundColor.red()) << "G" << QString("%1").arg(backgroundColor.green()) << "B" << QString("%1").arg(backgroundColor.blue());
        addTreeWidgetHaveChildStrItem(bigChildItem,list);
    }

    void draw(QPainter &painter)
    {
        textedit.setData(x,y,width,height,fontcolor,backgroundColor,&baseFont,vflagMap.value(vflags) | hflagMap.value(hflags),text);
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

