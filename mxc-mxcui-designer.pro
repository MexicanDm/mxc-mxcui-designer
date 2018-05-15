#-------------------------------------------------
#
# Project created by QtCreator 2018-05-09T10:13:50
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = mxc-mxcui-designer
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    paintwidget.cpp \
    publicfunc.cpp \
    ../mxc-mxcui/MXCUI/ui/imagebutton.cpp \
    ../mxc-mxcui/MXCUI/ui/uicomponent.cpp \
    ../mxc-mxcui/MXCUI/ui/wifialphabetkeyboard.cpp \
    treewidget.cpp \
    jsonPropertyItem/basecomonentproperty.cpp

HEADERS  += mainwindow.h \
    paintwidget.h \
    publicfunc.h \
    ../mxc-mxcui/MXCUI/ui/alphabetkeyboard.h \
    ../mxc-mxcui/MXCUI/ui/checkbox.h \
    ../mxc-mxcui/MXCUI/ui/checkimagebutton.h \
    ../mxc-mxcui/MXCUI/ui/circleprogressbar.h \
    ../mxc-mxcui/MXCUI/ui/combobox.h \
    ../mxc-mxcui/MXCUI/ui/imagebutton.h \
    ../mxc-mxcui/MXCUI/ui/imagelabel.h \
    ../mxc-mxcui/MXCUI/ui/infoconfirmpanel.h \
    ../mxc-mxcui/MXCUI/ui/ledprogressbar.h \
    ../mxc-mxcui/MXCUI/ui/listbox.h \
    ../mxc-mxcui/MXCUI/ui/loadinganimator.h \
    ../mxc-mxcui/MXCUI/ui/loadingprogressbar.h \
    ../mxc-mxcui/MXCUI/ui/messageboxpanel.h \
    ../mxc-mxcui/MXCUI/ui/numberkeyboard.h \
    ../mxc-mxcui/MXCUI/ui/rectprogressbar.h \
    ../mxc-mxcui/MXCUI/ui/roundrectprogressbar.h \
    ../mxc-mxcui/MXCUI/ui/textedit.h \
    ../mxc-mxcui/MXCUI/ui/texteditimage.h \
    ../mxc-mxcui/MXCUI/ui/textlabel.h \
    ../mxc-mxcui/MXCUI/ui/uicomponent.h \
    ../mxc-mxcui/MXCUI/ui/wifialphabetkeyboard.h \
    ../mxc-mxcui/MXCUI/ui/wificustombutton.h \
    treewidget.h \
    jsonPropertyItem/circleprobarproperty.h \
    jsonPropertyItem/checkboxproperty.h \
    jsonPropertyItem/imagebuttonproperty.h \
    jsonPropertyItem/alphabetkeyboardproperty.h \
    jsonPropertyItem/textlabelproperty.h \
    jsonPropertyItem/texteditproperty.h \
    jsonPropertyItem/basecomonentproperty.h


FORMS    += mainwindow.ui

RESOURCES += \
    main.qrc
