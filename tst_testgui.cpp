#include <QtTest>
#include <QCoreApplication>
#include <QLineEdit>
#include <QPushButton>
#include <QListWidget>
#include <QDialog>
#include "../../Lab2_widget/untitled1/mainwindow.h"
#include <QPlainTextEdit>
#include <QMessageBox>
#include <QWidget>

class testGUI : public QObject
{
    Q_OBJECT

private:
    MainWindow * mainWindow;
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
    void inputDataA();
    void inputDataB();
    void clickB();

};

testGUI::testGUI()
{

}

testGUI::~testGUI()
{

}

void testGUI::initTestCase()
{
    mainWindow = new MainWindow();
    lineEditA =  mainWindow->findChild<QLineEdit*>("lineEditA");
    lineEditB =  mainWindow->findChild<QLineEdit*>("lineEditB");
    pushButton =  mainWindow->findChild<QPushButton*>("pushButton");
    listWidget =  mainWindow->findChild<QListWidget*>("listWidget");
     mainWindow->show();
}

void testGUI::cleanupTestCase()
{
    delete  mainWindow;
}

void testGUI::inputDataA()
{
    // имитируем событие щелчка левой кнопкой мыши на поле ввода A
    QTest::mouseClick(lineEditA, Qt::LeftButton);
    // имитируем нажатие последовательности клавиш 123
    QTest::keyClicks(lineEditA, "123");
    // сравниваем введенное значение с образцом
    QCOMPARE(lineEditA->text(), QString("123"));
    // очищаем поле ввода
    lineEditA->clear();
}

void testGUI::inputDataB()
{
    // имитируем событие щелчка левой кнопкой мыши на поле ввода A
    QTest::mouseClick(lineEditB, Qt::LeftButton);
    // имитируем нажатие последовательности клавиш 123
    QTest::keyClicks(lineEditB, "123");
    // сравниваем введенное значение с образцом
    QCOMPARE(lineEditB->text(), QString("123"));
    // очищаем поле ввода
    lineEditA->clear();
}

void testGUI::clickB()
{

}


QTEST_MAIN(testGUI)

#include "tst_testgui.moc"
