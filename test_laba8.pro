QT += testlib
QT += gui
CONFIG += qt warn_on depend_includepath testcase

TEMPLATE = app

SOURCES +=  tst_testgui.cpp

DEPLOY_TARGET = $$shell_quote($$shell_path($$OUT_PWD/release/$$TARGET.exe))
QMAKE_POST_LINK = windeployqt $$DEPLOY_TARGET

DISTFILES += \
    .astylerc
