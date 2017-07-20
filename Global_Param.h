#ifndef GLOBAL_PARAM_H
#define GLOBAL_PARAM_H

#include <QObject>
#include <QLabel>
#include <QPainter>
#include <QLineEdit>
#include <QString>
#include <QTextCodec>
#include <string>
#include "Protobuf/messageall.pb.h"

struct ParamType_Proto{
    QString ParamType_Proto_key;
    QString ParamType_Proto_value;
};

struct Message_Proto{
    QString version;
    QString id;
    QString publish_ts;
    QString ttl;
    Message_MessageType type;
    QString sub_type;
    ParamType_Proto params;
};

struct ServiceStateInfo_Proto {
    ServiceState service_state;
    ServiceStateReason service_state_reason;
};

struct CommonBasicInfo_Proto{
    QString software_version;
    QString hardware_version;
    ServiceStateInfo_Proto service_state_info;
};

struct BasicInfo_Proto{
    CommonBasicInfo_Proto common_basic_info;
    ACPowerCharger_PowerChargerType power_charger_type;
    QString charging_connector_quantity;
    QString power;
};

struct ConnectivityState_Proto {
    NetworkOperator network_operator;
    NetworkType network_type;
};

//struct DeviceState_Proto {
//    DeviceWorkState device_work_state;
//    DeviceFaultState device_fault_state;
//};

struct ChargingConnector_Proto {
    QString charging_connector_id;
    ChargingConnectorWorkState charging_connector_work_state;
    ChargingConnectorConnectionState charging_connector_connection_state;
    ChargingConnectorFaultState charging_connector_fault_state;
    PowerChargerConnectorOutputType power_charger_connector_output_type; //针对交流充电桩
    PowerChargerConnectorOutputVoltage power_charger_connector_rated_output_voltage;
    QString power_charger_connector_rated_output_power;
    QString realtime_output_voltage;
    QString realtime_output_current;
 // QString output_power;
};

struct RealtimeInfo_Proto{
    ConnectivityState_Proto connectivity_state;
    ACPowerCharger_DeviceWorkState device_work_state;
    ChargingConnector_Proto charging_connector;
};

struct Alarm_Proto{
    QString alarm_type_id;
    QString alarm_timestamp; //消息发送的时间戳，采用UNIX时间，精确到毫秒
    AlarmState alarm_state;
};

struct ServiceInfo_Proto{
    QString service_id;
    ServiceEvent service_event;
    QString charging_event_timestamp;
    QString charging_connector_id;
    QString realtime_charged_energy;
    ServiceFinishResult service_finish_result;
    QString charged_energy_total;

};

// 配置项
struct LocalConfigurationInfo_Proto{
    QString configuration_key; //设备-->云， 云-->设备 [约束规则：not_null, not_empty]
    QString configuration_value; //设备-->云， 云-->设备

    LocalConfigurationInfoAccessType local_configuration_info_access_type; //仅限设备-->云

    QString has_been_updated; //该值是否成功更新, 仅限设备-->云
    QString failureReason;
};

struct LocalConfiguration_Proto {
    QString full; // 标识上传的是否是全量配置，若不提供，则认为是增量上传。
    LocalConfigurationInfo_Proto configuration_info; // [约束规则：not_empty]
};


struct ACPowerCharger_Proto{
    QString device_id;
    QString message_timestamp;
    BasicInfo_Proto basicinfo;
    RealtimeInfo_Proto realtime_info;
    Alarm_Proto alarm;
    ServiceInfo_Proto service_info;
    LocalConfiguration_Proto LocalConfiguration_info;
};


// 配置项
struct RemoteConfigurationInfo_Proto{
     QString configuration_key;
     QString configuration_value;
};

// 远程配置列表，由云传给设备
struct RemoteConfiguration_Proto {
     QString request_id; //required
     RemoteConfigurationInfo_Proto remote_configuration_info;
};

struct RemoteControlParam_Proto {
     QString key;
     QString value;
};

// 远程控制，由云传给设备
struct RemoteControl_Proto {
     QString request_id; //required
     RemoteControlCommand remote_control_command;
     RemoteControlParam_Proto remote_control_param; // “开始充电”时可以指定充电策略，默认为自然充电。key为“1”时指定秒数；key为“2”时指定度数。
};

struct RemoteUpgrade_Proto {
     QString request_id;
     QString software_version;
     QString ftp_address;
    //TODO: add more when solution is concluded
};

struct RemoteOperation_Proto {
     QString message_timestamp; //required 消息发送的时间戳，采用UNIX时间，精确到毫秒

     RemoteConfiguration_Proto remote_configuration; //远程配置
     RemoteControl_Proto remote_control; //远程控制
     RemoteUpgrade_Proto remote_upgrade; //远程升级
};

// 远程配置响应，由设备传给云
struct RemoteConfigurationResponse_Ptoyo {
     QString request_id; //required 这个值需要和RemoteConfiguration消息中的request_id匹配 [约束规则：not_null, not_empty]
     QString device_id; // [约束规则：not_null, not_empty]
     RemoteConfigurationResponseType remote_configuration_response_type;
     QString failureReason;
     LocalConfigurationInfo_Proto configuration_info; //将更新后的配置信息列表传给云，仅传已经变更的。
};

struct RemoteUpgradeResponse_Ptoyo {
     QString request_id; // [约束规则：not_null, not_empty]
     QString device_id; // [约束规则：not_null, not_empty]
    //TODO: add more when solution is concluded
};

// 远程控制响应，由设备传给云
struct RemoteControlResponse_Ptoyo {
     QString request_id; //required 这个值需要和RemoteControl消息中的request_id匹配 [约束规则：not_null, not_empty]
     QString device_id; // [约束规则：not_null, not_empty]
     RemoteControlResponseType remote_control_response_type;
     QString failureReason;
};

struct RemoteOperationResponse_Ptoyo{
    RemoteConfigurationResponse_Ptoyo remote_configuration_response;
    RemoteControlResponse_Ptoyo remote_control_response;
    RemoteUpgradeResponse_Ptoyo remote_upgrade_response;
};



//管理全局变量和接口的类
class Global_Param
{
    public:
        static Global_Param& getInstance()
        {
            static Global_Param instance;
            return instance;
        }
    private:
        Global_Param(){
        };
        Global_Param(Global_Param const&);
        void operator=(Global_Param const&);

public:
    Message_Proto message;
    ACPowerCharger_Proto ACpowercharger;
    RemoteOperation_Proto RemoteOperation;
    RemoteOperationResponse_Ptoyo RemoteOperationResponse;
    void InitData();
    QString m_publish;
    QString m_publishtopic;
    bool m_base64;

};

#endif // GLOBAL_PARAM_H
