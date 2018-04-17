QT += testlib
QT += gui
CONFIG += qt warn_on depend_includepath testcase

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TEMPLATE = app

SOURCES +=  tst_testgui.cpp \
    ../../Lab2_widget/untitled1/mainwindow.cpp

DEPLOY_TARGET = $$shell_quote($$shell_path($$OUT_PWD/release/$$TARGET.exe))
QMAKE_POST_LINK = windeployqt $$DEPLOY_TARGET

DISTFILES += \
    .astylerc

FORMS += \
    ../../Lab2_widget/untitled1/mainwindow.ui

HEADERS += \
    ../../Lab2_widget/untitled1/mainwindow.h

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../Lab3_library/build-lab3_prost-Desktop/release/ -llab3_prost
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../Lab3_library/build-lab3_prost-Desktop/debug/ -llab3_prost
else:unix: LIBS += -L$$PWD/../../Lab3_library/build-lab3_prost-Desktop/ -llab3_prost

INCLUDEPATH += $$PWD/../../Lab3_library/lab3_prost
DEPENDPATH += $$PWD/../../Lab3_library/lab3_prost

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../Lab3_library/build-lab3_prost-Desktop/release/liblab3_prost.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../Lab3_library/build-lab3_prost-Desktop/debug/liblab3_prost.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../Lab3_library/build-lab3_prost-Desktop/release/lab3_prost.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../Lab3_library/build-lab3_prost-Desktop/debug/lab3_prost.lib
else:unix: PRE_TARGETDEPS += $$PWD/../../Lab3_library/build-lab3_prost-Desktop/liblab3_prost.a
