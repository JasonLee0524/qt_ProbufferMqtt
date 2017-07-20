#include "Moni_main.h"
#include "ui_Moni_main.h"
#include "mainwindow.h"
#include "Protobuf/messageall.pb.h"
#include <QTime>
#include <QDateTime>
#include "Global_Param.h"
#include <QDesktopWidget>
#include <QDir>
#include <QMessageBox>
#include <QStringList>
#include "Protobuf/base64.h"
Moni_main::Moni_main(QWidget *parent,QMQTT::Client *client) :
    MqttForm(parent),
    ui(new Ui::Moni_main)
{
    ui->setupUi(this);

    this->init(client);
    this->setAttribute(Qt::WA_DeleteOnClose);

    Global_Param::getInstance().InitData();

    initUI();

    m_timer5s = new QTimer(this);
    m_timer5s->start(5000);
    connect(m_timer5s,SIGNAL(timeout()),this,SLOT(timer5s_out()));

    connect(_client, SIGNAL(received(const QMQTT::Message &)), this, SLOT(onMQTT_Received(const QMQTT::Message &)));


    //tabwiget初始化
    initACPowerCharger();
    initBasicInfo();
    initRealtimeInfo();
    initAlarm();
    initServiceInfo();
    initLocalConfiguration();



}

Moni_main::~Moni_main()
{
    qDebug()<<"~Moni_main";
    if(m_timer5s!= NULL){
        m_timer5s->deleteLater();
        m_timer5s = NULL;
    }
    delete ui;
}

void Moni_main::initUI(){

    m_MessageDialog = NULL;
    m_ACPowerChargerDialog = NULL;
    m_RemoteOperationDialog = NULL;
    m_RemoteOperationResponseDialog = NULL;

    m_MessageDialog = new MessageDialog(this);
    m_ACPowerChargerDialog = new ACPowerChargerDialog(this);
    m_RemoteOperationDialog = new RemoteOperationDialog(this);
    m_RemoteOperationResponseDialog = new RemoteOperationResponseDialog(this);

    ui->checkBox_Message->setChecked(true);

}

void Moni_main::timer5s_out(){



}

void Moni_main::login(){

}


void Moni_main::on_pushButton_clicked()
{
    Message message_proto;
    Message_ParamType* paramtype_proto = NULL;
    if(ui->checkBox_Message->isChecked()){
        if(m_MessageDialog->Get_checkBox_version())
            message_proto.set_version(Global_Param::getInstance().message.version.toInt());
        if(m_MessageDialog->Get_checkBox_id())
            message_proto.set_id(Global_Param::getInstance().message.id.toUtf8());
        if(m_MessageDialog->Get_checkBox_publish_ts())
            message_proto.set_publish_ts(Global_Param::getInstance().message.publish_ts.toInt());
        if(m_MessageDialog->Get_checkBox_ttl())
            message_proto.set_ttl(Global_Param::getInstance().message.ttl.toInt());
        if(m_MessageDialog->Get_checkBox_sub_type())
            message_proto.set_sub_type(Global_Param::getInstance().message.sub_type.toUtf8());
        if(m_MessageDialog->Get_checkBox_MessageType())
            message_proto.set_type(Global_Param::getInstance().message.type);
        if(m_MessageDialog->Get_checkBox_ParamType()) {
            paramtype_proto = message_proto.add_params();
            if(m_MessageDialog->Get_checkBox_ParamType_key())
                paramtype_proto->set_key(Global_Param::getInstance().message.params.ParamType_Proto_key.toUtf8());
        }
    }

    if(ui->checkBox_ACPowerCharger->isChecked()){

        std::string ACPowerChargerResp_str;
        m_ACPowerChargerDialog->m_ACPowerChargerData.SerializeToString(&ACPowerChargerResp_str);
        std::string encode;
        if(Global_Param::getInstance().m_base64){
               encode =  base64_encode(reinterpret_cast<const unsigned char*>(ACPowerChargerResp_str.c_str()),ACPowerChargerResp_str.length());
        }else{
               encode = ACPowerChargerResp_str;
        }
        if(ui->checkBox_Message->isChecked()){
            if(m_MessageDialog->Get_checkBox_ParamType()) {
                if(m_MessageDialog->Get_checkBox_ParamType_value()){
                    paramtype_proto->clear_value();
                    paramtype_proto->set_value(encode);
                }
            }

        }
    }

    if(ui->checkBox_RemoteOperation->isChecked()){
        std::string RemoteOperation_str;
        m_RemoteOperationDialog->m_RemoteOperationData.SerializeToString(&RemoteOperation_str);
        std::string encode;
        if(Global_Param::getInstance().m_base64){
               encode =  base64_encode(reinterpret_cast<const unsigned char*>(RemoteOperation_str.c_str()),RemoteOperation_str.length());
        }else{
               encode = RemoteOperation_str;
        }
        if(ui->checkBox_Message->isChecked()){
            if(m_MessageDialog->Get_checkBox_ParamType()) {
                if(m_MessageDialog->Get_checkBox_ParamType_value()){
                    paramtype_proto->clear_value();
                    paramtype_proto->set_value(encode);
                }
            }

        }
    }

    if(ui->checkBox_RemoteControlResponse->isChecked()){
        std::string RemoteOperationResponse_str;
        m_RemoteOperationResponseDialog->m_RemoteOperationResponseData.SerializeToString(&RemoteOperationResponse_str);
        std::string encode;
        if(Global_Param::getInstance().m_base64){
               encode =  base64_encode(reinterpret_cast<const unsigned char*>(RemoteOperationResponse_str.c_str()),RemoteOperationResponse_str.length());
        }else{
               encode = RemoteOperationResponse_str;
        }
        if(ui->checkBox_Message->isChecked()){
            if(m_MessageDialog->Get_checkBox_ParamType()) {
                if(m_MessageDialog->Get_checkBox_ParamType_value()){
                    paramtype_proto->clear_value();
                    paramtype_proto->set_value(encode);
                }
            }

        }
    }

    std::string message_str;
    message_proto.SerializeToString(&message_str);
    QByteArray array = QByteArray::fromStdString(message_str);

    QMQTT::Message msg(Global_Param::getInstance().m_publishtopic.toInt(),Global_Param::getInstance().m_publish, array);

    _client->publish(msg);

}
void Moni_main::fixdata(const QByteArray &encodedString){
//    QByteArray arraycode;
//   if(Global_Param::getInstance().m_base64){
//           arraycode = QByteArray::fromBase64(encodedString);
//   }else{
//           arraycode = encodedString;
//   }

    //tab数据显示复位
    initACPowerCharger();
    initBasicInfo();
    initRealtimeInfo();
    initAlarm();
    initServiceInfo();
    initLocalConfiguration();
    std::string str_message = encodedString.toStdString();

    Message messageResp;
    messageResp.Clear();
    messageResp.ParseFromString(str_message);
    if(messageResp.has_version())
        ui->textBrowser->append(tr("Message::version:%1").arg(messageResp.version()));
    if(messageResp.has_id())
        ui->textBrowser->append(tr("Message::id:%1").arg(QString::fromStdString(messageResp.id())));
    if(messageResp.has_publish_ts())
        ui->textBrowser->append(tr("Message::publish_ts:%1").arg(messageResp.publish_ts()));
    if(messageResp.has_ttl())
        ui->textBrowser->append(tr("Message::ttl:%1").arg(messageResp.ttl()));
    if(messageResp.has_type())
        ui->textBrowser->append(tr("Message::type:%1").arg(messageResp.type()));
    if(messageResp.has_sub_type())
        ui->textBrowser->append(tr("Message::sub_type:%1").arg(QString::fromStdString(messageResp.sub_type())));


    for(int i = 0 ; i < messageResp.params_size(); i++){
        //解密
        std::string str_logonResp;

        if(Global_Param::getInstance().m_base64){
               str_logonResp =  base64_decode(messageResp.params(i).value());
        }else{
               str_logonResp = messageResp.params(i).value();
        }

        if(messageResp.params(i).key() == "ACPowerCharger"){
          ACPowerCharger logonResp;
          logonResp.ParseFromString(str_logonResp);
          if(logonResp.has_device_id())
          {
              QString str = QString::fromStdString(logonResp.device_id());
              ui->tableWidget_ACPowerCharger->setItem(0,1,new QTableWidgetItem(str));
              ui->textBrowser->append(tr("ACPowerCharger::device_id: %1").arg(QString::fromStdString(logonResp.device_id())));
           }
          if(logonResp.has_message_timestamp()){
              QString str = QString("%1").arg(logonResp.message_timestamp());
              ui->tableWidget_ACPowerCharger->setItem(0,3,new QTableWidgetItem(str));
              ui->textBrowser->append(tr("ACPowerCharger::message_timestamp: %1").arg(logonResp.message_timestamp()));
          }

          if(logonResp.has_basicinfo())
          {
              if(logonResp.basicinfo().has_power_charger_type())
              {
                  QString str = QString("%1").arg(logonResp.basicinfo().power_charger_type());
                  ui->tableWidget_BasicInfo->setItem(2,1,new QTableWidgetItem(str));
                  ui->textBrowser->append(tr("basicinfo::power_charger_type: %1").arg(logonResp.basicinfo().power_charger_type()));
              }
              if(logonResp.basicinfo().has_charging_connector_quantity())
              {
                  QString str = QString("%1").arg(logonResp.basicinfo().charging_connector_quantity());
                  ui->tableWidget_BasicInfo->setItem(2,3,new QTableWidgetItem(str));
                  ui->textBrowser->append(tr("basicinfo::charging_connector_quantity: %1").arg(logonResp.basicinfo().charging_connector_quantity()));
              }
              if(logonResp.basicinfo().has_power())
              {
                  QString str = QString("%1").arg(logonResp.basicinfo().power());
                  ui->tableWidget_BasicInfo->setItem(3,1,new QTableWidgetItem(str));
                  ui->textBrowser->append(tr("basicinfo::power: %1").arg(logonResp.basicinfo().power()));
              }
                 if(logonResp.basicinfo().has_common_basic_info()){
                     if(logonResp.basicinfo().common_basic_info().has_software_version())
                     {
                         QString str = QString::fromStdString(logonResp.basicinfo().common_basic_info().software_version());
                         ui->tableWidget_BasicInfo->setItem(0,1,new QTableWidgetItem(str));
                         ui->textBrowser->append(tr("basicinfo::software_version: %1").arg(QString::fromStdString(logonResp.basicinfo().common_basic_info().software_version())));
                    }
                     if(logonResp.basicinfo().common_basic_info().has_hardware_version())
                     {
                         QString str = QString::fromStdString(logonResp.basicinfo().common_basic_info().hardware_version());
                         ui->tableWidget_BasicInfo->setItem(0,3,new QTableWidgetItem(str));
                         ui->textBrowser->append(tr("basicinfo::hardware_version: %1").arg(QString::fromStdString(logonResp.basicinfo().common_basic_info().hardware_version())));
                     }
                }
                 if(logonResp.basicinfo().common_basic_info().has_service_state_info()){
                     if(logonResp.basicinfo().common_basic_info().service_state_info().has_service_state())
                     {
                         QString str = QString("%1").arg(logonResp.basicinfo().common_basic_info().service_state_info().service_state());
                         ui->tableWidget_BasicInfo->setItem(1,1,new QTableWidgetItem(str));
                         ui->textBrowser->append(tr("basicinfo::service_state: %1").arg(logonResp.basicinfo().common_basic_info().service_state_info().service_state()));
                     }
                     if(logonResp.basicinfo().common_basic_info().service_state_info().has_service_state_reason())
                     {
                         QString str = QString("%1").arg(logonResp.basicinfo().common_basic_info().service_state_info().service_state_reason());
                         ui->tableWidget_BasicInfo->setItem(1,3,new QTableWidgetItem(str));
                         ui->textBrowser->append(tr("basicinfo::service_state_reason: %1").arg(logonResp.basicinfo().common_basic_info().service_state_info().service_state_reason()));
                     }
                 }
          }
          if(logonResp.has_realtime_info()){
              if(logonResp.realtime_info().has_connectivity_state()){
                  if(logonResp.realtime_info().connectivity_state().has_network_operator())
                  {
                      QString str = QString("%1").arg(logonResp.realtime_info().connectivity_state().network_operator());
                      ui->tableWidget_RealtimeInfo->setItem(0,1,new QTableWidgetItem(str));
                      ui->textBrowser->append(tr("RealtimeInfo::network_operator: %1").arg(logonResp.realtime_info().connectivity_state().network_operator()));
                  }
                  if(logonResp.realtime_info().connectivity_state().has_network_type())
                  {
                      QString str = QString("%1").arg(logonResp.realtime_info().connectivity_state().network_type());
                      ui->tableWidget_RealtimeInfo->setItem(0,3,new QTableWidgetItem(str));
                      ui->textBrowser->append(tr("RealtimeInfo::network_type: %1").arg(logonResp.realtime_info().connectivity_state().network_type()));
                   }
              }
              if(logonResp.realtime_info().has_device_work_state()){

                      QString str = QString("%1").arg(logonResp.realtime_info().device_work_state());
                      ui->tableWidget_RealtimeInfo->setItem(1,3,new QTableWidgetItem(str));
                      ui->textBrowser->append(tr("RealtimeInfo::device_work_state: %1").arg(logonResp.realtime_info().device_work_state()));
              }

              for(int num = 0; num < logonResp.realtime_info().charging_connector_size(); num++){
                  QString str = QString::fromStdString(logonResp.realtime_info().charging_connector(num).charging_connector_id());
                  ui->tableWidget_RealtimeInfo->setItem(2,1,new QTableWidgetItem(str));

                  str = QString("%1").arg(logonResp.realtime_info().charging_connector(num).charging_connector_work_state());
                  ui->tableWidget_RealtimeInfo->setItem(2,3,new QTableWidgetItem(str));

                  str = QString("%1").arg(logonResp.realtime_info().charging_connector(num).charging_connector_connection_state());
                  ui->tableWidget_RealtimeInfo->setItem(3,1,new QTableWidgetItem(str));

                  str = QString("%1").arg(logonResp.realtime_info().charging_connector(num).charging_connector_fault_state());
                  ui->tableWidget_RealtimeInfo->setItem(3,3,new QTableWidgetItem(str));

                  str = QString("%1").arg(logonResp.realtime_info().charging_connector(num).power_charger_connector_output_type());
                  ui->tableWidget_RealtimeInfo->setItem(4,1,new QTableWidgetItem(str));

                  str = QString("%1").arg(logonResp.realtime_info().charging_connector(num).power_charger_connector_rated_output_voltage());
                  ui->tableWidget_RealtimeInfo->setItem(4,3,new QTableWidgetItem(str));

                  str = QString("%1").arg(logonResp.realtime_info().charging_connector(num).power_charger_connector_rated_output_power());
                  ui->tableWidget_RealtimeInfo->setItem(5,1,new QTableWidgetItem(str));

                  str = QString("%1").arg(logonResp.realtime_info().charging_connector(num).realtime_output_voltage());
                  ui->tableWidget_RealtimeInfo->setItem(5,3,new QTableWidgetItem(str));

                  str = QString("%1").arg(logonResp.realtime_info().charging_connector(num).realtime_output_current());
                  ui->tableWidget_RealtimeInfo->setItem(6,1,new QTableWidgetItem(str));

                  ui->textBrowser->append(tr("RealtimeInfo::charging_connector_id: %1").arg(QString::fromStdString(logonResp.realtime_info().charging_connector(num).charging_connector_id())));
                  ui->textBrowser->append(tr("RealtimeInfo::charging_connector_work_state: %1").arg(logonResp.realtime_info().charging_connector(num).charging_connector_work_state()));
                  ui->textBrowser->append(tr("RealtimeInfo::charging_connector_connection_state: %1").arg(logonResp.realtime_info().charging_connector(num).charging_connector_connection_state()));
                  ui->textBrowser->append(tr("RealtimeInfo::charging_connector_fault_state: %1").arg(logonResp.realtime_info().charging_connector(num).charging_connector_fault_state()));
                  ui->textBrowser->append(tr("RealtimeInfo::power_charger_connector_output_type: %1").arg(logonResp.realtime_info().charging_connector(num).power_charger_connector_output_type()));
                  ui->textBrowser->append(tr("RealtimeInfo::power_charger_connector_rated_output_voltage: %1").arg(logonResp.realtime_info().charging_connector(num).power_charger_connector_rated_output_voltage()));
                  ui->textBrowser->append(tr("RealtimeInfo::power_charger_connector_rated_output_power: %1").arg(logonResp.realtime_info().charging_connector(num).power_charger_connector_rated_output_power()));
                  ui->textBrowser->append(tr("RealtimeInfo::realtime_output_voltage: %1").arg(logonResp.realtime_info().charging_connector(num).realtime_output_voltage()));
                  ui->textBrowser->append(tr("RealtimeInfo::realtime_output_current: %1").arg(logonResp.realtime_info().charging_connector(num).realtime_output_current()));

              }
          }
          for(int alarms_num = 0 ; alarms_num < logonResp.alarms_size(); alarms_num++){
              QString str = QString("%1").arg(logonResp.alarms(alarms_num).alarm_type_id());
              ui->tableWidget_Alarm->setItem(0,1,new QTableWidgetItem(str));

              str = QString("%1").arg(logonResp.alarms(alarms_num).alarm_timestamp());
              ui->tableWidget_Alarm->setItem(0,3,new QTableWidgetItem(str));

              str = QString("%1").arg(logonResp.alarms(alarms_num).alarm_state());
              ui->tableWidget_Alarm->setItem(1,1,new QTableWidgetItem(str));

              ui->textBrowser->append(tr("alarms::alarm_type_id: %1").arg(logonResp.alarms(alarms_num).alarm_type_id()));
              ui->textBrowser->append(tr("alarms::alarm_timestamp: %1").arg(logonResp.alarms(alarms_num).alarm_timestamp()));
              ui->textBrowser->append(tr("alarms::alarm_state: %1").arg(logonResp.alarms(alarms_num).alarm_state()));
          }
          for(int service_num = 0 ; service_num < logonResp.service_info_size(); service_num++){
              QString str;
              if(logonResp.service_info(service_num).has_service_id()){
                  str = QString::fromStdString(logonResp.service_info(service_num).service_id());
                  ui->tableWidget_ServiceInfo->setItem(0,1,new QTableWidgetItem(str));
                  ui->textBrowser->append(tr("ServiceInfo::service_id: %1").arg(QString::fromStdString(logonResp.service_info(service_num).service_id())));
              }

             if(logonResp.service_info(service_num).has_service_event()){
                 str = QString("%1").arg(logonResp.service_info(service_num).service_event());
                 ui->tableWidget_ServiceInfo->setItem(0,3,new QTableWidgetItem(str));
                 ui->textBrowser->append(tr("ServiceInfo::service_event: %1").arg(logonResp.service_info(service_num).service_event()));
             }

             if(logonResp.service_info(service_num).has_charging_event_timestamp()){
                 str = QString("%1").arg(logonResp.service_info(service_num).charging_event_timestamp());
                 ui->tableWidget_ServiceInfo->setItem(1,1,new QTableWidgetItem(str));
                 ui->textBrowser->append(tr("ServiceInfo::charging_event_timestamp: %1").arg(logonResp.service_info(service_num).charging_event_timestamp()));
             }

             if(logonResp.service_info(service_num).has_charging_connector_id()){
                str = QString::fromStdString(logonResp.service_info(service_num).charging_connector_id());
                ui->tableWidget_ServiceInfo->setItem(1,3,new QTableWidgetItem(str));
                ui->textBrowser->append(tr("ServiceInfo::charging_connector_id: %1").arg(QString::fromStdString(logonResp.service_info(service_num).charging_connector_id())));
             }

            if(logonResp.service_info(service_num).has_realtime_charged_energy()){
                  str = QString("%1").arg(logonResp.service_info(service_num).realtime_charged_energy());
                  ui->tableWidget_ServiceInfo->setItem(2,1,new QTableWidgetItem(str));
                  ui->textBrowser->append(tr("ServiceInfo::realtime_charged_energy: %1").arg(logonResp.service_info(service_num).realtime_charged_energy()));
             }

             if(logonResp.service_info(service_num).has_service_finish_result()){
                 str = QString("%1").arg(logonResp.service_info(service_num).service_finish_result());
                 ui->tableWidget_ServiceInfo->setItem(2,3,new QTableWidgetItem(str));
                 ui->textBrowser->append(tr("ServiceInfo::service_finish_result: %1").arg(logonResp.service_info(service_num).service_finish_result()));
             }

              if(logonResp.service_info(service_num).has_charged_energy_total()){
                 str = QString("%1").arg(logonResp.service_info(service_num).charged_energy_total());
                 ui->tableWidget_ServiceInfo->setItem(3,1,new QTableWidgetItem(str));
                 ui->textBrowser->append(tr("ServiceInfo::charged_energy_total: %1").arg(logonResp.service_info(service_num).charged_energy_total()));
              }
         }
          if(logonResp.has_local_configuration()){
              if(logonResp.local_configuration().has_full())
              {

                  ui->textBrowser->append(tr("LocalConfiguration::full: %1").arg(logonResp.local_configuration().full()));
              }
              int total = logonResp.local_configuration().configuration_info_size();
              for(int LocalConfigurationInfo_num = 0 ; LocalConfigurationInfo_num < total; LocalConfigurationInfo_num++){
                  if(logonResp.local_configuration().configuration_info(LocalConfigurationInfo_num).has_configuration_key())
                  {
                      ui->textBrowser->append(tr("LocalConfiguration::configuration_key: %1").arg(QString::fromStdString(logonResp.local_configuration().configuration_info(LocalConfigurationInfo_num).configuration_key())));
                  }
                  if(logonResp.local_configuration().configuration_info(LocalConfigurationInfo_num).has_configuration_value())
                  {
                      ui->textBrowser->append(tr("LocalConfiguration::configuration_value: %1").arg(QString::fromStdString(logonResp.local_configuration().configuration_info(LocalConfigurationInfo_num).configuration_value())));
                  }
                  if(logonResp.local_configuration().configuration_info(LocalConfigurationInfo_num).has_local_configuration_info_access_type())
                  {
                      ui->textBrowser->append(tr("LocalConfiguration::local_configuration_info_access_type: %1").arg(logonResp.local_configuration().configuration_info(LocalConfigurationInfo_num).local_configuration_info_access_type()));
                  }
                  if(logonResp.local_configuration().configuration_info(LocalConfigurationInfo_num).has_has_been_updated())
                  {
                      ui->textBrowser->append(tr("LocalConfiguration::has_been_updated: %1").arg(logonResp.local_configuration().configuration_info(LocalConfigurationInfo_num).has_been_updated()));
                  }
                  if(logonResp.local_configuration().configuration_info(LocalConfigurationInfo_num).has_failurereason())
                  {
                      ui->textBrowser->append(tr("LocalConfiguration::failureReason: %1").arg(QString::fromStdString(logonResp.local_configuration().configuration_info(LocalConfigurationInfo_num).failurereason())));
                  }
              }
          }

       }
       if(messageResp.params(i).key() == "RemoteOperation"){
       //   std::string str_logonResp = messageResp.params(i).value();
          RemoteOperation logonResp;
          logonResp.ParseFromString(str_logonResp);
          if(logonResp.has_message_timestamp())
              ui->textBrowser->append(tr("RemoteOperation::message_timestamp: %1").arg(logonResp.message_timestamp()));
          if(logonResp.has_remote_configuration()){
                if(logonResp.remote_configuration().has_request_id())
                    ui->textBrowser->append(tr("RemoteConfiguration::request_id: %1").arg(QString::fromStdString(logonResp.remote_configuration().request_id())));
                for(int i = 0 ; i < logonResp.remote_configuration().remote_configuration_info_size();i++){
                    if(logonResp.remote_configuration().remote_configuration_info(i).has_configuration_key())
                        ui->textBrowser->append(tr("RemoteConfiguration::configuration_key: %1").arg(QString::fromStdString(logonResp.remote_configuration().remote_configuration_info(i).configuration_key())));
                    if(logonResp.remote_configuration().remote_configuration_info(i).has_configuration_value())
                        ui->textBrowser->append(tr("RemoteConfiguration::configuration_value: %1").arg(QString::fromStdString(logonResp.remote_configuration().remote_configuration_info(i).configuration_value())));
                }
          }
          if(logonResp.has_remote_control()){
                if(logonResp.remote_control().has_request_id())
                    ui->textBrowser->append(tr("RemoteControl::request_id: %1").arg(QString::fromStdString(logonResp.remote_control().request_id())));
                if(logonResp.remote_control().has_remote_control_command())
                    ui->textBrowser->append(tr("RemoteControl::RemoteControlCommand: %1").arg(logonResp.remote_control().remote_control_command()));
                for(int i = 0 ; i < logonResp.remote_control().remote_control_param_size();i++){
                    if(logonResp.remote_configuration().remote_configuration_info(i).has_configuration_key())
                        ui->textBrowser->append(tr("RemoteControl::key: %1").arg(QString::fromStdString(logonResp.remote_control().remote_control_param(i).key())));
                    if(logonResp.remote_configuration().remote_configuration_info(i).has_configuration_value())
                        ui->textBrowser->append(tr("RemoteControl::value: %1").arg(QString::fromStdString(logonResp.remote_control().remote_control_param(i).value())));
                }
          }
          if(logonResp.has_remote_upgrade()){
              if(logonResp.remote_upgrade().has_request_id())
                  ui->textBrowser->append(tr("RemoteUpgrade::request_id: %1").arg(QString::fromStdString(logonResp.remote_upgrade().request_id())));
              if(logonResp.remote_upgrade().has_software_version())
                  ui->textBrowser->append(tr("RemoteUpgrade::software_version: %1").arg(QString::fromStdString(logonResp.remote_upgrade().software_version())));
              if(logonResp.remote_upgrade().has_ftp_address())
                  ui->textBrowser->append(tr("RemoteUpgrade::ftp_address: %1").arg(QString::fromStdString(logonResp.remote_upgrade().ftp_address())));
          }
       }
       if(messageResp.params(i).key() == "RemoteOperationResponse"){
     //     std::string str_logonResp = messageResp.params(i).value();
          RemoteOperationResponse logonResp;
          logonResp.ParseFromString(str_logonResp);
          if(logonResp.has_remote_configuration_response()){
              if(logonResp.remote_configuration_response().has_request_id())
                  ui->textBrowser->append(tr("RemoteConfigurationResponse::request_id: %1").arg(QString::fromStdString(logonResp.remote_configuration_response().request_id())));
              if(logonResp.remote_configuration_response().has_device_id())
                  ui->textBrowser->append(tr("RemoteConfigurationResponse::device_id: %1").arg(QString::fromStdString(logonResp.remote_configuration_response().device_id())));
              if(logonResp.remote_configuration_response().has_remote_configuration_response_type())
                  ui->textBrowser->append(tr("RemoteConfigurationResponse::configuration_response_type: %1").arg(logonResp.remote_configuration_response().remote_configuration_response_type()));
              if(logonResp.remote_configuration_response().has_failurereason())
                  ui->textBrowser->append(tr("RemoteConfigurationResponse::failureReason: %1").arg(QString::fromStdString(logonResp.remote_configuration_response().failurereason())));
              for(int i = 0; i < logonResp.remote_configuration_response().configuration_info_size(); i++){

                  if(logonResp.remote_configuration_response().configuration_info(i).has_configuration_key())
                      ui->textBrowser->append(tr("LocalConfigurationinfo::configuration_key: %1").arg(QString::fromStdString(logonResp.remote_configuration_response().configuration_info(i).configuration_key())));
                  if(logonResp.remote_configuration_response().configuration_info(i).has_configuration_value())
                      ui->textBrowser->append(tr("LocalConfigurationinfo::configuration_value: %1").arg(QString::fromStdString(logonResp.remote_configuration_response().configuration_info(i).configuration_value())));
                  if(logonResp.remote_configuration_response().configuration_info(i).has_local_configuration_info_access_type())
                      ui->textBrowser->append(tr("LocalConfigurationinfo::local_configuration_info_access_type: %1").arg(logonResp.remote_configuration_response().configuration_info(i).local_configuration_info_access_type()));
                  if(logonResp.remote_configuration_response().configuration_info(i).has_has_been_updated())
                      ui->textBrowser->append(tr("LocalConfigurationinfo::has_been_updated: %1").arg(logonResp.remote_configuration_response().configuration_info(i).has_been_updated()));
                  if(logonResp.remote_configuration_response().configuration_info(i).has_failurereason())
                      ui->textBrowser->append(tr("LocalConfigurationinfo::failureReason: %1").arg(QString::fromStdString(logonResp.remote_configuration_response().configuration_info(i).failurereason())));
              }
          }
          if(logonResp.has_remote_control_response()){
              if(logonResp.remote_control_response().has_request_id())
                  ui->textBrowser->append(tr("RemoteControlResponse::request_id: %1").arg(QString::fromStdString(logonResp.remote_control_response().request_id())));
              if(logonResp.remote_control_response().has_device_id())
                  ui->textBrowser->append(tr("RemoteControlResponse::device_id: %1").arg(QString::fromStdString(logonResp.remote_control_response().device_id())));
              if(logonResp.remote_control_response().has_remote_control_response_type())
                  ui->textBrowser->append(tr("RemoteControlResponse::remote_control_response_type: %1").arg(logonResp.remote_control_response().remote_control_response_type()));
              if(logonResp.remote_control_response().has_failurereason())
                  ui->textBrowser->append(tr("RemoteControlResponse::failureReason: %1").arg(QString::fromStdString(logonResp.remote_control_response().failurereason())));
          }
          if(logonResp.has_remote_upgrade_response()){
              if(logonResp.remote_upgrade_response().has_request_id())
                  ui->textBrowser->append(tr("RemoteUpgradeResponse::request_id: %1").arg(QString::fromStdString(logonResp.remote_upgrade_response().request_id())));
              if(logonResp.remote_upgrade_response().has_device_id())
                  ui->textBrowser->append(tr("RemoteUpgradeResponse::device_id: %1").arg(QString::fromStdString(logonResp.remote_upgrade_response().device_id())));
          }
       }

    }
}


void Moni_main::onMQTT_Received(const QMQTT::Message &message)
{
   ui->textEdit_1->clear();
   ui->textBrowser->clear();

   ui->textEdit_1->setText(message.payload().toHex());
   QDateTime dateTime;
   QString time = dateTime.currentDateTime().toString("yyyy-MM-dd / hh:mm:ss");
   ui->textBrowser->append(time);
   ui->textBrowser->append(tr("message recevied from %1: qos=%2").arg(message.topic()).arg(message.qos()));
   ui->textBrowser->append(tr("message_size:%1").arg(message.payload().size()));

   QByteArray encodedString = message.payload();
   fixdata(encodedString);

   //保存数据到文件
   //获取数据
   QString path;
   QDir dir;
   path=dir.currentPath() + "/data.txt";
    qDebug()<<""<<path;
    QFile file(path);
    if (!file.open(QIODevice::WriteOnly|QIODevice::Text | QIODevice::Append)) {
        QMessageBox::critical(NULL, "提示", "无法创建文件");
        return ;
    }
    QTextStream out(&file);
    //数据流
    QString recode = ui->textEdit_1->toPlainText();
    out<<recode<<endl;
    QString encode = ui->textBrowser->toPlainText();
    out<<encode<<endl<<endl;
    out.flush();
    file.close();
}


void Moni_main::on_pushButton_Message_clicked()
{
    m_MessageDialog->show();
    m_MessageDialog->move ((QApplication::desktop()->width() - this->width())/2,(QApplication::desktop()->height() - this->height())/2);
    m_MessageDialog->setFixedSize(800,600);
}


void Moni_main::on_pushButton_ACPowerCharger_clicked()
{
    m_ACPowerChargerDialog->show();
    m_ACPowerChargerDialog->move ((QApplication::desktop()->width() - this->width())/2,(QApplication::desktop()->height() - this->height())/2);
    m_ACPowerChargerDialog->setFixedSize(800,600);
}

void Moni_main::on_pushButton_RemoteOperation_clicked()
{
    m_RemoteOperationDialog->show();
    m_RemoteOperationDialog->move ((QApplication::desktop()->width() - this->width())/2,(QApplication::desktop()->height() - this->height())/2);
    m_RemoteOperationDialog->setFixedSize(800,600);
}


void Moni_main::on_pushButton_RemoteControlResponse_clicked()
{
    m_RemoteOperationResponseDialog->show();
    m_RemoteOperationResponseDialog->move ((QApplication::desktop()->width() - this->width())/2,(QApplication::desktop()->height() - this->height())/2);
    m_RemoteOperationResponseDialog->setFixedSize(800,600);
}

void Moni_main::on_pushButton_data_clicked()
{
    ui->textBrowser->clear();
    QByteArray encodedString = QByteArray::fromHex( ui->textEdit_1->toPlainText().toUtf8());
    fixdata(encodedString);
}

void Moni_main::on_pushButton_clear_clicked()
{
    ui->textBrowser->clear();
}


void Moni_main::on_checkBox_Message_clicked(bool checked)
{
    if(checked){
        ui->checkBox_ACPowerCharger->setChecked(true);
        ui->checkBox_RemoteOperation->setChecked(true);
    }else{
        ui->checkBox_ACPowerCharger->setChecked(false);
        ui->checkBox_RemoteOperation->setChecked(false);
    }
}

void Moni_main::initACPowerCharger(){

    QMap<int,QString>  map;
    map.insert(1,tr("device_id"));
    map.insert(2,tr("message_timestamp"));
    int column = 4;
    int row = 1;
    ui->tableWidget_ACPowerCharger->setColumnCount(column);
    ui->tableWidget_ACPowerCharger->setRowCount(row);
    ui->tableWidget_ACPowerCharger->horizontalHeader()->setHidden(true);
    ui->tableWidget_ACPowerCharger->verticalHeader()->setHidden(true);
    ui->tableWidget_ACPowerCharger->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget_ACPowerCharger->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget_ACPowerCharger->setEditTriggers(QAbstractItemView::NoEditTriggers); //设置不可编辑

     ui->tableWidget_ACPowerCharger->setItem(0,0,new QTableWidgetItem(map.value(1)));
     ui->tableWidget_ACPowerCharger->setItem(0,1,new QTableWidgetItem("N/A"));
     ui->tableWidget_ACPowerCharger->setItem(0,2,new QTableWidgetItem(map.value(2)));
     ui->tableWidget_ACPowerCharger->setItem(0,3,new QTableWidgetItem("N/A"));

}

void Moni_main::initBasicInfo(){
    QMap<int,QString> mapdata;

    mapdata.insert(1,tr("software_version"));
    mapdata.insert(2,tr("hardware_version"));
    mapdata.insert(3,tr("ServiceState"));
    mapdata.insert(4,tr("ServiceStateReason"));
    mapdata.insert(5,tr("PowerChargerType"));
    mapdata.insert(6,tr("charging_connector_quantity"));
    mapdata.insert(7,tr("power"));

    int column = 4;
    int row = 4;
    ui->tableWidget_BasicInfo->setColumnCount(column);
    ui->tableWidget_BasicInfo->setRowCount(row);
    ui->tableWidget_BasicInfo->horizontalHeader()->setHidden(true);
    ui->tableWidget_BasicInfo->verticalHeader()->setHidden(true);
    ui->tableWidget_BasicInfo->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget_BasicInfo->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget_BasicInfo->setEditTriggers(QAbstractItemView::NoEditTriggers); //设置不可编辑

    ui->tableWidget_BasicInfo->setItem(0,0,new QTableWidgetItem(mapdata.value(1)));
    ui->tableWidget_BasicInfo->setItem(0,1,new QTableWidgetItem("N/A"));

    ui->tableWidget_BasicInfo->setItem(0,2,new QTableWidgetItem(mapdata.value(2)));
    ui->tableWidget_BasicInfo->setItem(0,3,new QTableWidgetItem("N/A"));

    ui->tableWidget_BasicInfo->setItem(1,0,new QTableWidgetItem(mapdata.value(3)));
    ui->tableWidget_BasicInfo->setItem(1,1,new QTableWidgetItem("N/A"));

    ui->tableWidget_BasicInfo->setItem(1,2,new QTableWidgetItem(mapdata.value(4)));
    ui->tableWidget_BasicInfo->setItem(1,3,new QTableWidgetItem("N/A"));

    ui->tableWidget_BasicInfo->setItem(2,0,new QTableWidgetItem(mapdata.value(5)));
    ui->tableWidget_BasicInfo->setItem(2,1,new QTableWidgetItem("N/A"));

    ui->tableWidget_BasicInfo->setItem(2,2,new QTableWidgetItem(mapdata.value(6)));
    ui->tableWidget_BasicInfo->setItem(2,3,new QTableWidgetItem("N/A"));

    ui->tableWidget_BasicInfo->setItem(3,0,new QTableWidgetItem(mapdata.value(7)));
    ui->tableWidget_BasicInfo->setItem(3,1,new QTableWidgetItem("N/A"));

}

void Moni_main::initRealtimeInfo(){
    QMap<int,QString> mapdata;

    mapdata.insert(1,tr("NetworkOperator"));
    mapdata.insert(2,tr("NetworkType"));
    mapdata.insert(3,tr("DeviceWorkState"));
    mapdata.insert(4,tr("DeviceFaultState"));
    mapdata.insert(5,tr("charging_connector_id"));
    mapdata.insert(6,tr("ChargingConnectorWorkState"));
    mapdata.insert(7,tr("ChargingConnectorConnectionState"));
    mapdata.insert(8,tr("ChargingConnectorFaultState"));
    mapdata.insert(9,tr("PowerChargerConnectorOutputType"));
    mapdata.insert(10,tr("PowerChargerConnectorOutputVoltage"));
    mapdata.insert(11,tr("power_charger_connector_rated_output_power"));
    mapdata.insert(12,tr("realtime_output_voltage"));
    mapdata.insert(13,tr("realtime_output_current"));

    int column = 4;
    int row = 6;
    ui->tableWidget_RealtimeInfo->setColumnCount(column);
    ui->tableWidget_RealtimeInfo->setRowCount(row);
    ui->tableWidget_RealtimeInfo->horizontalHeader()->setHidden(true);
    ui->tableWidget_RealtimeInfo->verticalHeader()->setHidden(true);
    ui->tableWidget_RealtimeInfo->horizontalHeader()->setStretchLastSection(true);
   ui->tableWidget_RealtimeInfo->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
   ui->tableWidget_RealtimeInfo->setEditTriggers(QAbstractItemView::NoEditTriggers); //设置不可编辑

    ui->tableWidget_RealtimeInfo->setItem(0,0,new QTableWidgetItem(mapdata.value(1)));
    ui->tableWidget_RealtimeInfo->setItem(0,1,new QTableWidgetItem("N/A"));
    ui->tableWidget_RealtimeInfo->setItem(0,2,new QTableWidgetItem(mapdata.value(2)));
    ui->tableWidget_RealtimeInfo->setItem(0,3,new QTableWidgetItem("N/A"));

    ui->tableWidget_RealtimeInfo->setItem(1,0,new QTableWidgetItem(mapdata.value(3)));
    ui->tableWidget_RealtimeInfo->setItem(1,1,new QTableWidgetItem("N/A"));
    ui->tableWidget_RealtimeInfo->setItem(1,2,new QTableWidgetItem(mapdata.value(4)));
    ui->tableWidget_RealtimeInfo->setItem(1,3,new QTableWidgetItem("N/A"));

    ui->tableWidget_RealtimeInfo->setItem(2,0,new QTableWidgetItem(mapdata.value(5)));
    ui->tableWidget_RealtimeInfo->setItem(2,1,new QTableWidgetItem("N/A"));
    ui->tableWidget_RealtimeInfo->setItem(2,2,new QTableWidgetItem(mapdata.value(6)));
    ui->tableWidget_RealtimeInfo->setItem(2,3,new QTableWidgetItem("N/A"));

    ui->tableWidget_RealtimeInfo->setItem(3,0,new QTableWidgetItem(mapdata.value(7)));
    ui->tableWidget_RealtimeInfo->setItem(3,1,new QTableWidgetItem("N/A"));
    ui->tableWidget_RealtimeInfo->setItem(3,2,new QTableWidgetItem(mapdata.value(8)));
    ui->tableWidget_RealtimeInfo->setItem(3,3,new QTableWidgetItem("N/A"));

    ui->tableWidget_RealtimeInfo->setItem(4,0,new QTableWidgetItem(mapdata.value(9)));
    ui->tableWidget_RealtimeInfo->setItem(4,1,new QTableWidgetItem("N/A"));
    ui->tableWidget_RealtimeInfo->setItem(4,2,new QTableWidgetItem(mapdata.value(10)));
    ui->tableWidget_RealtimeInfo->setItem(4,3,new QTableWidgetItem("N/A"));

    ui->tableWidget_RealtimeInfo->setItem(5,0,new QTableWidgetItem(mapdata.value(11)));
    ui->tableWidget_RealtimeInfo->setItem(5,1,new QTableWidgetItem("N/A"));
    ui->tableWidget_RealtimeInfo->setItem(5,2,new QTableWidgetItem(mapdata.value(12)));
    ui->tableWidget_RealtimeInfo->setItem(5,3,new QTableWidgetItem("N/A"));

    ui->tableWidget_RealtimeInfo->setItem(6,0,new QTableWidgetItem(mapdata.value(13)));
    ui->tableWidget_RealtimeInfo->setItem(6,1,new QTableWidgetItem("N/A"));
}

void Moni_main::initAlarm(){
    QMap<int,QString>  map;
    map.insert(1,tr("alarm_type_id"));
    map.insert(2,tr("alarm_timestamp"));
    map.insert(3,tr("AlarmState"));

    int column = 4;
    int row = 2;
    ui->tableWidget_Alarm->setColumnCount(column);
    ui->tableWidget_Alarm->setRowCount(row);
    ui->tableWidget_Alarm->horizontalHeader()->setHidden(true);
    ui->tableWidget_Alarm->verticalHeader()->setHidden(true);
    ui->tableWidget_Alarm->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget_Alarm->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget_Alarm->setEditTriggers(QAbstractItemView::NoEditTriggers); //设置不可编辑

     ui->tableWidget_Alarm->setItem(0,0,new QTableWidgetItem(map.value(1)));
     ui->tableWidget_Alarm->setItem(0,1,new QTableWidgetItem("N/A"));
     ui->tableWidget_Alarm->setItem(0,2,new QTableWidgetItem(map.value(2)));
     ui->tableWidget_Alarm->setItem(0,3,new QTableWidgetItem("N/A"));

     ui->tableWidget_Alarm->setItem(1,0,new QTableWidgetItem(map.value(3)));
     ui->tableWidget_Alarm->setItem(1,1,new QTableWidgetItem("N/A"));
}

void Moni_main::initServiceInfo(){
    QMap<int,QString> mapdata;

    mapdata.insert(1,tr("service_id"));
    mapdata.insert(2,tr("ServiceEvent"));
    mapdata.insert(3,tr("charging_event_timestamp"));
    mapdata.insert(4,tr("charging_connector_id"));
    mapdata.insert(5,tr("realtime_charged_energy"));
    mapdata.insert(6,tr("ChargingFinishResult"));
    mapdata.insert(7,tr("charged_energy_total"));

    int column = 4;
    int row = 3;
    ui->tableWidget_ServiceInfo->setColumnCount(column);
    ui->tableWidget_ServiceInfo->setRowCount(row);
    ui->tableWidget_ServiceInfo->horizontalHeader()->setHidden(true);
    ui->tableWidget_ServiceInfo->verticalHeader()->setHidden(true);
    ui->tableWidget_ServiceInfo->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget_ServiceInfo->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget_ServiceInfo->setEditTriggers(QAbstractItemView::NoEditTriggers); //设置不可编辑
    ui->tableWidget_ServiceInfo->setEditTriggers(QAbstractItemView::NoEditTriggers); //设置不可编辑

    ui->tableWidget_ServiceInfo->setItem(0,0,new QTableWidgetItem(mapdata.value(1)));
    ui->tableWidget_ServiceInfo->setItem(0,1,new QTableWidgetItem("N/A"));
    ui->tableWidget_ServiceInfo->setItem(0,2,new QTableWidgetItem(mapdata.value(2)));
    ui->tableWidget_ServiceInfo->setItem(0,3,new QTableWidgetItem("N/A"));

    ui->tableWidget_ServiceInfo->setItem(1,0,new QTableWidgetItem(mapdata.value(3)));
    ui->tableWidget_ServiceInfo->setItem(1,1,new QTableWidgetItem("N/A"));
    ui->tableWidget_ServiceInfo->setItem(1,2,new QTableWidgetItem(mapdata.value(4)));
    ui->tableWidget_ServiceInfo->setItem(1,3,new QTableWidgetItem("N/A"));

    ui->tableWidget_ServiceInfo->setItem(2,0,new QTableWidgetItem(mapdata.value(5)));
    ui->tableWidget_ServiceInfo->setItem(2,1,new QTableWidgetItem("N/A"));
    ui->tableWidget_ServiceInfo->setItem(2,2,new QTableWidgetItem(mapdata.value(6)));
    ui->tableWidget_ServiceInfo->setItem(2,3,new QTableWidgetItem("N/A"));

    ui->tableWidget_ServiceInfo->setItem(3,0,new QTableWidgetItem(mapdata.value(7)));
    ui->tableWidget_ServiceInfo->setItem(3,1,new QTableWidgetItem("N/A"));
}

void Moni_main::initLocalConfiguration(){
//    QMap<int,QString> mapdata;

//    mapdata.insert(1,tr("full"));
//    mapdata.insert(2,tr("configuration_key"));
//    mapdata.insert(3,tr("configuration_value"));
//    mapdata.insert(4,tr("LocalConfigurationInfoAccessType"));
//    mapdata.insert(5,tr("has_been_updated"));
//    mapdata.insert(6,tr("failureReason"));


//    int column = 4;
//    int row = 2;
//    ui->tableWidget_LocalConfiguration->setColumnCount(column);
//    ui->tableWidget_LocalConfiguration->setRowCount(row);
//    ui->tableWidget_LocalConfiguration->horizontalHeader()->setHidden(true);
//    ui->tableWidget_LocalConfiguration->verticalHeader()->setHidden(true);
//    ui->tableWidget_LocalConfiguration->horizontalHeader()->setStretchLastSection(true);
//    ui->tableWidget_LocalConfiguration->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

//    ui->tableWidget_LocalConfiguration->setItem(0,0,new QTableWidgetItem(mapdata.value(1)));
//    ui->tableWidget_LocalConfiguration->setItem(0,1,new QTableWidgetItem("N/A"));
//    ui->tableWidget_LocalConfiguration->setItem(0,2,new QTableWidgetItem(mapdata.value(2)));
//    ui->tableWidget_LocalConfiguration->setItem(0,3,new QTableWidgetItem("N/A"));

//    ui->tableWidget_LocalConfiguration->setItem(1,0,new QTableWidgetItem(mapdata.value(3)));
//    ui->tableWidget_LocalConfiguration->setItem(1,1,new QTableWidgetItem("N/A"));
//    ui->tableWidget_LocalConfiguration->setItem(1,2,new QTableWidgetItem(mapdata.value(4)));
//    ui->tableWidget_LocalConfiguration->setItem(1,3,new QTableWidgetItem("N/A"));

//    ui->tableWidget_LocalConfiguration->setItem(2,0,new QTableWidgetItem(mapdata.value(5)));
//    ui->tableWidget_LocalConfiguration->setItem(2,1,new QTableWidgetItem("N/A"));
//    ui->tableWidget_LocalConfiguration->setItem(2,2,new QTableWidgetItem(mapdata.value(6)));
//    ui->tableWidget_LocalConfiguration->setItem(2,3,new QTableWidgetItem("N/A"));

}


void Moni_main::on_pushButton_send_clicked()
{
    ui->textBrowser->clear();
    QByteArray array = QByteArray::fromHex( ui->textEdit_senddata->toPlainText().toUtf8());
    QMQTT::Message msg(Global_Param::getInstance().m_publishtopic.toInt(),Global_Param::getInstance().m_publish, array);
    _client->publish(msg);

}

void Moni_main::on_pushButton_sendclear_clicked()
{
    ui->textEdit_senddata->clear();
}
