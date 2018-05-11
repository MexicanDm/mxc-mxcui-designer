#ifndef PAINTERWIDGET_H
#define PAINTERWIDGET_H

#include <QWidget>
#include "publicfunc.h"

class PaintWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PaintWidget(QWidget *parent = 0);
protected:
    void paintEvent(QPaintEvent *event);
private:

signals:

public slots:
    void slotGetComProperty();
    void slotUpdateSta(SearchType st);
};

#endif // PAINTERWIDGET_H
