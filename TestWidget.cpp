#include "TestWidget.h"
#include "ui_TestWidget.h"
#include "Protobuf/messageall.pb.h"
#include <QTime>
#include <QDateTime>
#include "Global_Param.h"
#include "Protobuf/base64.h"
TestWidget::TestWidget(QWidget *parent,QMQTT::Client *client) :
    MqttForm(parent),
    ui(new Ui::TestWidget)
{
    ui->setupUi(this);
      this->setAttribute(Qt::WA_DeleteOnClose);
    this->init(client);

}

TestWidget::~TestWidget()
{
    qDebug()<<"~TestWidget";
    delete ui;
}


void TestWidget::on_pushButton_start_clicked()
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
              QString zero = "start";
              RemoteControl_info->set_request_id(zero.toUtf8());
              RemoteControl_info->set_remote_control_command(RCC_START_CHARGING);

              m_RemoteOperationData.SerializeToString(&RemoteOperation_str);

              std::string encode;
              if(Global_Param::getInstance().m_base64){
                     encode =  base64_encode(reinterpret_cast<const unsigned char*>(RemoteOperation_str.c_str()),RemoteOperation_str.length());
              }else{
                     encode = RemoteOperation_str;
              }
              paramtype_proto->set_value(encode);


            std::string message_str;
            message_proto.SerializeToString(&message_str);
            QByteArray array;
            array = QByteArray::fromStdString(message_str);
            QMQTT::Message msg(Global_Param::getInstance().m_publishtopic.toInt(),Global_Param::getInstance().m_publish, array);

            _client->publish(msg);
}


void TestWidget::on_pushButton_finish_clicked()
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
              QString zero = "stop";
              RemoteControl_info->set_request_id(zero.toUtf8());
              RemoteControl_info->set_remote_control_command(RCC_STOP_CHARGING);

              m_RemoteOperationData.SerializeToString(&RemoteOperation_str);


              std::string encode;
              if(Global_Param::getInstance().m_base64){
                     encode =  base64_encode(reinterpret_cast<const unsigned char*>(RemoteOperation_str.c_str()),RemoteOperation_str.length());
              }else{
                     encode = RemoteOperation_str;
              }
              paramtype_proto->set_value(encode);


            std::string message_str;
            message_proto.SerializeToString(&message_str);
             QByteArray array;
            array = QByteArray::fromStdString(message_str);
            QMQTT::Message msg(Global_Param::getInstance().m_publishtopic.toInt(),Global_Param::getInstance().m_publish, array);

            _client->publish(msg);
}


void TestWidget::on_pushButton_clicked()
{
    this->deleteLater();
}

void TestWidget::on_pushButton_settime_clicked()
{
//     QString timestr = ui->lineEdit_time->text();
//     qint64 timesecadd = timestr.toInt() * 60;
//     qDebug()<<"timestr::"<<timestr;

//     Message message_proto;
//     Message_ParamType* paramtype_proto = NULL;

//             qint64 timeSecs =QDateTime::currentSecsSinceEpoch();

//             int time =  QTime::currentTime().msec();
//             qsrand(time);
//             int  rand = qrand()%100;
//             QString randstr = QString("%1").arg(rand);

//             message_proto.set_id(randstr.toUtf8());
//             message_proto.set_publish_ts(timeSecs);
//             message_proto.set_ttl(60);

//            message_proto.set_type(Message_MessageType_CONTROL_COMMAND);

//             paramtype_proto = message_proto.add_params();
//             QString key = "RemoteOperation";
//             paramtype_proto->set_key(key.toUtf8());

//               std::string RemoteOperation_str;

//               RemoteOperation m_RemoteOperationData;

//                qDebug()<<"timeMSecs——before:"<<QDateTime::currentMSecsSinceEpoch();
//              qint64 timeMSecs =QDateTime::currentMSecsSinceEpoch()+timesecadd*1000;
//               m_RemoteOperationData.set_message_timestamp(timeMSecs);

//               qDebug()<<"timeSecs:"<<timeSecs;
//                qDebug()<<"timeMSecs:"<<timeMSecs;

//               RemoteControl* RemoteControl_info = m_RemoteOperationData.mutable_remote_control();
//               QString zero = "yuyue";
//               RemoteControl_info->set_request_id(zero.toUtf8());
//               RemoteControl_info->set_remote_control_command(RCC_STARTUP);

//               m_RemoteOperationData.SerializeToString(&RemoteOperation_str);


//              paramtype_proto->set_value(RemoteOperation_str);


//             std::string message_str;
//             message_proto.SerializeToString(&message_str);
//             QByteArray array = QByteArray::fromStdString(message_str);

//             QMQTT::Message msg(Global_Param::getInstance().m_publishtopic.toInt(),Global_Param::getInstance().m_publish, array);

//             _client->publish(msg);

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

       RemoteConfiguration* RemoteConfiguration_info = m_RemoteOperationData.mutable_remote_configuration();
       QString request_id = "liyuzhe";
       RemoteConfiguration_info->set_request_id(request_id.toUtf8());

       RemoteConfigurationInfo* RemoteConfigurationInfo_info1 = RemoteConfiguration_info->add_remote_configuration_info();
       QString configuration_key = "chargingMode";
       QString configuration_value;
       if(ui->checkBox->isChecked()){
             configuration_value = "1";
       }
       else{
             configuration_value = "0";
       }
       RemoteConfigurationInfo_info1->set_configuration_key(configuration_key.toUtf8());
       RemoteConfigurationInfo_info1->set_configuration_value(configuration_value.toUtf8());

       RemoteConfigurationInfo* RemoteConfigurationInfo_info2 = RemoteConfiguration_info->add_remote_configuration_info();
       configuration_key = "reservationStartTime";
       configuration_value = ui->lineEdit_timebegin->text();
       RemoteConfigurationInfo_info2->set_configuration_key(configuration_key.toUtf8());
       RemoteConfigurationInfo_info2->set_configuration_value(configuration_value.toUtf8());

       configuration_key = "reservationEndTime";
       configuration_value = ui->lineEdit_timeend->text();
       RemoteConfigurationInfo* RemoteConfigurationInfo_info3 = RemoteConfiguration_info->add_remote_configuration_info();
       RemoteConfigurationInfo_info3->set_configuration_key(configuration_key.toUtf8());
       RemoteConfigurationInfo_info3->set_configuration_value(configuration_value.toUtf8());

       configuration_key = "timeZone";
       configuration_value = "UTC+8:00";
       RemoteConfigurationInfo* RemoteConfigurationInfo_info4 = RemoteConfiguration_info->add_remote_configuration_info();
       RemoteConfigurationInfo_info4->set_configuration_key(configuration_key.toUtf8());
       RemoteConfigurationInfo_info4->set_configuration_value(configuration_value.toUtf8());

       m_RemoteOperationData.SerializeToString(&RemoteOperation_str);


       std::string encode;
       if(Global_Param::getInstance().m_base64){
              encode =  base64_encode(reinterpret_cast<const unsigned char*>(RemoteOperation_str.c_str()),RemoteOperation_str.length());
       }else{
              encode = RemoteOperation_str;
       }
       paramtype_proto->set_value(encode);

        std::string message_str;
        message_proto.SerializeToString(&message_str);
        QByteArray array;
        array = QByteArray::fromStdString(message_str);


        QMQTT::Message msg(Global_Param::getInstance().m_publishtopic.toInt(),Global_Param::getInstance().m_publish, array);

        _client->publish(msg);
}
