#ifndef PUBLICFUNC_H
#define PUBLICFUNC_H

#include "../mxc-mxcui/MXCUI/ui/circleprogressbar.h"
#include "../mxc-mxcui/MXCUI/ui/imagelabel.h"
#include "../mxc-mxcui/MXCUI/ui/roundrectprogressbar.h"
#include "../mxc-mxcui/MXCUI/ui/textlabel.h"
#include "../mxc-mxcui/MXCUI/ui/imagebutton.h"
#include "../mxc-mxcui/MXCUI/ui/rectprogressbar.h"
#include "../mxc-mxcui/MXCUI/ui/listbox.h"
#include "../mxc-mxcui/MXCUI/ui/combobox.h"
#include "../mxc-mxcui/MXCUI/ui/checkbox.h"
#include "../mxc-mxcui/MXCUI/ui/textedit.h"
#include "../mxc-mxcui/MXCUI/ui/numberkeyboard.h"
#include "../mxc-mxcui/MXCUI/ui/ledprogressbar.h"
#include "../mxc-mxcui/MXCUI/ui/loadinganimator.h"
#include "../mxc-mxcui/MXCUI/ui/texteditimage.h"
#include "../mxc-mxcui/MXCUI/ui/alphabetkeyboard.h"
#include "../mxc-mxcui/MXCUI/ui/checkimagebutton.h"
#include "../mxc-mxcui/MXCUI/ui/messageboxpanel.h"
#include "../mxc-mxcui/MXCUI/ui/loadingprogressbar.h"
#include "../mxc-mxcui/MXCUI/ui/infoconfirmpanel.h"
#include "../mxc-mxcui/MXCUI/ui/wificustombutton.h"
#include "../mxc-mxcui/MXCUI/ui/wifialphabetkeyboard.h"
#include "../mxc-mxcui/MXCUI/ui/uicomponent.h"
#include <QWidget>
#include <QFile>
#include <QJsonParseError>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QDebug>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QCoreApplication>
#include <QDir>

#define CIRCLE_PROCESS_BAR_STR "CircleProgressBar"
#define CHECK_BOX_STR "CheckBox"
#define IMAGE_BUTTON_STR "ImageButton"
#define ALPHABET_KEYBOARD_STR "AlphabetKeyboard"

typedef struct{
    QString fileName;
    QString structName;
    QString structType;
    QString colorName;
    QTreeWidgetItem item;
}SearchType;

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
        iter = compObj.find("type");
        if(iter != compObj.end())
        {
            type = iter.value().toString();
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

    virtual void addTreeWidgetItem(QList<QTreeWidgetItem *>layerList)
    {
        QVector<QStringList> vStrList;
        QStringList list;

        if(layerList.count() > 0 && layer < layerList.count())
        {
            bigChildItem = new QTreeWidgetItem(layerList.at(layer),QStringList(QString(name)));
        }
        else
        {
            return;
        }

        list << "type" << type;
        vStrList.append(list);
        list.clear();

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

        list << "fontColor";
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
        //delete bigChildItem;
    }

    virtual void setData(const SearchType &st)
    {
        QString str = st.item.text(0);
        QString value = st.item.text(1);
        QString cName = st.colorName;
        if(str.compare("x") == 0)
        {
            x = value.toInt();
        }
        else if(str.compare("y") == 0)
        {
            y = value.toInt();
        }
        else if(str.compare("width") == 0)
        {
            width = value.toInt();
        }
        else if(str.compare("height") == 0)
        {
            height = value.toInt();
        }
        else if(str.compare("layer") == 0)
        {
            layer = value.toInt();
        }
        else if(str.compare("fontsize") == 0)
        {
            fontSize = value.toInt();
        }
        else if(cName.compare("fontcolor") == 0)
        {
            if(str.compare("R") == 0)
            {
                fontcolor.setRed(value.toInt());
            }
            else if(str.compare("G") == 0)
            {
                fontcolor.setGreen(value.toInt());
            }
            else if(str.compare("B") == 0)
            {
                fontcolor.setBlue(value.toInt());
            }
        }
        else if(str.compare("res_active") == 0)
        {
            resActive = value;
        }
        else if(str.compare("res_inactive") == 0)
        {
            resinActive = value;
        }
    }

    virtual void saveJsonData(QJsonObject &obj)
    {
        obj.insert("x",x);
        obj.insert("y",y);
        obj.insert("width",width);
        obj.insert("height",height);
        obj.insert("layer",layer);
        obj.insert("fontsize",fontSize);
        obj.insert("type",type);
        obj.insert("name",name);
        obj.insert("res_active",resActive);
        obj.insert("res_inactive",resinActive);

        QJsonObject fontColorObj;
        fontColorObj.insert("red",fontcolor.red());
        fontColorObj.insert("green",fontcolor.green());
        fontColorObj.insert("blue",fontcolor.blue());
        obj.insert("fontcolor",fontColorObj);

        //array.append(obj);
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

    void setData(const SearchType &st)
    {
        BaseComonentProperty::setData(st);
        QString str = st.item.text(0);
        QString value = st.item.text(1);
        QString cName = st.colorName;
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
            if(str.compare("R") == 0)
            {
                color.setRed(value.toInt());
            }
            else if(str.compare("G") == 0)
            {
                color.setGreen(value.toInt());
            }
            else if(str.compare("B") == 0)
            {
                color.setBlue(value.toInt());
            }
        }
        else if(cName.compare("baseColor") == 0)
        {
            if(str.compare("R") == 0)
            {
                baseColor.setRed(value.toInt());
            }
            else if(str.compare("G") == 0)
            {
                baseColor.setGreen(value.toInt());
            }
            else if(str.compare("B") == 0)
            {
                baseColor.setBlue(value.toInt());
            }
        }

    }

    void saveJsonData(QJsonObject &obj)
    {
        BaseComonentProperty::saveJsonData(obj);
        //QJsonObject obj;
        obj.insert("penWidth",penWidth);
        obj.insert("minValue",minValue);
        obj.insert("maxValue",maxValue);
        obj.insert("currentValue",currentValue);

        QJsonObject colorObj;
        colorObj.insert("red",color.red());
        colorObj.insert("green",color.green());
        colorObj.insert("blue",color.blue());
        obj.insert("color",colorObj);

        QJsonObject baseColorObj;
        baseColorObj.insert("red",baseColor.red());
        baseColorObj.insert("green",baseColor.green());
        baseColorObj.insert("blue",baseColor.blue());
        obj.insert("baseColor",baseColorObj);

        //array.append(obj);
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
    CheckBox vCheckBox;

};
/**
 * @brief The ImageButtonProperty class ImageButton
 */
class ImageButtonProperty : public BaseComonentProperty{
public:
    ImageButtonProperty() : BaseComonentProperty(),color(QColor(255,255,255))
    {}
    bool parseJsonData(QJsonValue component)
    {
        bool parentB = BaseComonentProperty::parseJsonData(component);
        QJsonObject compObj = component.toObject();
        QJsonObject::iterator iter = compObj.find("color");
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
        if(parentB)
            return true;
        else
            return false;
    }

    void addTreeWidgetItem(QList<QTreeWidgetItem *>layerList)
    {
        BaseComonentProperty::addTreeWidgetItem(layerList);
        if(bigChildItem == NULL) return ;
        QVector<QStringList> vStrList;
        QStringList list;

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
    }

    void setData(const SearchType &st)
    {
        BaseComonentProperty::setData(st);
        QString str = st.item.text(0);
        QString value = st.item.text(1);
        QString cName = st.colorName;
        if(cName.compare("color") == 0)
        {
            if(str.compare("R") == 0)
            {
                color.setRed(value.toInt());
            }
            else if(str.compare("G") == 0)
            {
                color.setGreen(value.toInt());
            }
            else if(str.compare("B") == 0)
            {
                color.setBlue(value.toInt());
            }
        }
    }
public:
    QColor color;
    ImageButton imageBtn;
};

class AlphabetKeyboardProperty : public BaseComonentProperty{
public:
    AlphabetKeyboardProperty() : BaseComonentProperty()
    {}

public:
    AlphabetKeyboard alKeyboard;


};

class JsonProperty{
public:
    QString fileName;
    QVector<CircleProBarProperty> vCircleBarProperty;
    QVector<CheckBoxProperty> vCheckBoxProperty;
    QVector<ImageButtonProperty> vImageBtnProperty;
    QVector<AlphabetKeyboardProperty> vAlKeyboardProperty;

    QVector<BaseComonentProperty> vTotalJsonPro;

};

class PublicFunc : public QWidget
{
    Q_OBJECT
public:
    explicit PublicFunc(QWidget *parent = 0);
    static bool readUIFile(QString path,JsonProperty &vJsonPro);
    static bool writeUIFile(const JsonProperty &jsonPro);
    static QVector<JsonProperty> vPublicJsonPro;
    static bool confirmFile(const QString fPath);
signals:

public slots:
};

#endif // PUBLICFUNC_H
