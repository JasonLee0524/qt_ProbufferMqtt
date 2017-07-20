#include "Global_Param.h"
#include <QDebug>


void Global_Param::InitData(){

    Global_Param::getInstance().message.version = "1";
    Global_Param::getInstance().message.id = "is is cool";
    Global_Param::getInstance().message.publish_ts = "3";
    Global_Param::getInstance().message.ttl = "4";
    Global_Param::getInstance().message.type = Message_MessageType_CONTROL_COMMAND;
    Global_Param::getInstance().message.sub_type = "is is liyz";
    Global_Param::getInstance().message.params.ParamType_Proto_key = "ACPowerCharger";

    //RemoteOperation
    Global_Param::getInstance().RemoteOperation.message_timestamp = "1020";
    //RemoteConfiguration
    Global_Param::getInstance().RemoteOperation.remote_configuration.request_id = "liyuzhe";
    Global_Param::getInstance().RemoteOperation.remote_configuration.remote_configuration_info.configuration_key = "configuration_key";
    Global_Param::getInstance().RemoteOperation.remote_configuration.remote_configuration_info.configuration_value = "configuration_value";
    //RemoteControl
    Global_Param::getInstance().RemoteOperation.remote_control.request_id = "request_id";
    Global_Param::getInstance().RemoteOperation.remote_control.remote_control_command = RCC_ENABLE_CONNECTOR;
    Global_Param::getInstance().RemoteOperation.remote_control.remote_control_param.key = "key";
    Global_Param::getInstance().RemoteOperation.remote_control.remote_control_param.value = "value";
    //RemoteUpgrade
    Global_Param::getInstance().RemoteOperation.remote_upgrade.request_id = "request_id";
    Global_Param::getInstance().RemoteOperation.remote_upgrade.software_version = "software_version";
    Global_Param::getInstance().RemoteOperation.remote_upgrade.ftp_address = "ftp_address";


    //ACpowercharger
    Global_Param::getInstance().ACpowercharger.device_id = "tseet";
    Global_Param::getInstance().ACpowercharger.message_timestamp = "1234";

    //Alarm
    Global_Param::getInstance().ACpowercharger.alarm.alarm_type_id = "111";
    Global_Param::getInstance().ACpowercharger.alarm.alarm_timestamp = "1234";
    Global_Param::getInstance().ACpowercharger.alarm.alarm_state = AS_INACTIVE;

    //basicinfo
    Global_Param::getInstance().ACpowercharger.basicinfo.power_charger_type = ACPowerCharger_PowerChargerType_PCT_DC_ONLY;
    Global_Param::getInstance().ACpowercharger.basicinfo.charging_connector_quantity = "2";
    Global_Param::getInstance().ACpowercharger.basicinfo.power = "1.23";
    Global_Param::getInstance().ACpowercharger.basicinfo.common_basic_info.software_version = "2017soft";
    Global_Param::getInstance().ACpowercharger.basicinfo.common_basic_info.hardware_version = "2017hard";
    Global_Param::getInstance().ACpowercharger.basicinfo.common_basic_info.service_state_info.service_state = SS_WAITING;
    Global_Param::getInstance().ACpowercharger.basicinfo.common_basic_info.service_state_info.service_state_reason = SSR_ALTERNATIVE_TRANSLATIONS;

    //realtime_info
    Global_Param::getInstance().ACpowercharger.realtime_info.connectivity_state.network_operator = NO_CHINA_MOBILE;
    Global_Param::getInstance().ACpowercharger.realtime_info.connectivity_state.network_type = NT_RADIO_4G;
    Global_Param::getInstance().ACpowercharger.realtime_info.device_work_state= ACPowerCharger_DeviceWorkState_DWS_IN_CHARGING;
    Global_Param::getInstance().ACpowercharger.realtime_info.charging_connector.charging_connector_id = "999test";
    Global_Param::getInstance().ACpowercharger.realtime_info.charging_connector.charging_connector_work_state = CCWS_IN_CHARGING;
    Global_Param::getInstance().ACpowercharger.realtime_info.charging_connector.charging_connector_connection_state = CCCS_DISCONNECTED;
    Global_Param::getInstance().ACpowercharger.realtime_info.charging_connector.charging_connector_fault_state = CCFS_HAVING_FAULT;
    Global_Param::getInstance().ACpowercharger.realtime_info.charging_connector.power_charger_connector_output_type = COT_7_PIN;
    Global_Param::getInstance().ACpowercharger.realtime_info.charging_connector.power_charger_connector_rated_output_voltage = COV_500V;
    Global_Param::getInstance().ACpowercharger.realtime_info.charging_connector.power_charger_connector_rated_output_power = "2.01";
    Global_Param::getInstance().ACpowercharger.realtime_info.charging_connector.realtime_output_voltage = "10.02";
    Global_Param::getInstance().ACpowercharger.realtime_info.charging_connector.realtime_output_current = "100.23";

    //ServiceInfo
    Global_Param::getInstance().ACpowercharger.service_info.service_id = "sfjwior";
    Global_Param::getInstance().ACpowercharger.service_info.service_event = SE_FINISH;
    Global_Param::getInstance().ACpowercharger.service_info.charging_event_timestamp = "12";
    Global_Param::getInstance().ACpowercharger.service_info.charging_connector_id = "alsfj";
    Global_Param::getInstance().ACpowercharger.service_info.realtime_charged_energy = "2.01";
    Global_Param::getInstance().ACpowercharger.service_info.service_finish_result = SFR_ERROR;
    Global_Param::getInstance().ACpowercharger.service_info.charged_energy_total = "3.01";

    //LocalConfiguration_info
    Global_Param::getInstance().ACpowercharger.LocalConfiguration_info.full = "1";
    Global_Param::getInstance().ACpowercharger.LocalConfiguration_info.configuration_info.configuration_key = "configuration_key222";
    Global_Param::getInstance().ACpowercharger.LocalConfiguration_info.configuration_info.configuration_value = "10";
    Global_Param::getInstance().ACpowercharger.LocalConfiguration_info.configuration_info.local_configuration_info_access_type = LCIAT_READWRITE;
    Global_Param::getInstance().ACpowercharger.LocalConfiguration_info.configuration_info.has_been_updated = "1";
    Global_Param::getInstance().ACpowercharger.LocalConfiguration_info.configuration_info.failureReason = "failureReason1111";

    //RemoteOperationResponse
    Global_Param::getInstance().RemoteOperationResponse.remote_configuration_response.request_id = "request_id1";
    Global_Param::getInstance().RemoteOperationResponse.remote_configuration_response.device_id = "device_id1";
    Global_Param::getInstance().RemoteOperationResponse.remote_configuration_response.remote_configuration_response_type = RCONFRT_FINISHED_FAILED;
    Global_Param::getInstance().RemoteOperationResponse.remote_configuration_response.failureReason = "failureReason1";
    Global_Param::getInstance().RemoteOperationResponse.remote_configuration_response.configuration_info = Global_Param::getInstance().ACpowercharger.LocalConfiguration_info.configuration_info;

    Global_Param::getInstance().RemoteOperationResponse.remote_control_response.request_id = "request_id2";
    Global_Param::getInstance().RemoteOperationResponse.remote_control_response.device_id = "device_id2";
    Global_Param::getInstance().RemoteOperationResponse.remote_control_response.remote_control_response_type = RCONTRT_FINISHED_FAILED;
    Global_Param::getInstance().RemoteOperationResponse.remote_control_response.failureReason = "failureReason2";

    Global_Param::getInstance().RemoteOperationResponse.remote_upgrade_response.request_id = "request_id3";
    Global_Param::getInstance().RemoteOperationResponse.remote_upgrade_response.device_id = "device_id3";

}

