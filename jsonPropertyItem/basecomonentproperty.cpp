#include "basecomonentproperty.h"


BaseComonentProperty::BaseComonentProperty():x(0),y(0),width(0),height(0),layer(0),fontSize(10),type(""),name(""),
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
    baseFont.setPointSize(fontSize);
    checkStaMap.insert("x",true);
    checkStaMap.insert("y",true);
    checkStaMap.insert("width",true);
    checkStaMap.insert("height",true);
    checkStaMap.insert("layer",true);
    checkStaMap.insert("fontsize",true);
    checkStaMap.insert("res_active",true);
    checkStaMap.insert("res_inactive",true);
    checkStaMap.insert("fontcolor",true);
    checkStaMap.insert("name",true);

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
        list << "x" << QString("%1").arg(x);
        list << "y" << QString("%1").arg(y);
        list << "width" << QString("%1").arg(width);
        list << "height" << QString("%1").arg(height);
//        list << "layer" << QString("%1").arg(layer);
        list << "fontsize" << QString("%1").arg(fontSize) ;
        list << "res_active" << resActive;
        list << "res_inactive" << resinActive;
    addTreeWidgetStrListItem(bigChildItem,list,true);
    list.clear();
    list << "fontcolor" << "R" << QString("%1").arg(fontcolor.red()) << "G" << QString("%1").arg(fontcolor.green()) << "B" << QString("%1").arg(fontcolor.blue());
    addTreeWidgetHaveChildStrItem(bigChildItem,list);
}

 bool BaseComonentProperty::setChechedSta(const SearchType &st)
 {
     if(st.fileName.compare(fileName) != 0 || st.structName.compare(name) != 0) return false;
     QString str = st.item->text(0);
    bool b = st.item->checkState(0);
     QString cName = st.cpName;

     checkStaMap[str] = b;
     checkStaMap[cName] = b;
     return true;
 }

bool BaseComonentProperty::setData(const SearchType &st)
{
    if(st.fileName.compare(fileName) != 0 || st.structName.compare(name) != 0) return false;
    QString str = st.item->text(0);
    QString value = st.item->text(1);
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
    if(checkStaMap.value("x"))
        obj.insert("x",x);
    if(checkStaMap.value("y"))
        obj.insert("y",y);

    if(checkStaMap.value("width"))
        obj.insert("width",width);

    if(checkStaMap.value("height"))
        obj.insert("height",height);

    if(checkStaMap.value("layer"))
        obj.insert("layer",layer);

    if(checkStaMap.value("fontsize"))
        obj.insert("fontsize",fontSize);

    if(checkStaMap.value("type"))
        obj.insert("type",type);

    if(checkStaMap.value("name"))
        obj.insert("name",name);

    if(checkStaMap.value("res_active"))
        obj.insert("res_active",resActive);

    if(checkStaMap.value("res_inactive"))
        obj.insert("res_inactive",resinActive);

    if(checkStaMap.value("fontcolor"))
    {
        QStringList strlist;
        strlist << "fontcolor" << "R" << QString("%1").arg(fontcolor.red()) << "G" << QString("%1").arg(fontcolor.green()) << "B" << QString("%1").arg(fontcolor.blue());
        saveJsonStrItem(obj,strlist);
    }
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

void BaseComonentProperty::addTreeWidgetStrListItem(QTreeWidgetItem *childItem, QStringList strlist, bool b)
{
    if(strlist.isEmpty()) return;
    for(int i = 0;i < strlist.count();i += 2)
    {
        QTreeWidgetItem *item = new QTreeWidgetItem();
        childItem->addChild(item);
        item->setText(0,strlist[i]);
        item->setText(1,strlist[i+1]);
        if(b)
            item->setCheckState(0,Qt::Checked);
        else
             item->setCheckState(0,Qt::Unchecked);
    }
}

void BaseComonentProperty::addTreeWidgetHaveChildStrItem(QTreeWidgetItem *childItem,QStringList strlist)
{
    if(strlist.isEmpty()) return;

    QTreeWidgetItem *itemlist = new QTreeWidgetItem();
    childItem->addChild(itemlist);
    itemlist->setText(0,strlist.at(0));
    itemlist->setCheckState(1,Qt::Checked);
    QStringList childList = strlist.mid(1,strlist.length());
    if(strlist.at(0).compare("fontcolor") == 0)
        addTreeWidgetStrListItem(itemlist,childList,true);
    else
        addTreeWidgetStrListItem(itemlist,childList,false);
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
