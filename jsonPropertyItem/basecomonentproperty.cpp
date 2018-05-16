#include "basecomonentproperty.h"

BaseComonentProperty::BaseComonentProperty():x(INVAILD_DATA),y(INVAILD_DATA),width(INVAILD_DATA),height(INVAILD_DATA),layer(INVAILD_DATA),fontSize(INVAILD_DATA),type(""),name(""),
    fontcolor(QColor(255,255,255)),resActive(""),resinActive(""),bigChildItem(NULL),fileName("")
{
    hflagMap.insert("AlignHCenter",Qt::AlignHCenter);
    hflagMap.insert("AlignLeft",Qt::AlignLeft);
    hflagMap.insert("AlignRight",Qt::AlignRight);
    vflagMap.insert("AlignBottom",Qt::AlignBottom);
    vflagMap.insert("AlignTop",Qt::AlignTop);
    vflagMap.insert("AlignVCenter",Qt::AlignVCenter);
    tflagMap.insert("TextSingleLine",Qt::TextSingleLine);
    baseFont.setFamily("Droid Sans Fallback Regular");
    //INVAILD_DATA = std::numeric_limits<int>::max();
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
    if(!type.isEmpty())
    {
        list << "type" << type;
        vStrList.append(list);
        list.clear();
    }
    if(x != INVAILD_DATA)
    {
        list << "x" << QString("%1").arg(x);
        vStrList.append(list);
        list.clear();
    }
    if(y != INVAILD_DATA)
    {
        list << "y" << QString("%1").arg(y);
        vStrList.append(list);
        list.clear();
    }
    if(width != INVAILD_DATA)
    {
        list << "width" << QString("%1").arg(width);
        vStrList.append(list);
        list.clear();
    }
    if(height != INVAILD_DATA)
    {
        list << "height" << QString("%1").arg(height);
        vStrList.append(list);
        list.clear();
    }

//        list << "layer" << QString("%1").arg(layer);
//        vStrList.append(list);
//        list.clear();
    if(fontSize != INVAILD_DATA)
    {
        list << "fontsize" << QString("%1").arg(fontSize);
        vStrList.append(list);
        list.clear();
    }
    if(!resActive.isEmpty())
    {
        list << "res_active" << resActive;
        vStrList.append(list);
        list.clear();
    }
    if(!resinActive.isEmpty())
    {
        list << "res_inactive" << resinActive;
        vStrList.append(list);
        list.clear();
    }
    for(int k = 0;k < vStrList.count();k++)
    {
        new QTreeWidgetItem(bigChildItem,vStrList[k]);
    }

    list << "fontcolor" << "R" << QString("%1").arg(fontcolor.red()) << "G" << QString("%1").arg(fontcolor.green()) << "B" << QString("%1").arg(fontcolor.blue());
    addTreeWidgetStrItem(bigChildItem,list);
}

bool BaseComonentProperty::setData(const SearchType &st)
{
    if(st.fileName.compare(fileName) != 0 || st.structName.compare(name) != 0) return false;
    QString str = st.item.text(0);
    QString value = st.item.text(1);
    QString cName = st.cpName;
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

    //obj.insert("fontcolor",saveColorData(fontcolor));
    QStringList strlist;
    strlist << "fontcolor" << "R" << QString("%1").arg(fontcolor.red()) << "G" << QString("%1").arg(fontcolor.green()) << "B" << QString("%1").arg(fontcolor.blue());
    saveJsonStrItem(obj,strlist);
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

void BaseComonentProperty::addTreeWidgetStrItem(QTreeWidgetItem *childItem,QStringList strlist)
{
    if(strlist.isEmpty()) return;
    QVector<QStringList> vStrList;
    vStrList.clear();

    QTreeWidgetItem *itemlist = new QTreeWidgetItem(childItem,QStringList(strlist.at(0)));

    for(int i = 1;i < strlist.count();i+=2)
    {
        QStringList list;
        list << strlist.at(i) << strlist.at(i+1);
        vStrList.append(list);
    }

    for(int k = 0;k < vStrList.count();k++)
    {
        new QTreeWidgetItem(itemlist,vStrList[k]);
    }
}

void BaseComonentProperty::saveJsonStrItem(QJsonObject &obj,QStringList &strlist)
{
    QJsonObject sobj;
    for(int i = 1;i < strlist.count();i += 2)
    {
        sobj.insert(strlist.at(i),strlist.at(i+1));
    }
    obj.insert(strlist.at(0),sobj);
}

QString BaseComonentProperty::selectDefaultName(QString name)
{
    if (!name.startsWith(":/")) return name;
    return ":/cn/" + name.mid(2);
}
