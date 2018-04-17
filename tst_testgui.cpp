#include <QtTest>
#include <QCoreApplication>
#include <QLineEdit>
#include <QPushButton>
#include <QListWidget>
#include <QDialog>
#include "../../Lab2_widget/untitled1/mainwindow.h"




class testGUI : public QObject
{
    Q_OBJECT

private:
    QDialog * mainDialog;
    QLineEdit * lineEditA;
    QLineEdit * lineEditB;
    QPushButton * pushButton;
    QListWidget * listWidget;
public:
    testGUI();
    ~testGUI();

private slots:
    void initTestCase();
    void cleanupTestCase();

};

testGUI::testGUI()
{

}

testGUI::~testGUI()
{

}

void testGUI::initTestCase()
{
    mainDialog = new QDialog();
    lineEditA = mainDialog->findChild<QLineEdit*>("lineEditA");
    lineEditB = mainDialog->findChild<QLineEdit*>("lineEditB");
    pushButton = mainDialog->findChild<QPushButton*>("pushButton");
    listWidget = mainDialog->findChild<QListWidget*>("listWidget");
    mainDialog->show();
}

void testGUI::cleanupTestCase()
{
    delete mainDialog;
}


QTEST_MAIN(testGUI)

#include "tst_testgui.moc"
