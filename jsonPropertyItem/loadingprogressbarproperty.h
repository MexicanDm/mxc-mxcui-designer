#ifndef LOADINGPROGRESSBARPROPERTY_H
#define LOADINGPROGRESSBARPROPERTY_H
#include "basecomonentproperty.h"

class LoadingProgressBarProperty : public BaseComonentProperty{
public:
    LoadingProgressBarProperty() : BaseComonentProperty(),color(QColor(255,255,255)),baseColor(QColor(255,255,255)),
        currentValue(0)
    {
    }
    bool parseJsonData(QJsonValue component)
    {
        if(!BaseComonentProperty::parseJsonData(component))return false;
        QJsonObject compObj = component.toObject();
        QJsonObject::iterator iter = compObj.find("currentValue");

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
        QString str = st.item.text(0);
        QString value = st.item.text(1);
        QString cName = st.parentName;
        if(str.compare("currentValue") == 0)
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
        QVector<QStringList> vStrList;
        QStringList list;

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

    void saveJsonData(QJsonObject &obj)
    {
        BaseComonentProperty::saveJsonData(obj);

        obj.insert("currentValue",currentValue);

        obj.insert("color",saveColorData(color));

        obj.insert("baseColor",saveColorData(baseColor));
    }

    void draw(QPainter &painter)
    {
        loadingBar.setData(x,y,width,height);
        loadingBar.setColor(baseColor,color);
        loadingBar.setValue(currentValue);
        loadingBar.draw(painter);
    }
public:
    QColor color;
    QColor baseColor;
    int currentValue;
    LoadingProgressBar loadingBar;
};

#endif // LOADINGPROGRESSBARPROPERTY_H
