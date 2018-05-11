#include "publicfunc.h"

QVector<JsonProperty> PublicFunc::vPublicJsonPro;
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
                        jsonPro.vCircleBarProperty.append(tmpCircle);
                    }
                    else if(tmp.compare("CheckBox") == 0)
                    {
                        CheckBoxProperty tmpCheck;
                        tmpCheck.parseJsonData(component);
                        jsonPro.vCheckBoxProperty.append(tmpCheck);
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

bool PublicFunc::writeUIFile(const JsonProperty &jsonPro)
{
    QString sAppPath = QCoreApplication::applicationDirPath();
    QString filePath = sAppPath + "/json/" + jsonPro.fileName;
    if(!confirmFile(filePath)) return false;
    QFile fileW(filePath);
    if(!fileW.open(QIODevice::WriteOnly))
    {
        qDebug() << QString("[MXCUI] open file %1 failed!").arg(filePath);
        return false;
    }
    QJsonDocument doc;
    QJsonObject mainObj;
    QJsonArray array;

    for(int i = 0;i < jsonPro.vCircleBarProperty.count();i++)
    {
        QJsonObject obj;
        CircleProBarProperty circlePro = jsonPro.vCircleBarProperty[i];
        circlePro.saveJsonData(obj);
        array.append(obj);
    }

    mainObj.insert("components",array);
    doc.setObject(mainObj);
    QByteArray byteArray = doc.toJson();
    fileW.write(byteArray);
    return true;
}

bool PublicFunc::confirmFile(const QString fPath)
{
    QString sPath = fPath.left(fPath.lastIndexOf('/'));
    if(QFile::exists(fPath))
        return true;

    QDir dir(sPath);
    if(!dir.exists(sPath))
    {
        if(!dir.mkdir(sPath))
            return false;
    }
    return true;
}
