#include "paintwidget.h"

PaintWidget::PaintWidget(QWidget *parent) : QWidget(parent)
{

}

void PaintWidget::slotGetComProperty()
{
    QVector<JsonProperty> &vJsonPro = PublicFunc::vPublicJsonPro;
    //vCircle.clear();
    for(int i = 0;i < vJsonPro.count();i++)
    {
        JsonProperty &jsonpro = vJsonPro[i];
        for(int j = 0;j < jsonpro.vCircleBarProperty.count();j++)
        {

            CircleProBarProperty &circlePro = jsonpro.vCircleBarProperty[j];
            CircleProgressBar &circleBar = circlePro.circleBar;
            QRectF rectangle = QRectF(circlePro.x,circlePro.y,circlePro.width,circlePro.height);
            circleBar.setData(rectangle,circlePro.color,circlePro.baseColor,circlePro.penWidth,circlePro.minValue,circlePro.maxValue);

        }
        for(int j = 0;j < vJsonPro[i].vImageBtnProperty.count();j++)
        {
            ImageButtonProperty &imageBtnPro = jsonpro.vImageBtnProperty[j];
            ImageButton &imageBtn = imageBtnPro.imageBtn;
            imageBtn.setData(imageBtnPro.x,imageBtnPro.y,imageBtnPro.width,imageBtnPro.height);
            imageBtn.setImage(imageBtnPro.resActive,imageBtnPro.resinActive);
        }

        for(int j = 0;j < vJsonPro[i].vAlKeyboardProperty.count();j++)
        {

            AlphabetKeyboardProperty &alKeyboardPro = jsonpro.vAlKeyboardProperty[j];
            AlphabetKeyboard &alKeyboard = alKeyboardPro.alKeyboard;
            alKeyboard.init(new QFont("Droid Sans Fallback Regular",20));
            alKeyboard.setData(alKeyboardPro.x,alKeyboardPro.y,alKeyboardPro.width,alKeyboardPro.height);
            alKeyboard.setSymbolEnable("/", false);
            alKeyboard.setSymbolEnable("?", false);
            alKeyboard.setSymbolEnable("|", false);
            alKeyboard.setSymbolEnable(">", false);
            alKeyboard.setSymbolEnable("<", false);
            alKeyboard.setSymbolEnable(":", false);
            alKeyboard.setSymbolEnable("*", false);
            alKeyboard.setSymbolEnable("\\", false);
            alKeyboard.setSymbolEnable("\"", false);
        }

    }
    update();
}

void PaintWidget::slotUpdateSta(SearchType st)
{
    QVector<JsonProperty> &vJsonPro = PublicFunc::vPublicJsonPro;
    for(int i = 0;i < vJsonPro.count();i++)
    {
        JsonProperty &tempjsonPro = vJsonPro[i];
        if(st.fileName.compare(tempjsonPro.fileName) == 0)
        {
            if(st.structType.compare(CIRCLE_PROCESS_BAR_STR) == 0)
            {
                for(int j = 0;j < tempjsonPro.vCircleBarProperty.count();j++)
                {
                    CircleProBarProperty &circlePro = tempjsonPro.vCircleBarProperty[j];
                    if(st.structName.compare(circlePro.name) == 0)
                    {
                        circlePro.setData(st);
                        CircleProgressBar &circleBar = circlePro.circleBar;
                        QRectF rectangle = QRectF(circlePro.x,circlePro.y,circlePro.width,circlePro.height);
                        circleBar.setData(rectangle,circlePro.color,circlePro.baseColor,circlePro.penWidth,circlePro.minValue,circlePro.maxValue);
                        circleBar.setValue(circlePro.currentValue);
                        update();
                    }
                }
            }
            else if(st.structType.compare(IMAGE_BUTTON_STR) == 0)
            {
                for(int j = 0;j < tempjsonPro.vImageBtnProperty.count();j++)
                {
                    ImageButtonProperty &imageBtnPro = tempjsonPro.vImageBtnProperty[j];
                    if(st.structName.compare(imageBtnPro.name) == 0)
                    {
                        imageBtnPro.setData(st);
                        ImageButton &imageBtn = imageBtnPro.imageBtn;
                        imageBtn.setData(imageBtnPro.x,imageBtnPro.y,imageBtnPro.width,imageBtnPro.height);
                        imageBtn.setImage(imageBtnPro.resActive,imageBtnPro.resinActive);
                        update();
                    }
                }
            }
            else if(st.structType.compare(ALPHABET_KEYBOARD_STR) == 0)
            {
                for(int j = 0;j < tempjsonPro.vAlKeyboardProperty.count();j++)
                {
                    AlphabetKeyboardProperty &alKeyboardPro = tempjsonPro.vAlKeyboardProperty[j];
                    if(st.structName.compare(alKeyboardPro.name) == 0)
                    {
                        alKeyboardPro.setData(st);
                        AlphabetKeyboard &alKeyboard = alKeyboardPro.alKeyboard;
                        alKeyboard.setData(alKeyboardPro.x,alKeyboardPro.y,alKeyboardPro.width,alKeyboardPro.height);
                        update();
                    }
                }
            }
        }
    }
}

void PaintWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    int w = 600;
    int h = 1024;
    QPainter painter(this);
    QVector<JsonProperty> &vJsonPro = PublicFunc::vPublicJsonPro;
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setRenderHint(QPainter::TextAntialiasing, true);
    painter.setRenderHint(QPainter::SmoothPixmapTransform, true);
    painter.save();
    painter.fillRect(0,0,w,h,QBrush(QColor(0,0,0,255)));
    painter.restore();
    for(int i = 0;i < vJsonPro.count();i++)
    {
        JsonProperty jsonpro = vJsonPro[i];
        for(int j = 0;j < jsonpro.vCircleBarProperty.count();j++)
        {
            jsonpro.vCircleBarProperty[j].circleBar.draw(painter);
        }
        for(int j = 0;j < jsonpro.vImageBtnProperty.count();j++)
        {
            jsonpro.vImageBtnProperty[j].imageBtn.draw(painter);
        }
        for(int j = 0;j < jsonpro.vAlKeyboardProperty.count();j++)
        {
            jsonpro.vAlKeyboardProperty[j].alKeyboard.draw(painter);
        }
    }
}

