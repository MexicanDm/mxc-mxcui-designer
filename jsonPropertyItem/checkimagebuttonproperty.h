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
        QString str = st.changeStr;
        QString value = st.changeValue;

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
        QStringList list;

        list << "text" << text;
        addTreeWidgetStrListItem(bigChildItem,list,false);
        list.clear();

    }

    void draw(QPainter &painter)
    {
        checkImageBtn.setData(x,y,width,height);
        checkImageBtn.setText(text);
        checkImageBtn.setCheckOffImage(selectDefaultName(resinActive),selectDefaultName(resActive));
        checkImageBtn.setCheckOnImage(selectDefaultName(resinActive),selectDefaultName(resActive));
        checkImageBtn.setChecked(true);
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
