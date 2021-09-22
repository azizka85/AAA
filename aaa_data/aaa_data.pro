#-------------------------------------------------
#
# Project created by QtCreator 2018-05-27T20:08:28
#
#-------------------------------------------------

QT       += core gui sql xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = aaa_data
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

TRANSLATIONS = translations/aaa_data_kazakh.ts \
                translations/aaa_data_russian.ts \
                translations/aaa_data_english.ts


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    aboutdialog.cpp \
    changedatabasedialog.cpp \
    settings.cpp \
    recommendationmodel.cpp \
    parameterdata.cpp \
    rangeparameterdata.cpp \
    parameterdatawithtype.cpp \
    rangeparameterdatawithtypes.cpp \
    parameterdatadialog.cpp \
    createparameterdatadialog.cpp \
    editparameterdatadialog.cpp \
    parameterdatawithcategorydialog.cpp \
    createparameterdatawithcategorydialog.cpp \
    editparameterdatawithcategorydialog.cpp \
    parameterdatawithcategorymodel.cpp \
    createparametervaluedialog.cpp \
    editparametervaluedialog.cpp \
    parametervalue.cpp \
    parametervalueform.cpp \
    rangeparametervalueform.cpp \
    rangeparametervalue.cpp \
    parametervaluewithtypeform.cpp \
    parametervaluewithtype.cpp \
    rangeparametervaluewithtypeform.cpp \
    rangeparametervaluewithtype.cpp \
    comparisonparameterdata.cpp \
    comparisonparametervalueform.cpp \
    comparisonparametervalue.cpp

HEADERS += \
        mainwindow.h \
    aboutdialog.h \
    changedatabasedialog.h \
    settings.h \
    recommendationmodel.h \
    parameterdata.h \
    rangeparameterdata.h \
    parameterdatawithtype.h \
    rangeparameterdatawithtypes.h \
    parameterdatadialog.h \
    createparameterdatadialog.h \
    editparameterdatadialog.h \
    parameterdatawithcategorydialog.h \
    createparameterdatawithcategorydialog.h \
    editparameterdatawithcategorydialog.h \
    parameterdatawithcategorymodel.h \
    createparametervaluedialog.h \
    editparametervaluedialog.h \
    parametervalue.h \
    parametervalueform.h \
    rangeparametervalueform.h \
    rangeparametervalue.h \
    parametervaluewithtypeform.h \
    parametervaluewithtype.h \
    rangeparametervaluewithtypeform.h \
    rangeparametervaluewithtype.h \
    comparisonparameterdata.h \
    comparisonparametervalueform.h \
    comparisonparametervalue.h

FORMS += \
        mainwindow.ui \
    aboutdialog.ui \
    changedatabasedialog.ui \
    parameterdatadialog.ui \
    createparameterdatadialog.ui \
    editparameterdatadialog.ui \
    parameterdatawithcategorydialog.ui \
    createparameterdatawithcategorydialog.ui \
    editparameterdatawithcategorydialog.ui \
    createparametervaluedialog.ui \
    editparametervaluedialog.ui \
    parametervalueform.ui \
    rangeparametervalueform.ui \
    parametervaluewithtypeform.ui \
    rangeparametervaluewithtypeform.ui \
    comparisonparametervalueform.ui

RESOURCES += \
    images.qrc

DISTFILES +=
