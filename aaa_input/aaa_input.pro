#-------------------------------------------------
#
# Project created by QtCreator 2018-06-05T15:07:54
#
#-------------------------------------------------

QT       += core gui sql xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = aaa_input
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

TRANSLATIONS = translations/aaa_input_kazakh.ts \
                translations/aaa_input_russian.ts \
                translations/aaa_input_english.ts

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    welldataform.cpp \
    wellformdata.cpp \
    productiondataform.cpp \
    productionformdata.cpp \
    reservoirdataform.cpp \
    reservoirformdata.cpp \
    mineralogydataform.cpp \
    mineralogyformdata.cpp \
    laboratorydataform.cpp \
    laboratoryformdata.cpp \
    calculationdataform.cpp \
    calculationformdata.cpp \
    settings.cpp \
    parameterdatawithcategorymodel.cpp \
    programform.cpp \
    treatmentdesignform.cpp \
    maintreatmentform.cpp \
    picklingform.cpp \
    preflushform.cpp \
    overflushform.cpp \
    stfbform.cpp \
    programformdata.cpp \
    maintreatmentformdata.cpp \
    treatmentformdata.cpp \
    picklingformdata.cpp \
    preflushformdata.cpp \
    overflushformdata.cpp \
    stfbformdata.cpp \
    doubleeditordelegate.cpp \
    updatemodel.cpp \
    inputparameter.cpp \
    parameterrecommendation.cpp \
    singleselectionparameter.cpp \
    rangeparameterrecommendation.cpp \
    comparisonparameterrecommendation.cpp \
    multiselectionparameter.cpp \
    multiselectionparameterwithcategory.cpp \
    mapselectionparameter.cpp \
    rangeparameterrecommendationwithcategory.cpp \
    changedatabasedialog.cpp

HEADERS += \
        mainwindow.h \
    formdata.h \
    welldataform.h \
    wellformdata.h \
    productiondataform.h \
    productionformdata.h \
    reservoirdataform.h \
    reservoirformdata.h \
    mineralogydataform.h \
    mineralogyformdata.h \
    laboratorydataform.h \
    laboratoryformdata.h \
    calculationdataform.h \
    calculationformdata.h \
    settings.h \
    parameterdatawithcategorymodel.h \
    programform.h \
    treatmentdesignform.h \
    maintreatmentform.h \
    picklingform.h \
    preflushform.h \
    overflushform.h \
    stfbform.h \
    programformdata.h \
    maintreatmentformdata.h \
    treatmentformdata.h \
    picklingformdata.h \
    preflushformdata.h \
    overflushformdata.h \
    stfbformdata.h \
    doubleeditordelegate.h \
    updatemodel.h \
    inputparameter.h \
    parameterrecommendation.h \
    singleselectionparameter.h \
    rangeparameterrecommendation.h \
    comparisonparameterrecommendation.h \
    multiselectionparameter.h \
    multiselectionparameterwithcategory.h \
    mapselectionparameter.h \
    rangeparameterrecommendationwithcategory.h \
    changedatabasedialog.h

FORMS += \
        mainwindow.ui \
    welldataform.ui \
    productiondataform.ui \
    reservoirdataform.ui \
    mineralogydataform.ui \
    laboratorydataform.ui \
    calculationdataform.ui \
    programform.ui \
    treatmentdesignform.ui \
    maintreatmentform.ui \
    picklingform.ui \
    preflushform.ui \
    overflushform.ui \
    stfbform.ui \
    changedatabasedialog.ui

RESOURCES += \
    images.qrc
