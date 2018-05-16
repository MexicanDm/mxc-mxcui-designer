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
                    BaseComonentProperty *tmpPro = NULL;
                    if(tmp.compare(CIRCLE_PROCESS_BAR_STR) == 0)
                    {
                        tmpPro = new CircleProBarProperty();
                    }
                    else if(tmp.compare(CHECK_BOX_STR) == 0)
                    {
                        tmpPro = new CheckBoxProperty();
                    }
                    else if(tmp.compare(IMAGE_BUTTON_STR) == 0)
                    {
                        tmpPro = new ImageButtonProperty();
                    }
                    else if(tmp.compare(TEXT_LABEL_STR) == 0)
                    {
                        tmpPro = new TextLabelProperty();
                    }
                    else if(tmp.compare(TEXT_EDIT_STR) == 0)
                    {
                        tmpPro = new TextEditProperty();
                    }
                    else if(tmp.compare(TEXT_EDIT_IMAGE_STA) == 0)
                    {
                        tmpPro = new TextEditImageProperty();
                    }
                    else if(tmp.compare(CHECK_IMAGE_BUTTON_STA) == 0)
                    {
                        tmpPro = new CheckImageButtonProperty();
                    }
                    else if(tmp.compare(LED_PROGRESS_BAR_STA) == 0)
                    {
                        tmpPro = new LedProgressBarProperty();
                    }
                    else if(tmp.compare(LOADING_PROGRESS_BAR_STA) == 0)
                    {
                        tmpPro = new LoadingProgressBarProperty();
                    }
                    else if(tmp.compare(RECT_PROCESS_BAR_STR) == 0)
                    {
                        tmpPro = new RectProgressBarProperty();
                    }
                    else if(tmp.compare(ROUND_RECT_PROGRESS_BAR_STA) == 0)
                    {
                        tmpPro = new RoundRectProgressBarProperty();
                    }
                    else if(tmp.compare(ALPHABET_KEYBOARD_STR) == 0)
                    {
                        tmpPro = new AlphabetKeyboardProperty();
                    }
                    else if(tmp.compare(COMBO_ITEM_STA) == 0)
                    {
                        tmpPro = new ComboItemProperty();
                    }
                    else if(tmp.compare(NUM_KEYBOARD_STR) == 0)
                    {
                        tmpPro = new NumberKeyboardProperty();
                    }
                    else if(tmp.compare(WIFI_CUSTOM_BUTTON_STR) == 0)
                    {
                        tmpPro = new WifiCustomButtonProperty();
                    }
                    else if(tmp.compare(WIFI_ALPHABET_KEYBOAED_STR) == 0)
                    {
                        tmpPro = new WifiAlphabetKeyboardProperty();
                    }
                    else if(tmp.compare(INFO_CONFIRM_PANEL_STR) == 0)
                    {
                        tmpPro = new InfoConfirmPanelProperty();
                    }
                    else if(tmp.compare(SOLID_LINE_STR) == 0)
                    {
                        tmpPro = new SolidLineProperty();
                    }
                    if(tmpPro != NULL)
                    {
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
