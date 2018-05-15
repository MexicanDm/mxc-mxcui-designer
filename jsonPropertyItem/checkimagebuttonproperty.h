#ifndef CHECKIMAGEBUTTONPROPERTY_H
#define CHECKIMAGEBUTTONPROPERTY_H
#include "basecomonentproperty.h"

class CheckImageButtonProperty : public BaseComonentProperty{
public:
    CheckImageButtonProperty() : BaseComonentProperty(),text("")
    {}
    bool parseJsonData(QJsonValue component)
    {
        if(!BaseComonentProperty::parseJsonData(component))return false;
        QJsonObject compObj = component.toObject();
        QJsonObject::iterator iter = compObj.find("text");
        if(iter != compObj.end())
        {
            text = iter.value().toString();
        }
        return true;
    }

    bool setData(const SearchType &st)
    {
        if(!BaseComonentProperty::setData(st))return false;
        QString str = st.item.text(0);
        QString value = st.item.text(1);
        QString cName = st.parentName;

        if(str.compare("text") == 0)
        {
            text = value;
        }
        return true;
    }

    void addTreeWidgetItem(QList<QTreeWidgetItem *> layerList)
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
    }

    void draw(QPainter &painter)
    {
        checkImageBtn.setData(x,y,width,height);
        checkImageBtn.setText(text);
        checkImageBtn.draw(painter);
    }

    void saveJsonData(QJsonObject &obj)
    {
        BaseComonentProperty::saveJsonData(obj);
        obj.insert("text",text);
    }

public:
    QString text;
    CheckImageButton checkImageBtn;
};

#endif // CHECKIMAGEBUTTONPROPERTY_H
