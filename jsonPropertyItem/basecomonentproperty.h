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
#include "realline.h"
#include "targettemptext.h"
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
#include <limits>
#include <QCheckBox>

#define INVAILD_DATA (std::numeric_limits<int>::max())
#define CIRCLE_PROCESS_BAR_STR "CircleProgressBar"
#define CHECK_BOX_STR "CheckBox"
#define IMAGE_BUTTON_STR "ImageButton"
#define ALPHABET_KEYBOARD_STR "AlphabetKeyboard"
#define TEXT_LABEL_STR "TextLabel"
#define TEXT_EDIT_STR "TextEdit"
#define TEXT_EDIT_IMAGE_STA "TextEditImage"
#define CHECK_IMAGE_BUTTON_STA "CheckImageButton"
#define COMBO_ITEM_STA "ComboItem"
#define LED_PROGRESS_BAR_STA "LedProgressBar"
#define LOADING_PROGRESS_BAR_STA "LoadingProgressBar"
#define RECT_PROCESS_BAR_STR "RectProgressBar"
#define ROUND_RECT_PROGRESS_BAR_STA "RoundRectProgressBar"
#define NUM_KEYBOARD_STR "NumberKeyboard"
#define WIFI_CUSTOM_BUTTON_STR "WifiCustomButton"
#define WIFI_ALPHABET_KEYBOAED_STR "WifiAlphabetKeyboard"
#define INFO_CONFIRM_PANEL_STR "InfoConfirmPanel"
#define REAL_LINE_STR "RealLine"
#define TARGET_TEMP_TEXT_STR "TargetTempText"
#define LIST_BOX_STR "ListBox"
#define LIST_ITEM_STR "ListItem"

typedef struct SearchType_{
    QString fileName; //wen jian
    QString structName; //bian liang ming
    QString structType;// bian liang lei xing
    QString cpName; //color alignment
    QString changeStr;
    QString changeValue;
}SearchType;

typedef struct AlignmentFlag_{
    QString vflag;
    QString hflag;
    QString tflag;
}AlignmentFlag;

typedef struct {
    QColor activeColor;
    QColor inactiveColor;
}TextSwitchColor;

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
    void setColorData(const QString &str,QColor &color,const QString &value);
    void addTreeWidgetHaveChildStrItem(QTreeWidgetItem *childItem, QStringList strlist);
    void addTreeWidgetStrListItem(QTreeWidgetItem *childItem, QStringList strlist,bool b);
    void saveJsonStrItem(QJsonObject &obj, QStringList &strlist);
    QString selectDefaultName(QString name);

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
    QMap<QString,int> vflagMap;
    QMap<QString,int> hflagMap;
    QMap<QString,int> tflagMap;
    QFont baseFont;
    //int maxInvalidData;
};

#endif // BASECOMONENTPROPERTY1_H
