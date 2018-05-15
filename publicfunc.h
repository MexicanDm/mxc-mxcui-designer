#ifndef PUBLICFUNC_H
#define PUBLICFUNC_H

#include "jsonPropertyItem/basecomonentproperty.h"
#include "jsonPropertyItem/alphabetkeyboardproperty.h"
#include "jsonPropertyItem/checkboxproperty.h"
#include "jsonPropertyItem/circleprobarproperty.h"
#include "jsonPropertyItem/imagebuttonproperty.h"
#include "jsonPropertyItem/textlabelproperty.h"
#include "jsonPropertyItem/texteditproperty.h"

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
