#ifndef CIRCLEPROBARPROPERTY_H
#define CIRCLEPROBARPROPERTY_H
#include "basecomonentproperty.h"

class CircleProBarProperty : public BaseComonentProperty{
public:
    CircleProBarProperty():BaseComonentProperty(),color(QColor(255,255,255)),baseColor(QColor(255,255,255)),
        penWidth(0),minValue(0),maxValue(0),currentValue(0)
    {}
    bool parseJsonData(QJsonValue component)
    {
        BaseComonentProperty::parseJsonData(component);
        QJsonObject compObj = component.toObject();
        QJsonObject::iterator iter = compObj.find("penWidth");
        if(iter != compObj.end())
        {
            penWidth = iter.value().toInt();
        }
        iter = compObj.find("minValue");
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

    void addTreeWidgetItem(QList<QTreeWidgetItem *>layerList)
    {
        BaseComonentProperty::addTreeWidgetItem(layerList);
        if(bigChildItem == NULL) return ;
        QVector<QStringList> vStrList;
        QStringList list;
        list << "penWidth" << QString("%1").arg(penWidth);
        vStrList.append(list);
        list.clear();

        list << "minValue" << QString("%1").arg(minValue);
        vStrList.append(list);
        list.clear();

        list << "maxValue" << QString("%1").arg(maxValue);
        vStrList.append(list);
        list.clear();

        list << "currentValue" << QString("%1").arg(currentValue);
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

    bool setData(const SearchType &st)
    {
        if(!BaseComonentProperty::setData(st)) return false;
        QString str = st.item.text(0);
        QString value = st.item.text(1);
        QString cName = st.parentName;
        if(str.compare("penWidth") == 0)
        {
            penWidth = value.toInt();

        }
        else if(str.compare("minValue") == 0)
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

    void saveJsonData(QJsonObject &obj)
    {
        BaseComonentProperty::saveJsonData(obj);
        //QJsonObject obj;
        obj.insert("penWidth",penWidth);
        obj.insert("minValue",minValue);
        obj.insert("maxValue",maxValue);
        obj.insert("currentValue",currentValue);

        obj.insert("color",saveColorData(color));

        obj.insert("baseColor",saveColorData(baseColor));

        //array.append(obj);
    }

    void initData()
    {
        QRectF rectangle = QRectF(x,y,width,height);
        circleBar.setData(rectangle,color,baseColor,penWidth,minValue,maxValue);
        circleBar.setValue(currentValue);
    }

    void draw(QPainter &painter)
    {
        QRectF rectangle = QRectF(x,y,width,height);
        circleBar.setData(rectangle,color,baseColor,penWidth,minValue,maxValue);
        circleBar.setValue(currentValue);
        circleBar.draw(painter);
    }

public:
    QColor color;
    QColor baseColor;
    int penWidth;
    int minValue;
    int maxValue;
    int currentValue;
    CircleProgressBar circleBar;
};

#endif // CIRCLEPROBARPROPERTY_H

