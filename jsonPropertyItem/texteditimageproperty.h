#ifndef TEXTEDITIMAGEPROPERTY_H
#define TEXTEDITIMAGEPROPERTY_H
#include "basecomonentproperty.h"

class TextEditImageProperty : public BaseComonentProperty{
public:
    TextEditImageProperty() : BaseComonentProperty(),text(""),vflags("AlignVCenter"),hflags("AlignHCenter")
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

        return true;
    }

    void saveJsonData(QJsonObject &obj)
    {
        BaseComonentProperty::saveJsonData(obj);
        obj.insert("text",text);

        QStringList list;

        list << "alignment" << "horizontal" << hflags << "vertical" << vflags;
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
    }

    void draw(QPainter &painter)
    {
        texteditImage.setData(x,y,width,height,fontcolor,&baseFont,vflagMap.value(vflags) | hflagMap.value(hflags),text);
        texteditImage.draw(painter);
    }

public:
    QString text;
    QString vflags;
    QString hflags;
    TextEditImage texteditImage;
};

#endif // TEXTEDITIMAGEPROPERTY_H
