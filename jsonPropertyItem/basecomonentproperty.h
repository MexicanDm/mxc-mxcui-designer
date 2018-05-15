#ifndef BASECOMONENTPROPERTY1_H
#define BASECOMONENTPROPERTY1_H

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
#define TEXT_LABEL_STR "TextLabel"
#define TEXT_EDIT_STR "TextEdit"

typedef struct SearchType_{
    QString fileName;
    QString structName;
    QString structType;
    QString parentName;
    QTreeWidgetItem item;
}SearchType;

class BaseComonentProperty{
public:
    BaseComonentProperty();
    virtual bool parseJsonData(QJsonValue component);
    virtual void addTreeWidgetItem(QList<QTreeWidgetItem *>layerList);
    virtual bool setData(const SearchType &st);
    virtual void saveJsonData(QJsonObject &obj);
    virtual void initData();
    virtual void draw(QPainter &painter);
    QColor parseColor(QJsonObject::iterator iter);
    void addColorItem(QTreeWidgetItem *itembgColor,QColor color);
    QJsonObject saveColorData(QColor color);
    void setColorData(const QString &str,QColor &color,const QString &value);
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
    QString fileName;
    QMap<QString,int> vflagsMap;
    QMap<QString,int> hflagsMap;
    QFont baseFont;
};

#endif // BASECOMONENTPROPERTY1_H
