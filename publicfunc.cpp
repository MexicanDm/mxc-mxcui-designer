#include "publicfunc.h"

QList<JsonProperty> PublicFunc::vPublicJsonPro;
int PublicFunc::proNum = 0;
PublicFunc::PublicFunc(QWidget *parent) : QWidget(parent)
{

}
/**
 * @brief PublicFunc::readUIFile 读取Json
 * @param path
 * @param jsonPro
 * @return
 */
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
                    if(tmp.compare(CIRCLE_PROCESS_BAR_STR) == 0)
                    {
                        BaseComonentProperty *tmpCircle = new CircleProBarProperty();
                         tmpCircle->parseJsonData(component);
                         tmpCircle->fileName = jsonPro.fileName;
                        jsonPro.vTotalJsonProperty.append(tmpCircle);
                        proNum++;
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

    for(int i = 0;i < jsonPro.vTotalJsonProperty.count();i++)
    {
        QJsonObject obj;
        BaseComonentProperty *pro = jsonPro.vTotalJsonProperty[i];
        pro->saveJsonData(obj);
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
