#ifndef CHECKBOXPROPERTY_H
#define CHECKBOXPROPERTY_H

#include "basecomonentproperty.h"

class CheckBoxProperty : public BaseComonentProperty
{
public:
    CheckBoxProperty() : BaseComonentProperty(),vflags("AlignVCenter"),hflags("AlignHCenter"),text("")
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

    void addTreeWidgetItem(QList<QTreeWidgetItem *>layerList)
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

    void draw(QPainter &painter)
    {
        vCheckBox.setData(x,y,width,height);
        vCheckBox.setImage(selectDefaultName(resinActive),selectDefaultName(resActive));
        vCheckBox.setTextInfo(fontcolor,&baseFont);
        vCheckBox.setText(text);
        vCheckBox.setTextOffset(0,0);
        vCheckBox.setTextFlags(vflagMap.value(vflags) | hflagMap.value(hflags));
        vCheckBox.draw(painter);

    }


public:
    //QColor switchColor;
    QString vflags;
    QString hflags;
    QString text;
    CheckBox vCheckBox;

};

#endif // CHECKBOXPROPERTY_H

