#ifndef PAINTERWIDGET_H
#define PAINTERWIDGET_H

#include <QWidget>
#include "publicfunc.h"
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
class PaintWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PaintWidget(QWidget *parent = 0);
protected:
    void paintEvent(QPaintEvent *event);
private:
    QVector<CircleProgressBar> vCircle;
    QVector<ImageButton> vImageBtn;
    QVector<TextLabel> vTextLab;
    QVector<TextEdit> vTextEdit;
    QVector<TextEditImage> vTEditImage;
    QVector<RectProgressBar> vRectProgressBar;
    QVector<NumberKeyboard> vNumKeyBoard;
    QVector<JsonProperty> vPaintJsonPro;
signals:

public slots:
    void slotGetComProperty(QVector<JsonProperty> jsonPro);
    void slotUpdateSta(SearchType st);
};

#endif // PAINTERWIDGET_H
