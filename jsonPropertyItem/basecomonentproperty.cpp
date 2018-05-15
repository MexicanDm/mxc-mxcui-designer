#include "basecomonentproperty.h"

BaseComonentProperty::BaseComonentProperty():x(0),y(0),width(0),height(0),layer(0),fontSize(0),type(""),name(""),
    fontcolor(QColor(255,255,255)),resActive(""),resinActive(""),bigChildItem(NULL),fileName("")
{
    hflagsMap.insert("AlignHCenter",Qt::AlignHCenter);
    hflagsMap.insert("AlignLeft",Qt::AlignLeft);
    hflagsMap.insert("AlignRight",Qt::AlignRight);
    vflagsMap.insert("AlignBottom",Qt::AlignBottom);
    vflagsMap.insert("AlignTop",Qt::AlignTop);
    vflagsMap.insert("AlignVCenter",Qt::AlignVCenter);
    baseFont.setFamily("Droid Sans Fallback Regular");
}
bool BaseComonentProperty::parseJsonData(QJsonValue component)
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
        baseFont.setPointSize(fontSize);
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
        fontcolor = parseColor(iter);
    }
    return true;
}

void BaseComonentProperty::addTreeWidgetItem(QList<QTreeWidgetItem *>layerList)
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

//        list << "layer" << QString("%1").arg(layer);
//        vStrList.append(list);
//        list.clear();

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
    QTreeWidgetItem *itemfontColor = new QTreeWidgetItem(bigChildItem,list);
    addColorItem(itemfontColor,fontcolor);
    //delete bigChildItem;
}

bool BaseComonentProperty::setData(const SearchType &st)
{
    if(st.fileName.compare(fileName) != 0 || st.structName.compare(name) != 0) return false;
    QString str = st.item.text(0);
    QString value = st.item.text(1);
    QString cName = st.parentName;
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
        baseFont.setPointSize(fontSize);
    }
    else if(cName.compare("fontcolor") == 0)
    {
        setColorData(str,fontcolor,value);
    }
    else if(str.compare("res_active") == 0)
    {
        resActive = value;
    }
    else if(str.compare("res_inactive") == 0)
    {
        resinActive = value;
    }
    return true;
}

void BaseComonentProperty::saveJsonData(QJsonObject &obj)
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

    obj.insert("fontcolor",saveColorData(fontcolor));

    //array.append(obj);
}

void BaseComonentProperty::initData()
{

}

void BaseComonentProperty::draw(QPainter &painter)
{
    Q_UNUSED(painter);
}

QColor BaseComonentProperty::parseColor(QJsonObject::iterator iter)
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
    return QColor(r,g,b);
}

void BaseComonentProperty::addColorItem(QTreeWidgetItem *itembgColor,QColor color)
{
    QVector<QStringList> vStrList;
    QStringList list;
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
        new QTreeWidgetItem(itembgColor,vStrList[k]);
    }
}

QJsonObject BaseComonentProperty::saveColorData(QColor color)
{
    QJsonObject bgColorObj;
    bgColorObj.insert("red",color.red());
    bgColorObj.insert("green",color.green());
    bgColorObj.insert("blue",color.blue());
    return bgColorObj;
}

void BaseComonentProperty::setColorData(const QString &str,QColor &color,const QString &value)
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
