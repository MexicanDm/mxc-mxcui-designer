#ifndef ROUNDRECTPROGRESSBARPROPERTY_H
#define ROUNDRECTPROGRESSBARPROPERTY_H
#include "basecomonentproperty.h"

class RoundRectProgressBarProperty : public BaseComonentProperty{
public :
    RoundRectProgressBarProperty() : BaseComonentProperty(),color(QColor(255,255,255)),baseColor(QColor(255,255,255)),
        radius(0),minValue(0),maxValue(0),currentValue(0)
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
        iter = compObj.find("radius");
        if(iter != compObj.end())
        {
            radius = iter.value().toInt();
        }
        return true;
    }

    bool setData(const SearchType &st)
    {
        if(!BaseComonentProperty::setData(st)) return false;
        QString str = st.item.text(0);
        QString value = st.item.text(1);
        QString cName = st.parentName;
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
        else if(str.compare("radius") == 0)
        {
            radius = value.toInt();
        }
        return true;
    }

    void addTreeWidgetItem(QList<QTreeWidgetItem *> layerList)
    {
        BaseComonentProperty::addTreeWidgetItem(layerList);
        if(bigChildItem == NULL) return ;
        QVector<QStringList> vStrList;
        QStringList list;

        list << "minValue" << QString("%1").arg(minValue);
        vStrList.append(list);
        list.clear();

        list << "maxValue" << QString("%1").arg(maxValue);
        vStrList.append(list);
        list.clear();

        list << "currentValue" << QString("%1").arg(currentValue);
        vStrList.append(list);
        list.clear();

        list << "radius" << QString("%1").arg(radius);
        vStrList.append(list);
        list.clear();

        for(int k = 0;k < vStrList.count();k++)
        {
            new QTreeWidgetItem(bigChildItem,vStrList[k]);
        }

        list << "color";
        QTreeWidgetItem *itemColor = new QTreeWidgetItem(bigChildItem,list);
        addColorItem(itemColor,color);

        list << "baseColor";
        QTreeWidgetItem *baseColorItem = new QTreeWidgetItem(bigChildItem,list);
        addColorItem(baseColorItem,baseColor);
    }

    void saveJsonData(QJsonObject &obj)
    {
        BaseComonentProperty::saveJsonData(obj);
        obj.insert("minValue",minValue);
        obj.insert("maxValue",maxValue);
        obj.insert("currentValue",currentValue);
        obj.insert("radius",radius);

        obj.insert("color",saveColorData(color));

        obj.insert("baseColor",saveColorData(baseColor));
    }

    void draw(QPainter &painter)
    {
        roundRectBar.setData(x,y,width,height,color,baseColor,radius,minValue,maxValue);
        roundRectBar.setValue(currentValue);
        roundRectBar.draw(painter);
    }
public:
    QColor color;
    QColor baseColor;
    int radius;
    int minValue;
    int maxValue;
    int currentValue;
    RoundRectProgressBar roundRectBar;
};

#endif // ROUNDRECTPROGRESSBARPROPERTY_H
