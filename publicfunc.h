#ifndef PUBLICFUNC_H
#define PUBLICFUNC_H

#include <QWidget>
#include <QFile>
#include <QJsonParseError>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QDebug>
#include <QTreeWidget>
#include <QTreeWidgetItem>

class BaseComonentProperty{
public:
    BaseComonentProperty():x(0),y(0),width(0),height(0),layer(0),fontSize(0),type(""),name(""),
        fontcolor(QColor(255,255,255)),resActive(""),resinActive(""),bigChildItem(NULL)
    {}
    virtual bool parseJsonData(QJsonValue component)
    {
        QJsonObject compObj = component.toObject();
        QJsonObject::iterator iter = compObj.find("name");
        if(iter != compObj.end())
        {
            name = iter.value().toString();
        }
        iter = compObj.find("x");
        if(iter != compObj.end())
        {
            x = iter.value().toInt();
        }
        iter = compObj.find("y");
        if(iter != compObj.end())
        {
            y = iter.value().toInt();
        }
        iter = compObj.find("layer");
        if(iter != compObj.end())
        {
            layer = iter.value().toInt();
        }
        iter = compObj.find("width");
        if(iter != compObj.end())
        {
            width = iter.value().toInt();
        }
        iter = compObj.find("height");
        if(iter != compObj.end())
        {
            height = iter.value().toInt();
        }
        iter = compObj.find("fontsize");
        if(iter != compObj.end())
        {
            fontSize = iter.value().toInt();
        }
        iter = compObj.find("res_active");
        if(iter != compObj.end())
        {
            resActive = iter.value().toString();
        }
        iter = compObj.find("res_inactive");
        if(iter != compObj.end())
        {
            resinActive = iter.value().toString();
        }
        iter = compObj.find("fontcolor");
        if(iter != compObj.end())
        {
            QJsonObject colorObj = iter.value().toObject();
            int r = 255, g = 255, b = 255;
            iter = colorObj.find("red");
            if(iter != colorObj.end())
            {
                r = iter.value().toInt();
            }
            iter = colorObj.find("green");
            if(iter != colorObj.end())
            {
                g = iter.value().toInt();
            }
            iter = colorObj.find("blue");
            if(iter != colorObj.end())
            {
                b = iter.value().toInt();
            }
            fontcolor = QColor(r,g,b);
        }
        return true;
    }
    virtual void addTreeWidgetItem(QTreeWidgetItem *fatherItem)
    {
        bigChildItem = new QTreeWidgetItem(fatherItem,QStringList(QString(name)));
        QVector<QStringList> vStrList;
        QStringList list;
        list << "x" << QString("%1").arg(x);
        vStrList.append(list);
        list.clear();

        list << "y" << QString("%1").arg(y);
        vStrList.append(list);
        list.clear();

        list << "width" << QString("%1").arg(width);
        vStrList.append(list);
        list.clear();

        list << "height" << QString("%1").arg(height);
        vStrList.append(list);
        list.clear();

        list << "layer" << QString("%1").arg(layer);
        vStrList.append(list);
        list.clear();

        list << "fontsize" << QString("%1").arg(fontSize);
        vStrList.append(list);
        list.clear();

        list << "res_active" << resActive;
        vStrList.append(list);
        list.clear();

        list << "res_inactive" << resinActive;
        vStrList.append(list);
        list.clear();

        for(int k = 0;k < vStrList.count();k++)
        {
            new QTreeWidgetItem(bigChildItem,vStrList[k]);
        }

        list << "fontcolor";
        QTreeWidgetItem *itemColor = new QTreeWidgetItem(bigChildItem,list);
        list.clear();
        vStrList.clear();
        list << "R" << QString("%1").arg(fontcolor.red());
        vStrList.append(list);
        list.clear();

        list << "G" << QString("%1").arg(fontcolor.green());
        vStrList.append(list);
        list.clear();

        list << "B" << QString("%1").arg(fontcolor.blue());
        vStrList.append(list);
        list.clear();
        for(int k = 0;k < vStrList.count();k++)
        {
            new QTreeWidgetItem(itemColor,vStrList[k]);
        }
    }

public:
    int x;
    int y;
    int width;
    int height;
    int layer;
    int fontSize;
    QString type;
    QString name;
    QColor fontcolor;
    QString resActive;
    QString resinActive;
    QTreeWidgetItem *bigChildItem;
};

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
            QJsonObject colorObj = iter.value().toObject();
            int r = 255, g = 255, b = 255;
            iter = colorObj.find("red");
            if(iter != colorObj.end())
            {
                r = iter.value().toInt();
            }
            iter = colorObj.find("green");
            if(iter != colorObj.end())
            {
                g = iter.value().toInt();
            }
            iter = colorObj.find("blue");
            if(iter != colorObj.end())
            {
                b = iter.value().toInt();
            }
            color = QColor(r,g,b);
        }
        iter = compObj.find("baseColor");
        if(iter != compObj.end())
        {
            QJsonObject colorObj = iter.value().toObject();
            int r = 255, g = 255, b = 255;
            iter = colorObj.find("red");
            if(iter != colorObj.end())
            {
                r = iter.value().toInt();
            }
            iter = colorObj.find("green");
            if(iter != colorObj.end())
            {
                g = iter.value().toInt();
            }
            iter = colorObj.find("blue");
            if(iter != colorObj.end())
            {
                b = iter.value().toInt();
            }
            baseColor = QColor(r,g,b);
        }
        return true;
    }
    void addTreeWidgetItem(QTreeWidgetItem *fatherItem)
    {
        BaseComonentProperty::addTreeWidgetItem(fatherItem);
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
        list.clear();
        vStrList.clear();
        list << "R" << QString("%1").arg(color.red());
        vStrList.append(list);
        list.clear();

        list << "G" << QString("%1").arg(color.green());
        vStrList.append(list);
        list.clear();

        list << "B" << QString("%1").arg(color.blue());
        vStrList.append(list);
        list.clear();
        for(int k = 0;k < vStrList.count();k++)
        {
            new QTreeWidgetItem(itemColor,vStrList[k]);
        }

        list << "baseColor";
        QTreeWidgetItem *baseColorItem = new QTreeWidgetItem(bigChildItem,list);
        list.clear();
        vStrList.clear();
        list << "R" << QString("%1").arg(baseColor.red());
        vStrList.append(list);
        list.clear();

        list << "G" << QString("%1").arg(baseColor.green());
        vStrList.append(list);
        list.clear();

        list << "B" << QString("%1").arg(baseColor.blue());
        vStrList.append(list);
        list.clear();
        for(int k = 0;k < vStrList.count();k++)
        {
            new QTreeWidgetItem(baseColorItem,vStrList[k]);
        }
    }

public:
    QColor color;
    QColor baseColor;
    int penWidth;
    int minValue;
    int maxValue;
    int currentValue;
};

class CheckBoxProperty : public BaseComonentProperty{
public:
    CheckBoxProperty() : BaseComonentProperty()
    {}
    bool parseJsonData(QJsonValue component)
    {
        BaseComonentProperty::parseJsonData(component);
        return true;
    }

public:

};

class JsonProperty{
public:
    QString fileName;
    QVector<CircleProBarProperty> vCircleProBar;
    QVector<CheckBoxProperty> vCheckBox;
};

class PublicFunc : public QWidget
{
    Q_OBJECT
public:
    explicit PublicFunc(QWidget *parent = 0);
    static bool readUIFile(QString path,JsonProperty &vJsonPro);
signals:

public slots:
};

#endif // PUBLICFUNC_H
