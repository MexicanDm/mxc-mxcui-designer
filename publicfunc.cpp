#include "publicfunc.h"

QVector<JsonProperty> PublicFunc::vPublicJsonPro;
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
                        CircleProBarProperty tmpCircle;
                        tmpCircle.parseJsonData(component);
                        jsonPro.vCircleBarProperty.append(tmpCircle);
                        jsonPro.vTotalJsonPro.append(jsonPro.vCircleBarProperty.last());
                    }
                    else if(tmp.compare(CHECK_BOX_STR) == 0)
                    {
                        CheckBoxProperty tmpCheck;
                        tmpCheck.parseJsonData(component);
                        jsonPro.vCheckBoxProperty.append(tmpCheck);
                        jsonPro.vTotalJsonPro.append(jsonPro.vCheckBoxProperty.last());
                    }
                    else if(tmp.compare(IMAGE_BUTTON_STR) == 0)
                    {
                        ImageButtonProperty imageBtnPro;
                        imageBtnPro.parseJsonData(component);
                        jsonPro.vImageBtnProperty.append(imageBtnPro);
                        jsonPro.vTotalJsonPro.append(jsonPro.vImageBtnProperty.last());
                    }
                    else if(tmp.compare(ALPHABET_KEYBOARD_STR) == 0)
                    {
                        AlphabetKeyboardProperty alKeyboard;
                        alKeyboard.parseJsonData(component);
                        jsonPro.vAlKeyboardProperty.append(alKeyboard);
                        jsonPro.vTotalJsonPro.append(jsonPro.vAlKeyboardProperty.last());
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

    for(int i = 0;i < jsonPro.vTotalJsonPro.count();i++)
    {
        QJsonObject obj;
        BaseComonentProperty pro = jsonPro.vTotalJsonPro[i];
        pro.saveJsonData(obj);
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
