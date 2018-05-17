#ifndef PUBLICFUNC_H
#define PUBLICFUNC_H

#include "jsonPropertyItem/basecomonentproperty.h"
#include "jsonPropertyItem/alphabetkeyboardproperty.h"
#include "jsonPropertyItem/checkboxproperty.h"
#include "jsonPropertyItem/circleprobarproperty.h"
#include "jsonPropertyItem/imagebuttonproperty.h"
#include "jsonPropertyItem/textlabelproperty.h"
#include "jsonPropertyItem/texteditproperty.h"
#include "jsonPropertyItem/texteditimageproperty.h"
#include "jsonPropertyItem/checkimagebuttonproperty.h"
#include "jsonPropertyItem/comboitemproperty.h"
#include "jsonPropertyItem/ledprogressbarproperty.h"
#include "jsonPropertyItem/loadingprogressbarproperty.h"
#include "jsonPropertyItem/rectprogressbarproperty.h"
#include "jsonPropertyItem/roundrectprogressbarproperty.h"
#include "jsonPropertyItem/numberkeyboardproperty.h"
#include "jsonPropertyItem/wificustombuttonproperty.h"
#include "jsonPropertyItem/wifialphabetkeyboardproperty.h"
#include "jsonPropertyItem/infoconfirmpanelproperty.h"
#include "jsonPropertyItem/reallineproperty.h"
#include "jsonPropertyItem/targettemptextproperty.h"
#include "jsonPropertyItem/listitemproperty.h"
#include "jsonPropertyItem/listboxproperty.h"

class JsonProperty{
public:
    QString fileName;
    QList<BaseComonentProperty*> vTotalJsonProperty;

};

class PublicFunc : public QWidget
{
    Q_OBJECT
public:
    explicit PublicFunc(QWidget *parent = 0);
    static bool readUIFile(QString path,JsonProperty &vJsonPro);
    static bool writeUIFile(const JsonProperty &jsonPro);
    static QList<JsonProperty> vPublicJsonPro;
    static bool confirmFile(const QString fPath);
signals:

public slots:
};

#endif // PUBLICFUNC_H
