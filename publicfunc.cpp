#include "publicfunc.h"


PublicFunc::PublicFunc(QWidget *parent) : QWidget(parent)
{

}
bool PublicFunc::readUIFile(QString path, JsonProperty &jsonPro)
{
    QFile fileR(path);
    if(!fileR.open(QIODevice::ReadOnly))
    {
        qDebug() << QString("[MXCUI] open file %1 failed!").arg(path);
        return false;
    }
    jsonPro.fileName = path.mid(path.lastIndexOf("/") + 1);
    QByteArray data = fileR.readAll();
    fileR.close();
    QJsonParseError error;
    QJsonDocument doc = QJsonDocument::fromJson(data, &error);
    if (error.error == QJsonParseError::NoError)
    {
        QJsonObject obj = doc.object();
        QJsonObject::iterator iter = obj.find("components");
        if(iter != obj.end())
        {
            QJsonArray componentsarray = iter.value().toArray();
            foreach (QJsonValue component, componentsarray) {
                QJsonObject compObj = component.toObject();
                iter = compObj.find("type");
                if(iter != compObj.end())
                {
                    QString tmp = iter.value().toString();
                    if(tmp.compare(CIRCLE_PROCESS_BAR) == 0)
                    {
                        CircleProBarProperty tmpCircle;
                        tmpCircle.parseJsonData(component);
                        jsonPro.vCircleProBar.append(tmpCircle);
                    }
                    else if(tmp.compare("CheckBox") == 0)
                    {
                        CheckBoxProperty tmpCheck;
                        tmpCheck.parseJsonData(component);
                        jsonPro.vCheckBox.append(tmpCheck);
                    }
                }
            }
        }
    }
    else
    {
        qDebug() << QString("[MXCUI] file %1 json format error %2!").arg(path).arg(error.errorString());
        return false;
    }
    return true;
}
