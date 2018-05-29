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
    bool seenMessage;
    QString messageText;
public:
    testGUI();
    ~testGUI();
    void close_messagebox();

private slots:
    void initTestCase();
    void cleanupTestCase();
    void inputDataA();  //имитируем событие щелчка левой кнопкой мыши на поле ввода A
    void inputDataB();  //имитируем событие щелчка левой кнопкой мыши на поле ввода B
    void buttonWork();  //сценарий проверки независимой работы кнопки
    void focus();       //сценарий проверки последовательности перехода фокуса ввода по компонентам формы
    void clearL();      //проверки очистки списка вывода перед заполнением
    void inputDataAFail(); //сценарий проверки появления окна с сообщением об ошибке при недопустимом значении A:
    void inputDataBFail();
    void testPositiveA();
    void testPositiveB();
};

void testGUI::close_messagebox()
{
    QMessageBox * msgbox = qobject_cast<QMessageBox*>(QApplication::activeModalWidget());
    if(msgbox) {
        seenMessage = true;
        messageText = msgbox->text();
        msgbox->close();
    }
}

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
    lineEditB->clear();
}

void testGUI::buttonWork()
{
    QObject::disconnect(pushButton, SIGNAL(clicked()), mainWindow, SLOT(calculate()));
    // создаем объект инспектора сигналов, реагирующего на сигнал clicked() кнопки
    QSignalSpy clickSpy(pushButton, SIGNAL(clicked()));
    // имитируем событие нажатия кнопки
    QTest::mouseClick(pushButton, Qt::LeftButton);
    // проверяем, что инспектор зафиксировал одно событие
    QCOMPARE(clickSpy.count(), 1);
    // присоединяем слот обработки данных обратно
    QObject::connect(pushButton, SIGNAL(clicked()), mainWindow, SLOT(calculate()));
}

void testGUI::focus()
{
    QTest::mouseClick(lineEditA, Qt::LeftButton);
    QVERIFY(lineEditA->hasFocus());
    QTest::keyClick(lineEditA, Qt::Key::Key_Tab);
    QVERIFY(lineEditB->hasFocus());
    QTest::keyClick(lineEditA, Qt::Key::Key_Tab);
    QVERIFY(pushButton->hasFocus());
    QTest::keyClick(pushButton, Qt::Key::Key_Tab);
    QVERIFY(listWidget->hasFocus());
    QTest::keyClick(pushButton, Qt::Key::Key_Tab);
    QVERIFY(lineEditA->hasFocus());
}

void testGUI::clearL()
{
    lineEditA->setText("10");
    lineEditB->setText("20");
    // генерируем событие нажатия кнопки
    pushButton->click();
    // проверяем количество значений в списке
    QCOMPARE(listWidget->count(), 4);
    // повторно нажимаем кнопку
    pushButton->click();
    // и проверяем количество значений
    QCOMPARE(listWidget->count(), 4);
}

void testGUI::inputDataAFail()
{
    lineEditA->setText("");
    lineEditB->setText("20");
    seenMessage = false;
    // через 100 мс выполняем функцию close_messagebox()
    QTimer::singleShot(100, this, &testGUI::close_messagebox);
    pushButton->click();
    if(!seenMessage) {
        QFAIL("no messagebox");
    }
    QCOMPARE(messageText, QString("A must be an integer"));
}

void testGUI::inputDataBFail()
{
    lineEditB->setText("");
    lineEditA->setText("20");
    seenMessage = false;
    // через 100 мс выполняем функцию close_messagebox()
    QTimer::singleShot(100, this, &testGUI::close_messagebox);
    pushButton->click();
    if(!seenMessage) {
        QFAIL("no messagebox");
    }
    QCOMPARE(messageText, QString("B must be an integer"));
}

void testGUI::testPositiveA()
{
    lineEditA->setText("-1");
    lineEditB->setText("10");
    seenMessage = false;
    QTimer::singleShot(100, this, &testGUI::close_messagebox);
    pushButton->click();
    if(!seenMessage) {
        QFAIL("no messagebox");
    }
    QCOMPARE(messageText, QString("a must be positive"));
}

void testGUI::testPositiveB()
{
    lineEditA->setText("10");
    lineEditB->setText("-1");
    seenMessage = false;
    QTimer::singleShot(100, this, &testGUI::close_messagebox);
    pushButton->click();
    if(!seenMessage) {
        QFAIL("no messagebox");
    }
    QCOMPARE(messageText, QString("b must be positive"));
}

QTEST_MAIN(testGUI)

#include "tst_testgui.moc"
