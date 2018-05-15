#include "publicfunc.h"

QList<JsonProperty> PublicFunc::vPublicJsonPro;
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
                    }
                    else if(tmp.compare(CHECK_BOX_STR) == 0)
                    {
                        BaseComonentProperty *tmpCheckBox = new CheckBoxProperty();
                        tmpCheckBox->parseJsonData(component);
                        tmpCheckBox->fileName = jsonPro.fileName;
                        jsonPro.vTotalJsonProperty.append(tmpCheckBox);
                    }
                    else if(tmp.compare(IMAGE_BUTTON_STR) == 0)
                    {
                        BaseComonentProperty *tmpImageBtn = new ImageButtonProperty();
                        tmpImageBtn->parseJsonData(component);
                        tmpImageBtn->fileName = jsonPro.fileName;
                        jsonPro.vTotalJsonProperty.append(tmpImageBtn);
                    }
                    else if(tmp.compare(TEXT_LABEL_STR) == 0)
                    {
                        BaseComonentProperty *tmpTextLab = new TextLabelProperty();
                        tmpTextLab->parseJsonData(component);
                        tmpTextLab->fileName = jsonPro.fileName;
                        jsonPro.vTotalJsonProperty.append(tmpTextLab);
                    }
                    else if(tmp.compare(TEXT_EDIT_STR) == 0)
                    {
                        BaseComonentProperty *tmpTextEdit = new TextEditProperty();
                        tmpTextEdit->parseJsonData(component);
                        tmpTextEdit->fileName = jsonPro.fileName;
                        jsonPro.vTotalJsonProperty.append(tmpTextEdit);
                    }
                    else if(tmp.compare(TEXT_EDIT_IMAGE_STA) == 0)
                    {
                        BaseComonentProperty *tmpPro = new TextEditImageProperty();
                        tmpPro->parseJsonData(component);
                        tmpPro->fileName = jsonPro.fileName;
                        jsonPro.vTotalJsonProperty.append(tmpPro);
                    }
                    else if(tmp.compare(CHECK_IMAGE_BUTTON_STA) == 0)
                    {
                        BaseComonentProperty *tmpPro = new CheckImageButtonProperty();
                        tmpPro->parseJsonData(component);
                        tmpPro->fileName = jsonPro.fileName;
                        jsonPro.vTotalJsonProperty.append(tmpPro);
                    }
                    else if(tmp.compare(LED_PROGRESS_BAR_STA) == 0)
                    {
                        BaseComonentProperty *tmpPro = new LedProgressBarProperty();
                        tmpPro->parseJsonData(component);
                        tmpPro->fileName = jsonPro.fileName;
                        jsonPro.vTotalJsonProperty.append(tmpPro);
                    }
                    else if(tmp.compare(LOADING_PROGRESS_BAR_STA) == 0)
                    {
                        BaseComonentProperty *tmpPro = new LoadingProgressBarProperty();
                        tmpPro->parseJsonData(component);
                        tmpPro->fileName = jsonPro.fileName;
                        jsonPro.vTotalJsonProperty.append(tmpPro);
                    }
                    else if(tmp.compare(RECT_PROCESS_BAR_STR) == 0)
                    {
                        BaseComonentProperty *tmpPro = new RectProgressBarProperty();
                        tmpPro->parseJsonData(component);
                        tmpPro->fileName = jsonPro.fileName;
                        jsonPro.vTotalJsonProperty.append(tmpPro);
                    }
                    else if(tmp.compare(ROUND_RECT_PROGRESS_BAR_STA) == 0)
                    {
                        BaseComonentProperty *tmpPro = new RoundRectProgressBarProperty();
                        tmpPro->parseJsonData(component);
                        tmpPro->fileName = jsonPro.fileName;
                        jsonPro.vTotalJsonProperty.append(tmpPro);
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
