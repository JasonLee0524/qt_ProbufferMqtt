#ifndef MONI_MAIN_H
#define MONI_MAIN_H

#include <QWidget>
#include "mqttform.h"
#include <QTimer>
#include "MessageDialog.h"
#include "ACPowerChargerDialog.h"
#include "RemoteOperationResponseDialog.h"
#include "cloud2device/RemoteOperationDialog.h"

namespace Ui {
class Moni_main;
}

class Moni_main : public MqttForm
{
    Q_OBJECT

public:
    explicit Moni_main(QWidget *parent = 0,QMQTT::Client *client = 0);
    ~Moni_main();
//    （1）注册
//    目前注册的形式为：无需特殊注册方式。直接接入数据上送。

//    （2）登录
//    目前登录信息和实时数据一并上送，没有特殊的登录信息体。
      void login();
//    （3）实时数据
//    （3.1）实时数据
//    （3.2）实时数据的服务器回包，目前需要通过MQTT自身的回包信息确认。

//    （4）充电交互
//    （4.1）启动充电时，系统下发启动充电。桩回复收到、完成两个回包。
//    （4.2）结束充电时，系统下发结束充电。桩回复收到、完成两个回包。

private slots:
    void onMQTT_Received(const QMQTT::Message &);

private slots:
    void timer5s_out();

    void on_pushButton_clicked();

    void on_pushButton_Message_clicked();

    void on_checkBox_Message_clicked(bool checked);

    void on_pushButton_data_clicked();

    void on_pushButton_clear_clicked();

    void on_pushButton_ACPowerCharger_clicked();

    void on_pushButton_RemoteOperation_clicked();

    void on_pushButton_RemoteControlResponse_clicked();


    void on_pushButton_send_clicked();

    void on_pushButton_sendclear_clicked();

private:
    Ui::Moni_main *ui;
    QTimer* m_timer5s;
    void initUI();

    MessageDialog* m_MessageDialog;
    ACPowerChargerDialog* m_ACPowerChargerDialog;
    RemoteOperationDialog* m_RemoteOperationDialog;
    RemoteOperationResponseDialog* m_RemoteOperationResponseDialog;

    void fixdata(const QByteArray &);

    void initACPowerCharger();
    void initBasicInfo();
    void initRealtimeInfo();
    void initAlarm();
    void initServiceInfo();
    void initLocalConfiguration();

};

#endif // MONI_MAIN_H
