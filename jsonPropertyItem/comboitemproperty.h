#ifndef COMBOITEM_H
#define COMBOITEM_H
#include "basecomonentproperty.h"

class ComboItemProperty : public BaseComonentProperty
{
public:
    ComboItemProperty() : BaseComonentProperty(),textPos(QPoint(0,0)),text(""),vflags("AlignBottom"),hflags("AlignLeft")
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
        iter = compObj.find("textPos");
        if(iter != compObj.end())
        {
            QJsonObject alignmentObj = iter.value().toObject();
            iter = alignmentObj.find("tx");
            if(iter != alignmentObj.end())
            {
                textPos.setX(iter.value().toInt());
            }
            iter = alignmentObj.find("ty");
            if(iter != alignmentObj.end())
            {
                textPos.setY(iter.value().toInt());
            }
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

        list << "textPos" << "tx" << QString("%1").arg(textPos.x()) << "ty" << QString("%1").arg(textPos.y());
        addTreeWidgetStrItem(bigChildItem,list);
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
        else if(cName.compare("textPos") == 0)
        {
            if(str.compare("tx") == 0)
            {
                textPos.setX(value.toInt());
            }
            else if(str.compare("ty") == 0)
            {
                textPos.setY(value.toInt());
            }
        }
        return true;
    }

    void saveJsonData(QJsonObject &obj)
    {
        BaseComonentProperty::saveJsonData(obj);
        obj.insert("text",text);

        QStringList strlist;
        strlist << "textPos" << "tx" << QString("%1").arg(textPos.x()) << "ty" << QString("%1").arg(textPos.y());
        saveJsonStrItem(obj,strlist);
        strlist.clear();

        strlist << "alignment" << "horizontal" << hflags << "vertical" << vflags;
        saveJsonStrItem(obj,strlist);
    }

    void draw(QPainter &painter)
    {
        comitem.setData(x,y,width,height);
        comitem.setText(text);
        comitem.setTextInfo(textPos.x(),textPos.y(),fontcolor,&baseFont,vflagMap.value(vflags) | hflagMap.value(hflags));
        comitem.draw(painter,QPoint(0,0));
    }

public:
    QPoint textPos;
    QString text;
    QString vflags;
    QString hflags;
    ComboItem comitem;
};

#endif // COMBOITEM_H
