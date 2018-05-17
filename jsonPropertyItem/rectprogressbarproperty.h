#ifndef RECTPROGRESSBARPROPERTY_H
#define RECTPROGRESSBARPROPERTY_H
#include "basecomonentproperty.h"

class RectProgressBarProperty : public BaseComonentProperty
{
public:
    RectProgressBarProperty() : BaseComonentProperty(),color(QColor(255,255,255)),baseColor(QColor(255,255,255)),
        minValue(0),maxValue(0),currentValue(0)
    {}

    bool parseJsonData(QJsonValue component)
    {
        if(!BaseComonentProperty::parseJsonData(component))return false;
        QJsonObject compObj = component.toObject();
        QJsonObject::iterator iter = compObj.find("minValue");
        if(iter != compObj.end())
        {
            minValue = iter.value().toInt();
        }
        iter = compObj.find("maxValue");
        if(iter != compObj.end())
        {
            maxValue = iter.value().toInt();
        }
        iter = compObj.find("currentValue");
        if(iter != compObj.end())
        {
            currentValue = iter.value().toInt();
        }
        iter = compObj.find("color");
        if(iter != compObj.end())
        {
            color = parseColor(iter);
        }
        iter = compObj.find("baseColor");
        if(iter != compObj.end())
        {
            baseColor = parseColor(iter);
        }
        return true;
    }

    bool setData(const SearchType &st)
    {
        if(!BaseComonentProperty::setData(st)) return false;
        QString str = st.changeStr;
        QString value = st.changeValue;
        QString cName = st.cpName;
        if(str.compare("minValue") == 0)
        {
            minValue = value.toInt();
        }
        else if(str.compare("maxValue") == 0)
        {
            maxValue = value.toInt();
        }
        else if(str.compare("currentValue") == 0)
        {
            currentValue = value.toInt();
        }
        else if(cName.compare("color") == 0)
        {
            setColorData(str,color,value);
        }
        else if(cName.compare("baseColor") == 0)
        {
            setColorData(str,baseColor,value);
        }
        return true;
    }

    void addTreeWidgetItem(QList<QTreeWidgetItem *> layerList)
    {
        BaseComonentProperty::addTreeWidgetItem(layerList);
        if(bigChildItem == NULL) return ;
        QStringList list;

        list << "minValue" << QString("%1").arg(minValue);

        list << "maxValue" << QString("%1").arg(maxValue);

        list << "currentValue" << QString("%1").arg(currentValue);
        addTreeWidgetStrListItem(bigChildItem,list,false);
        list.clear();

        list << "color" << "R" << QString("%1").arg(color.red()) << "G" << QString("%1").arg(color.green()) << "B" << QString("%1").arg(color.blue());
        addTreeWidgetHaveChildStrItem(bigChildItem,list);
        list.clear();

        list << "baseColor" << "R" << QString("%1").arg(baseColor.red()) << "G" << QString("%1").arg(baseColor.green()) << "B" << QString("%1").arg(baseColor.blue());
        addTreeWidgetHaveChildStrItem(bigChildItem,list);
    }

    void saveJsonData(QJsonObject &obj)
    {
        BaseComonentProperty::saveJsonData(obj);
        obj.insert("minValue",minValue);
        obj.insert("maxValue",maxValue);
        obj.insert("currentValue",currentValue);

        QStringList list;

        list << "color" << "R" << QString("%1").arg(color.red()) << "G" << QString("%1").arg(color.green()) << "B" << QString("%1").arg(color.blue());
        saveJsonStrItem(obj,list);
        list.clear();

        list << "baseColor" << "R" << QString("%1").arg(baseColor.red()) << "G" << QString("%1").arg(baseColor.green()) << "B" << QString("%1").arg(baseColor.blue());
        saveJsonStrItem(obj,list);
    }

    void draw(QPainter &painter)
    {
        rectBar.setData(x,y,width,height,color,baseColor,minValue,maxValue);
        rectBar.setValue(currentValue);
        rectBar.draw(painter);
    }
public:
    QColor color;
    QColor baseColor;
    int minValue;
    int maxValue;
    int currentValue;
    RectProgressBar rectBar;
};

#endif // RECTPROGRESSBARPROPERTY_H
