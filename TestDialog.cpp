#include "TestDialog.h"
#include "ui_TestDialog.h"
#include "Protobuf/messageall.pb.h"
#include <QTime>
#include <QDateTime>
#include "Global_Param.h"
#include <QDebug>

TestDialog::TestDialog(QWidget *parent,QMQTT::Client *client = 0) :
    QDialog(parent), MqttForm(parent),
    ui(new Ui::TestDialog)
{
    ui->setupUi(this);
    this->init(client);

}

TestDialog::~TestDialog()
{
    delete ui;
}


void TestDialog::on_pushButton_start_clicked()
{
    Message message_proto;
    Message_ParamType* paramtype_proto = NULL;

            qint64 timeSecs =QDateTime::currentSecsSinceEpoch();

            int time =  QTime::currentTime().msec();
            qsrand(time);
            int  rand = qrand()%100;
            QString randstr = QString("%1").arg(rand);

            message_proto.set_id(randstr.toUtf8());
            message_proto.set_publish_ts(timeSecs);
            message_proto.set_ttl(60);

           message_proto.set_type(Message_MessageType_CONTROL_COMMAND);

            paramtype_proto = message_proto.add_params();
            QString key = "RemoteOperation";
            paramtype_proto->set_key(key.toUtf8());

              std::string RemoteOperation_str;

              RemoteOperation m_RemoteOperationData;

             qint64 timeMSecs =QDateTime::currentMSecsSinceEpoch();
              m_RemoteOperationData.set_message_timestamp(timeMSecs);

              qDebug()<<"timeSecs:"<<timeSecs;
               qDebug()<<"timeMSecs:"<<timeMSecs;

              RemoteControl* RemoteControl_info = m_RemoteOperationData.mutable_remote_control();
              QString zero = "0";
              RemoteControl_info->set_request_id(zero.toUtf8());
              RemoteControl_info->set_remote_control_command(RCC_START_CHARGING);

//              RemoteControlParam* RemoteControlParam_info = RemoteControl_info->add_remote_control_param();
//              QString RemoteControlParamKey = "1";
//              RemoteControlParam_info->set_key(RemoteControlParamKey.toUtf8());
//              QString RemoteControlParamValue = "60";
//              RemoteControlParam_info->set_value(RemoteControlParamValue.toUtf8());
              m_RemoteOperationData.SerializeToString(&RemoteOperation_str);


              paramtype_proto->set_value(RemoteOperation_str);


            std::string message_str;
            message_proto.SerializeToString(&message_str);
            QByteArray array = QByteArray::fromStdString(message_str);

            QMQTT::Message msg(Global_Param::getInstance().m_publishtopic.toInt(),Global_Param::getInstance().m_publish, array);

            _client->publish(msg);
}


void TestDialog::on_pushButton_finish_clicked()
{
    Message message_proto;
    Message_ParamType* paramtype_proto = NULL;

            qint64 timeSecs =QDateTime::currentSecsSinceEpoch();

            int time =  QTime::currentTime().msec();
            qsrand(time);
            int  rand = qrand()%100;
            QString randstr = QString("%1").arg(rand);

            message_proto.set_id(randstr.toUtf8());
            message_proto.set_publish_ts(timeSecs);
            message_proto.set_ttl(60);

           message_proto.set_type(Message_MessageType_CONTROL_COMMAND);

            paramtype_proto = message_proto.add_params();
            QString key = "RemoteOperation";
            paramtype_proto->set_key(key.toUtf8());

              std::string RemoteOperation_str;

              RemoteOperation m_RemoteOperationData;

             qint64 timeMSecs =QDateTime::currentMSecsSinceEpoch();
              m_RemoteOperationData.set_message_timestamp(timeMSecs);

              qDebug()<<"timeSecs:"<<timeSecs;
               qDebug()<<"timeMSecs:"<<timeMSecs;

              RemoteControl* RemoteControl_info = m_RemoteOperationData.mutable_remote_control();
              QString zero = "0";
              RemoteControl_info->set_request_id(zero.toUtf8());
              RemoteControl_info->set_remote_control_command(RCC_STOP_CHARGING);

//              RemoteControlParam* RemoteControlParam_info = RemoteControl_info->add_remote_control_param();
//              QString RemoteControlParamKey = "1";
//              RemoteControlParam_info->set_key(RemoteControlParamKey.toUtf8());
//              QString RemoteControlParamValue = "60";
//              RemoteControlParam_info->set_value(RemoteControlParamValue.toUtf8());
              m_RemoteOperationData.SerializeToString(&RemoteOperation_str);


              paramtype_proto->set_value(RemoteOperation_str);


            std::string message_str;
            message_proto.SerializeToString(&message_str);
            QByteArray array = QByteArray::fromStdString(message_str);

            QMQTT::Message msg(Global_Param::getInstance().m_publishtopic.toInt(),Global_Param::getInstance().m_publish, array);

            _client->publish(msg);
}
