#include "ACPowerChargerDialog.h"
#include "ui_ACPowerChargerDialog.h"
#include "Global_Param.h"
#include <QDesktopWidget>

ACPowerChargerDialog::ACPowerChargerDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ACPowerChargerDialog)
{
    ui->setupUi(this);
    initUI();

    m_ACPowerChargerData.Clear();
    if(ui->checkBox_device_id->isChecked()){
        m_ACPowerChargerData.set_device_id(Global_Param::getInstance().ACpowercharger.device_id.toUtf8());
    }
    if(ui->checkBox_message_timestamp->isChecked()){
        m_ACPowerChargerData.set_message_timestamp(Global_Param::getInstance().ACpowercharger.message_timestamp.toInt());
    }
    if(ui->checkBox_BasicInfo->isChecked()){
        ACPowerCharger_BasicInfo* basicinfo = m_ACPowerChargerData.mutable_basicinfo();
        if(m_BasicInfoDialog->Get_checkBox_power_charger_type())
            basicinfo->set_power_charger_type(Global_Param::getInstance().ACpowercharger.basicinfo.power_charger_type);
        if(m_BasicInfoDialog->Get_checkBox_charging_connector_quantity())
            basicinfo->set_charging_connector_quantity(Global_Param::getInstance().ACpowercharger.basicinfo.charging_connector_quantity.toInt());
        if(m_BasicInfoDialog->Get_checkBox_power())
            basicinfo->set_power(Global_Param::getInstance().ACpowercharger.basicinfo.power.toFloat());

        if(m_BasicInfoDialog->Get_checkBox_CommonBasicInfo()){
            CommonBasicInfo* commoninfo = basicinfo->mutable_common_basic_info();
            if(m_BasicInfoDialog->Get_checkBox_software_version())
                commoninfo->set_software_version(Global_Param::getInstance().ACpowercharger.basicinfo.common_basic_info.software_version.toUtf8());
            if(m_BasicInfoDialog->Get_checkBox_hardware_version())
                commoninfo->set_hardware_version(Global_Param::getInstance().ACpowercharger.basicinfo.common_basic_info.hardware_version.toUtf8());

            if(m_BasicInfoDialog->Get_checkBox_ServiceStateInfo()){
                ServiceStateInfo* servicestateinfo = commoninfo->mutable_service_state_info();
                if(m_BasicInfoDialog->Get_checkBox_ServiceState())
                    servicestateinfo->set_service_state(Global_Param::getInstance().ACpowercharger.basicinfo.common_basic_info.service_state_info.service_state);
                if(m_BasicInfoDialog->Get_checkBox_ServiceStateReason())
                    servicestateinfo->set_service_state_reason(Global_Param::getInstance().ACpowercharger.basicinfo.common_basic_info.service_state_info.service_state_reason);
            }
        }
    }

    if(ui->checkBox_RealtimeInfo->isChecked()){
        ACPowerCharger_RealtimeInfo* realtimeinfo = m_ACPowerChargerData.mutable_realtime_info();
        if(m_RealtimeInfoDialog->Get_checkBox_ConnectivityState()){
            ConnectivityState* ConnectivityStateinfo = realtimeinfo->mutable_connectivity_state();
            if(m_RealtimeInfoDialog->Get_checkBox_NetworkOperator())
                ConnectivityStateinfo->set_network_operator(Global_Param::getInstance().ACpowercharger.realtime_info.connectivity_state.network_operator);
            if(m_RealtimeInfoDialog->Get_checkBox_NetworkType())
                ConnectivityStateinfo->set_network_type(Global_Param::getInstance().ACpowercharger.realtime_info.connectivity_state.network_type);
        }

        if(m_RealtimeInfoDialog->Get_checkBox_DeviceWorkState())
               realtimeinfo->set_device_work_state(Global_Param::getInstance().ACpowercharger.realtime_info.device_work_state);

        if(m_RealtimeInfoDialog->Get_checkBox_ChargingConnector()){
            ChargingConnector* ChargingConnectorinfo = realtimeinfo->add_charging_connector();

            if(m_RealtimeInfoDialog->Get_checkBox_charging_connector_id())
                ChargingConnectorinfo->set_charging_connector_id(Global_Param::getInstance().ACpowercharger.realtime_info.charging_connector.charging_connector_id.toUtf8());
            if(m_RealtimeInfoDialog->Get_checkBox_ChargingConnectorWorkState())
                ChargingConnectorinfo->set_charging_connector_work_state(Global_Param::getInstance().ACpowercharger.realtime_info.charging_connector.charging_connector_work_state);
            if(m_RealtimeInfoDialog->Get_checkBox_ChargingConnectorConnectionState())
                ChargingConnectorinfo->set_charging_connector_connection_state(Global_Param::getInstance().ACpowercharger.realtime_info.charging_connector.charging_connector_connection_state);
            if(m_RealtimeInfoDialog->Get_checkBox_ChargingConnectorFaultState())
                ChargingConnectorinfo->set_charging_connector_fault_state(Global_Param::getInstance().ACpowercharger.realtime_info.charging_connector.charging_connector_fault_state);
            if(m_RealtimeInfoDialog->Get_checkBox_PowerChargerConnectorOutputType())
                ChargingConnectorinfo->set_power_charger_connector_output_type(Global_Param::getInstance().ACpowercharger.realtime_info.charging_connector.power_charger_connector_output_type);
            if(m_RealtimeInfoDialog->Get_checkBox_PowerChargerConnectorOutputVoltage())
                ChargingConnectorinfo->set_power_charger_connector_rated_output_voltage(Global_Param::getInstance().ACpowercharger.realtime_info.charging_connector.power_charger_connector_rated_output_voltage);
            if(m_RealtimeInfoDialog->Get_checkBox_power_charger_connector_rated_output_power())
                ChargingConnectorinfo->set_power_charger_connector_rated_output_power(Global_Param::getInstance().ACpowercharger.realtime_info.charging_connector.power_charger_connector_rated_output_power.toFloat());
            if(m_RealtimeInfoDialog->Get_checkBox_realtime_output_voltage())
                ChargingConnectorinfo->set_realtime_output_voltage(Global_Param::getInstance().ACpowercharger.realtime_info.charging_connector.realtime_output_voltage.toFloat());
            if(m_RealtimeInfoDialog->Get_checkBox_realtime_output_current())
                ChargingConnectorinfo->set_realtime_output_current(Global_Param::getInstance().ACpowercharger.realtime_info.charging_connector.realtime_output_current.toFloat());

        }
    }
    if(ui->checkBox_Alarm->isChecked()){
        Alarm* alarms = m_ACPowerChargerData.add_alarms();
        if(m_AlarmDialog->Get_checkBox_alarm_type_id())
            alarms->set_alarm_type_id(Global_Param::getInstance().ACpowercharger.alarm.alarm_type_id.toInt());
        if(m_AlarmDialog->Get_checkBox_alarm_timestamp())
            alarms->set_alarm_timestamp(Global_Param::getInstance().ACpowercharger.alarm.alarm_timestamp.toInt());
        if(m_AlarmDialog->Get_checkBox_alarm_state())
            alarms->set_alarm_state(Global_Param::getInstance().ACpowercharger.alarm.alarm_state);
    }
    if(ui->checkBox_ServiceInfo->isChecked()){
        ACPowerCharger_ServiceInfo* serviceinfo = m_ACPowerChargerData.add_service_info();
        if(m_ServiceInfoDialog->Get_checkBox_ServiceEvent())
            serviceinfo->set_service_event(Global_Param::getInstance().ACpowercharger.service_info.service_event);
        if(m_ServiceInfoDialog->Get_checkBox_charging_event_timestamp())
            serviceinfo->set_charging_event_timestamp(Global_Param::getInstance().ACpowercharger.service_info.charging_event_timestamp.toInt());
        if(m_ServiceInfoDialog->Get_checkBox_service_id())
            serviceinfo->set_service_id(Global_Param::getInstance().ACpowercharger.service_info.service_id.toUtf8());
        if(m_ServiceInfoDialog->Get_checkBox_charging_connector_id())
            serviceinfo->set_charging_connector_id(Global_Param::getInstance().ACpowercharger.service_info.charging_connector_id.toUtf8());
        if(m_ServiceInfoDialog->Get_checkBox_realtime_charged_energy())
            serviceinfo->set_realtime_charged_energy(Global_Param::getInstance().ACpowercharger.service_info.realtime_charged_energy.toFloat());
        if(m_ServiceInfoDialog->Get_checkBox_charged_energy_total())
            serviceinfo->set_charged_energy_total(Global_Param::getInstance().ACpowercharger.service_info.charged_energy_total.toFloat());
        if(m_ServiceInfoDialog->Get_checkBox_ServiceFinishResult())
            serviceinfo->set_service_finish_result(Global_Param::getInstance().ACpowercharger.service_info.service_finish_result);
    }
    if(ui->checkBox_LocalConfiguration->isChecked()){
        LocalConfiguration* LocalConfiguration_data = m_ACPowerChargerData.mutable_local_configuration();
        if(m_LocalConfigurationDialog->Get_checkBox_full())
            LocalConfiguration_data->set_full(Global_Param::getInstance().ACpowercharger.LocalConfiguration_info.full.toInt());
        if(m_LocalConfigurationDialog->Get_checkBox_LocalConfigurationInfo())
        {
            LocalConfigurationInfo* LocalConfigurationInfo_data = LocalConfiguration_data->add_configuration_info();
            if(m_LocalConfigurationDialog->Get_checkBox_configuration_key())
                LocalConfigurationInfo_data->set_configuration_key(Global_Param::getInstance().ACpowercharger.LocalConfiguration_info.configuration_info.configuration_key.toUtf8());
            if(m_LocalConfigurationDialog->Get_checkBox_configuration_value())
                LocalConfigurationInfo_data->set_configuration_value(Global_Param::getInstance().ACpowercharger.LocalConfiguration_info.configuration_info.configuration_value.toUtf8());
            if(m_LocalConfigurationDialog->Get_checkBox_LocalConfigurationInfoAccessType())
                LocalConfigurationInfo_data->set_local_configuration_info_access_type(Global_Param::getInstance().ACpowercharger.LocalConfiguration_info.configuration_info.local_configuration_info_access_type);
            if(m_LocalConfigurationDialog->Get_checkBox_has_been_updated())
                LocalConfigurationInfo_data->set_has_been_updated(Global_Param::getInstance().ACpowercharger.LocalConfiguration_info.configuration_info.has_been_updated.toInt());
            if(m_LocalConfigurationDialog->Get_checkBox_failureReason())
                LocalConfigurationInfo_data->set_failurereason(Global_Param::getInstance().ACpowercharger.LocalConfiguration_info.configuration_info.failureReason.toUtf8());
        }
    }
}

ACPowerChargerDialog::~ACPowerChargerDialog()
{
    delete ui;
}

void ACPowerChargerDialog::initUI(){

    m_AlarmDialog = NULL;
    m_BasicInfoDialog = NULL;
    m_RealtimeInfoDialog = NULL;
    m_ServiceInfoDialog = NULL;
    m_LocalConfigurationDialog = NULL;
 //   m_RemoteOperationResponseDialog = NULL;

    m_BasicInfoDialog = new BasicInfoDialog(this);
    m_RealtimeInfoDialog = new RealtimeInfoDialog(this);
    m_ServiceInfoDialog = new ServiceInfoDialog(this);
    m_AlarmDialog = new AlarmDialog(this);
    m_LocalConfigurationDialog = new LocalConfigurationDialog(this);
 //   m_RemoteOperationResponseDialog = new RemoteOperationResponseDialog(this);

    ui->checkBox_device_id->setChecked(true);
    ui->checkBox_message_timestamp->setChecked(true);
    ui->checkBox_BasicInfo->setChecked(true);
    ui->checkBox_RealtimeInfo->setChecked(true);
    ui->checkBox_Alarm->setChecked(true);
    ui->checkBox_ServiceInfo->setChecked(true);
    ui->checkBox_LocalConfiguration->setChecked(true);

    ui->lineEdit_device_id->setText(Global_Param::getInstance().ACpowercharger.device_id);
    ui->lineEdit_message_timestamp->setText(Global_Param::getInstance().ACpowercharger.message_timestamp);

}

void ACPowerChargerDialog::on_pushButton_BasicInfo_clicked()
{
    m_BasicInfoDialog->show();
    m_BasicInfoDialog->move ((QApplication::desktop()->width() - this->width())/2,(QApplication::desktop()->height() - this->height())/2);
     m_BasicInfoDialog->setFixedSize(800,600);
}

void ACPowerChargerDialog::on_pushButton_RealtimeInfo_clicked()
{
    m_RealtimeInfoDialog->show();
    m_RealtimeInfoDialog->move ((QApplication::desktop()->width() - this->width())/2,(QApplication::desktop()->height() - this->height())/2);
    m_RealtimeInfoDialog->setFixedSize(800,600);
}

void ACPowerChargerDialog::on_pushButton_ServiceInfo_clicked()
{
    m_ServiceInfoDialog->show();
    m_ServiceInfoDialog->move ((QApplication::desktop()->width() - this->width())/2,(QApplication::desktop()->height() - this->height())/2);
    m_ServiceInfoDialog->setFixedSize(800,600);
}

void ACPowerChargerDialog::on_pushButton_Alarm_clicked()
{
    m_AlarmDialog->show();
    m_AlarmDialog->move ((QApplication::desktop()->width() - this->width())/2,(QApplication::desktop()->height() - this->height())/2);
    m_AlarmDialog->setFixedSize(800,600);
}

void ACPowerChargerDialog::on_pushButton_LocalConfiguration_clicked()
{
    m_LocalConfigurationDialog->show();
    m_LocalConfigurationDialog->move ((QApplication::desktop()->width() - this->width())/2,(QApplication::desktop()->height() - this->height())/2);
    m_LocalConfigurationDialog->setFixedSize(800,600);
}


void ACPowerChargerDialog::on_pushButton_save_clicked()
{
    m_ACPowerChargerData.Clear();

    if(ui->checkBox_device_id->isChecked()){
        Global_Param::getInstance().ACpowercharger.device_id = ui->lineEdit_device_id->text();
        m_ACPowerChargerData.set_device_id(Global_Param::getInstance().ACpowercharger.device_id.toUtf8());
    }
    if(ui->checkBox_message_timestamp->isChecked()){
        Global_Param::getInstance().ACpowercharger.message_timestamp = ui->lineEdit_message_timestamp->text();
        m_ACPowerChargerData.set_message_timestamp(Global_Param::getInstance().ACpowercharger.message_timestamp.toInt());
    }
    if(ui->checkBox_BasicInfo->isChecked()){
        ACPowerCharger_BasicInfo* basicinfo = m_ACPowerChargerData.mutable_basicinfo();
        if(m_BasicInfoDialog->Get_checkBox_power_charger_type())
            basicinfo->set_power_charger_type(Global_Param::getInstance().ACpowercharger.basicinfo.power_charger_type);
        if(m_BasicInfoDialog->Get_checkBox_charging_connector_quantity())
            basicinfo->set_charging_connector_quantity(Global_Param::getInstance().ACpowercharger.basicinfo.charging_connector_quantity.toInt());
        if(m_BasicInfoDialog->Get_checkBox_power())
            basicinfo->set_power(Global_Param::getInstance().ACpowercharger.basicinfo.power.toFloat());

        if(m_BasicInfoDialog->Get_checkBox_CommonBasicInfo()){
            CommonBasicInfo* commoninfo = basicinfo->mutable_common_basic_info();
            if(m_BasicInfoDialog->Get_checkBox_software_version())
                commoninfo->set_software_version(Global_Param::getInstance().ACpowercharger.basicinfo.common_basic_info.software_version.toUtf8());
            if(m_BasicInfoDialog->Get_checkBox_hardware_version())
                commoninfo->set_hardware_version(Global_Param::getInstance().ACpowercharger.basicinfo.common_basic_info.hardware_version.toUtf8());

            if(m_BasicInfoDialog->Get_checkBox_ServiceStateInfo()){
                ServiceStateInfo* servicestateinfo = commoninfo->mutable_service_state_info();
                if(m_BasicInfoDialog->Get_checkBox_ServiceState())
                    servicestateinfo->set_service_state(Global_Param::getInstance().ACpowercharger.basicinfo.common_basic_info.service_state_info.service_state);
                if(m_BasicInfoDialog->Get_checkBox_ServiceStateReason())
                    servicestateinfo->set_service_state_reason(Global_Param::getInstance().ACpowercharger.basicinfo.common_basic_info.service_state_info.service_state_reason);
            }
        }
    }

    if(ui->checkBox_RealtimeInfo->isChecked()){
        ACPowerCharger_RealtimeInfo* realtimeinfo = m_ACPowerChargerData.mutable_realtime_info();
        if(m_RealtimeInfoDialog->Get_checkBox_ConnectivityState()){
            ConnectivityState* ConnectivityStateinfo = realtimeinfo->mutable_connectivity_state();
            if(m_RealtimeInfoDialog->Get_checkBox_NetworkOperator())
                ConnectivityStateinfo->set_network_operator(Global_Param::getInstance().ACpowercharger.realtime_info.connectivity_state.network_operator);
            if(m_RealtimeInfoDialog->Get_checkBox_NetworkType())
                ConnectivityStateinfo->set_network_type(Global_Param::getInstance().ACpowercharger.realtime_info.connectivity_state.network_type);
        }

        if(m_RealtimeInfoDialog->Get_checkBox_DeviceWorkState())
               realtimeinfo->set_device_work_state(Global_Param::getInstance().ACpowercharger.realtime_info.device_work_state);

        if(m_RealtimeInfoDialog->Get_checkBox_ChargingConnector()){
            ChargingConnector* ChargingConnectorinfo = realtimeinfo->add_charging_connector();

            if(m_RealtimeInfoDialog->Get_checkBox_charging_connector_id())
                ChargingConnectorinfo->set_charging_connector_id(Global_Param::getInstance().ACpowercharger.realtime_info.charging_connector.charging_connector_id.toUtf8());
            if(m_RealtimeInfoDialog->Get_checkBox_ChargingConnectorWorkState())
                ChargingConnectorinfo->set_charging_connector_work_state(Global_Param::getInstance().ACpowercharger.realtime_info.charging_connector.charging_connector_work_state);
            if(m_RealtimeInfoDialog->Get_checkBox_ChargingConnectorConnectionState())
                ChargingConnectorinfo->set_charging_connector_connection_state(Global_Param::getInstance().ACpowercharger.realtime_info.charging_connector.charging_connector_connection_state);
            if(m_RealtimeInfoDialog->Get_checkBox_ChargingConnectorFaultState())
                ChargingConnectorinfo->set_charging_connector_fault_state(Global_Param::getInstance().ACpowercharger.realtime_info.charging_connector.charging_connector_fault_state);
            if(m_RealtimeInfoDialog->Get_checkBox_PowerChargerConnectorOutputType())
                ChargingConnectorinfo->set_power_charger_connector_output_type(Global_Param::getInstance().ACpowercharger.realtime_info.charging_connector.power_charger_connector_output_type);
            if(m_RealtimeInfoDialog->Get_checkBox_PowerChargerConnectorOutputVoltage())
                ChargingConnectorinfo->set_power_charger_connector_rated_output_voltage(Global_Param::getInstance().ACpowercharger.realtime_info.charging_connector.power_charger_connector_rated_output_voltage);
            if(m_RealtimeInfoDialog->Get_checkBox_power_charger_connector_rated_output_power())
                ChargingConnectorinfo->set_power_charger_connector_rated_output_power(Global_Param::getInstance().ACpowercharger.realtime_info.charging_connector.power_charger_connector_rated_output_power.toFloat());
            if(m_RealtimeInfoDialog->Get_checkBox_realtime_output_voltage())
                ChargingConnectorinfo->set_realtime_output_voltage(Global_Param::getInstance().ACpowercharger.realtime_info.charging_connector.realtime_output_voltage.toFloat());
            if(m_RealtimeInfoDialog->Get_checkBox_realtime_output_current())
                ChargingConnectorinfo->set_realtime_output_current(Global_Param::getInstance().ACpowercharger.realtime_info.charging_connector.realtime_output_current.toFloat());

        }
    }
    if(ui->checkBox_Alarm->isChecked()){
        Alarm* alarms = m_ACPowerChargerData.add_alarms();
        if(m_AlarmDialog->Get_checkBox_alarm_type_id())
            alarms->set_alarm_type_id(Global_Param::getInstance().ACpowercharger.alarm.alarm_type_id.toInt());
        if(m_AlarmDialog->Get_checkBox_alarm_timestamp())
            alarms->set_alarm_timestamp(Global_Param::getInstance().ACpowercharger.alarm.alarm_timestamp.toInt());
        if(m_AlarmDialog->Get_checkBox_alarm_state())
            alarms->set_alarm_state(Global_Param::getInstance().ACpowercharger.alarm.alarm_state);
    }
    if(ui->checkBox_ServiceInfo->isChecked()){
        ACPowerCharger_ServiceInfo* serviceinfo = m_ACPowerChargerData.add_service_info();
        if(m_ServiceInfoDialog->Get_checkBox_ServiceEvent())
            serviceinfo->set_service_event(Global_Param::getInstance().ACpowercharger.service_info.service_event);
        if(m_ServiceInfoDialog->Get_checkBox_charging_event_timestamp())
            serviceinfo->set_charging_event_timestamp(Global_Param::getInstance().ACpowercharger.service_info.charging_event_timestamp.toInt());
        if(m_ServiceInfoDialog->Get_checkBox_service_id())
            serviceinfo->set_service_id(Global_Param::getInstance().ACpowercharger.service_info.service_id.toUtf8());
        if(m_ServiceInfoDialog->Get_checkBox_charging_connector_id())
            serviceinfo->set_charging_connector_id(Global_Param::getInstance().ACpowercharger.service_info.charging_connector_id.toUtf8());
        if(m_ServiceInfoDialog->Get_checkBox_realtime_charged_energy())
            serviceinfo->set_realtime_charged_energy(Global_Param::getInstance().ACpowercharger.service_info.realtime_charged_energy.toFloat());
        if(m_ServiceInfoDialog->Get_checkBox_charged_energy_total())
            serviceinfo->set_charged_energy_total(Global_Param::getInstance().ACpowercharger.service_info.charged_energy_total.toFloat());
        if(m_ServiceInfoDialog->Get_checkBox_ServiceFinishResult())
            serviceinfo->set_service_finish_result(Global_Param::getInstance().ACpowercharger.service_info.service_finish_result);
    }

    if(ui->checkBox_LocalConfiguration->isChecked()){
        LocalConfiguration* LocalConfiguration_data = m_ACPowerChargerData.mutable_local_configuration();
        if(m_LocalConfigurationDialog->Get_checkBox_full())
            LocalConfiguration_data->set_full(Global_Param::getInstance().ACpowercharger.LocalConfiguration_info.full.toInt());
        if(m_LocalConfigurationDialog->Get_checkBox_LocalConfigurationInfo())
        {
            LocalConfigurationInfo* LocalConfigurationInfo_data = LocalConfiguration_data->add_configuration_info();
            if(m_LocalConfigurationDialog->Get_checkBox_configuration_key())
                LocalConfigurationInfo_data->set_configuration_key(Global_Param::getInstance().ACpowercharger.LocalConfiguration_info.configuration_info.configuration_key.toUtf8());
            if(m_LocalConfigurationDialog->Get_checkBox_configuration_value())
                LocalConfigurationInfo_data->set_configuration_value(Global_Param::getInstance().ACpowercharger.LocalConfiguration_info.configuration_info.configuration_value.toUtf8());
            if(m_LocalConfigurationDialog->Get_checkBox_LocalConfigurationInfoAccessType())
                LocalConfigurationInfo_data->set_local_configuration_info_access_type(Global_Param::getInstance().ACpowercharger.LocalConfiguration_info.configuration_info.local_configuration_info_access_type);
            if(m_LocalConfigurationDialog->Get_checkBox_has_been_updated())
                LocalConfigurationInfo_data->set_has_been_updated(Global_Param::getInstance().ACpowercharger.LocalConfiguration_info.configuration_info.has_been_updated.toInt());
            if(m_LocalConfigurationDialog->Get_checkBox_failureReason())
                LocalConfigurationInfo_data->set_failurereason(Global_Param::getInstance().ACpowercharger.LocalConfiguration_info.configuration_info.failureReason.toUtf8());
        }
    }

    this->accept();
}

void ACPowerChargerDialog::on_pushButton_quit_clicked()
{
    this->reject();
}


