#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "qmqtt/qmqtt.h"
#include "Moni/Moni_main.h"
#include "TestWidget.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QMQTT::Client *client,QWidget *parent = 0);
    ~MainWindow();

private slots:
    void onMQTT_Connected();
    void onMQTT_disConnected();
    void onMQTT_error(QMQTT::ClientError);
    void onMQTT_Published(const QMQTT::Message &);
    void onMQTT_Received(const QMQTT::Message &);
    void onMQTT_subscribed(const QString &);
    void onMQTT_unsubscribed(const QString &);

    void on_pushButton_moniqi_clicked();

    void on_pushButton_test_clicked();

private:
    Ui::MainWindow *ui;
    QMQTT::Client* m_client;
    Moni_main* m_Moni;
    TestWidget* m_TestWidget;
    void log(const QString &);
};

#endif // MAINWINDOW_H
