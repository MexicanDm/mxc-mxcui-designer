#ifndef TEMPTEXTPROPERTY_H
#define TEMPTEXTPROPERTY_H
#include "basecomonentproperty.h"

class TargetTempTextProperty : public BaseComonentProperty{
public:
    TargetTempTextProperty() : BaseComonentProperty(),text("")
    {
        aflag.hflag = "AlignHCenter";
        aflag.vflag = "AlignTop";
        aflag.tflag = "";
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
                aflag.hflag = iter.value().toString();
            }
            iter = alignmentObj.find("vertical");
            if(iter != alignmentObj.end())
            {
                aflag.vflag = iter.value().toString();
            }
            iter = alignmentObj.find("textflag");
            if(iter != alignmentObj.end())
            {
                aflag.tflag = iter.value().toString();
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

        list << "alignment" << "horizontal" << aflag.hflag << "vertical" << aflag.vflag << "textflag" << aflag.tflag;
        addTreeWidgetHaveChildStrItem(bigChildItem,list);
        list.clear();

    }

    bool setData(const SearchType &st)
    {
        if(!BaseComonentProperty::setData(st)) return false;
        QString str = st.changeStr;
        QString value = st.changeValue;
        QString cName = st.cpName;

        if(str.compare("text") == 0)
        {
            text = value;
        }
        else if(cName.compare("alignment") == 0)
        {
            if(str.compare("horizontal") == 0)
            {
                aflag.hflag = value;
            }
            else if(str.compare("vertical") == 0)
            {
                aflag.vflag = value;
            }
            else if(str.compare("textflag") == 0)
            {
                aflag.tflag = value;
            }
        }
        return true;
    }

    void saveJsonData(QJsonObject &obj)
    {
        BaseComonentProperty::saveJsonData(obj);

        obj.insert("text",text);

        QStringList list;

        list << "alignment" << "horizontal" << aflag.hflag << "vertical" << aflag.vflag << "textflag" << aflag.tflag;
        saveJsonStrItem(obj,list);
        list.clear();

    }

    void draw(QPainter &painter)
    {
        temptext.setData(x,y,width,height,vflagMap.value(aflag.vflag) | hflagMap.value(aflag.hflag) | tflagMap.value(aflag.tflag),text);
        painter.setFont(baseFont);
        painter.setPen(fontcolor);
        painter.setBrush(fontcolor);
        temptext.draw(painter);
    }
public:
    QString text;
    AlignmentFlag aflag;
    TargetTempText temptext;
};

#endif // TEMPTEXTPROPERTY_H

