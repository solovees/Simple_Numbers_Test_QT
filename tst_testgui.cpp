#include <QtTest>
#include <QCoreApplication>

// add necessary includes here

class testGUI : public QObject
{
    Q_OBJECT

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

}

void testGUI::cleanupTestCase()
{

}


QTEST_MAIN(testGUI)

#include "tst_testgui.moc"
