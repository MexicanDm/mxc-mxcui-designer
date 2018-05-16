#ifndef IMAGEBUTTONPROPERTY_H
#define IMAGEBUTTONPROPERTY_H

#include "basecomonentproperty.h"

/**
 * @brief The ImageButtonProperty class ImageButton
 */
class ImageButtonProperty : public BaseComonentProperty{
public:
    ImageButtonProperty() : BaseComonentProperty(),color(QColor(255,255,255)),text(""),vflags("AlignBottom"),hflags("AlignLeft")
    {}
    bool parseJsonData(QJsonValue component)
    {
        if(!BaseComonentProperty::parseJsonData(component)) return false;
        QJsonObject compObj = component.toObject();
        QJsonObject::iterator iter = compObj.find("color");
        if(iter != compObj.end())
        {
            color = parseColor(iter);
        }
        iter = compObj.find("alignment");
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

        list << "color" << "R" << QString("%1").arg(color.red()) << "G" << QString("%1").arg(color.green()) << "B" << QString("%1").arg(color.blue());
        addTreeWidgetStrItem(bigChildItem,list);
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
        else if(cName.compare("color") == 0)
        {
            setColorData(str,color,value);
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
        list.clear();

        list << "color" << "R" << QString("%1").arg(color.red()) << "G" << QString("%1").arg(color.green()) << "B" << QString("%1").arg(color.blue());
        saveJsonStrItem(obj,list);
    }

    void draw(QPainter &painter)
    {
        imageBtn.setData(x,y,width,height);
        imageBtn.setImage(resinActive,resActive);
        imageBtn.setTextInfo(fontcolor,&baseFont,vflagMap.value(vflags) | hflagMap.value(hflags));
        imageBtn.setText(text);
        imageBtn.draw(painter);
    }

public:
    QColor color;
    QString text;
    QString vflags;
    QString hflags;
    ImageButton imageBtn;
};


#endif // IMAGEBUTTONPROPERTY_H

