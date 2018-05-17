#ifndef TEXTLABELPROPERTY_H
#define TEXTLABELPROPERTY_H

#include "basecomonentproperty.h"

class TextLabelProperty : public BaseComonentProperty{
public:
    TextLabelProperty() : BaseComonentProperty(),text(""),vflag(""),hflag(""),tflag("")
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
                hflag = iter.value().toString();
            }
            iter = alignmentObj.find("vertical");
            if(iter != alignmentObj.end())
            {
                vflag = iter.value().toString();
            }
            iter = alignmentObj.find("textflag");
            if(iter != alignmentObj.end())
            {
                tflag = iter.value().toString();
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
        QStringList list;

        list << "text" << text;
        addTreeWidgetStrListItem(bigChildItem,list,false);
        list.clear();

        list << "alignment" << "horizontal" << hflag << "vertical" << vflag << "textflag" << tflag;
        addTreeWidgetHaveChildStrItem(bigChildItem,list);
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
                hflag = value;
            }
            else if(str.compare("vertical") == 0)
            {
                vflag = value;
            }
            else if(str.compare("textflag") == 0)
            {
                tflag = value;
            }
        }
        return true;
    }

    void saveJsonData(QJsonObject &obj)
    {
        BaseComonentProperty::saveJsonData(obj);
        obj.insert("text",text);

        QStringList strlist;

        strlist << "alignment" << "horizontal" << hflag << "vertical" << vflag << "textflag" << tflag;
        saveJsonStrItem(obj,strlist);
    }

    void draw(QPainter &painter)
    {
        textlab.setData(x,y,width,height,fontcolor,&baseFont,vflagMap.value(vflag) | hflagMap.value(hflag),text);
        textlab.draw(painter);
        //textlab.SetLayer(layer);
    }
public:
    QString text;
    QString vflag;
    QString hflag;
    QString tflag;
    TextLabel textlab;
};

#endif // TEXTLABELPROPERTY_H

