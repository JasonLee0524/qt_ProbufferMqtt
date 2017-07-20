#include "RealtimeInfoDialog.h"
#include "ui_RealtimeInfoDialog.h"
#include <QDebug>
#include "Global_Param.h"
RealtimeInfoDialog::RealtimeInfoDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RealtimeInfoDialog)
{
    ui->setupUi(this);

   // this->setAttribute(Qt::WA_DeleteOnClose);


    //默认全选中
    ui->checkBox_NetworkOperator->setChecked(true);
    ui->checkBox_NetworkType->setChecked(true);
    ui->checkBox_DeviceWorkState->setChecked(true);
    ui->checkBox_ChargingConnectorWorkState->setChecked(true);
    ui->checkBox_ChargingConnectorConnectionState->setChecked(true);
    ui->checkBox_ChargingConnectorFaultState->setChecked(true);
    ui->checkBox_PowerChargerConnectorOutputType->setChecked(true);
    ui->checkBox_charging_connector_id->setChecked(true);
    ui->checkBox_ConnectivityState->setChecked(true);
    ui->checkBox_ChargingConnector->setChecked(true);
    ui->checkBox_PowerChargerConnectorOutputVoltage->setChecked(true);
    ui->checkBox_power_charger_connector_rated_output_power->setChecked(true);
    ui->checkBox_realtime_output_voltage->setChecked(true);
    ui->checkBox_realtime_output_current->setChecked(true);

    ui->comboBox_NetworkOperator->addItem(tr("中国移动"),0);
    ui->comboBox_NetworkOperator->addItem(tr("中国联通"),1);
    ui->comboBox_NetworkOperator->addItem(tr("中国电信"),2);
    ui->comboBox_NetworkOperator->addItem(tr("其他"),254);
    ui->comboBox_NetworkOperator->addItem(tr("未知"),255);

    ui->comboBox_NetworkType->addItem(tr("1G"),0);
    ui->comboBox_NetworkType->addItem(tr("2G"),1);
    ui->comboBox_NetworkType->addItem(tr("3G"),2);
    ui->comboBox_NetworkType->addItem(tr("4G"),3);
    ui->comboBox_NetworkType->addItem(tr("其他"),254);
    ui->comboBox_NetworkType->addItem(tr("未知"),255);

    ui->comboBox_DeviceWorkState->addItem(tr("空闲"),0);
    ui->comboBox_DeviceWorkState->addItem(tr("充电中"),1);

    ui->comboBox_ChargingConnectorWorkState->addItem(tr("空闲"),0);
    ui->comboBox_ChargingConnectorWorkState->addItem(tr("充电中"),1);
    ui->comboBox_ChargingConnectorWorkState->addItem(tr("充电完成"),3);

    ui->comboBox_ChargingConnectorConnectionState->addItem(tr("连接"),0);
    ui->comboBox_ChargingConnectorConnectionState->addItem(tr("断开连接"),1);

    ui->comboBox_ChargingConnectorFaultState->addItem(tr("不使能"),0);
    ui->comboBox_ChargingConnectorFaultState->addItem(tr("使能"),1);

    ui->comboBox_PowerChargerConnectorOutputType->addItem(tr("COT_3_PHASE"),0);
    ui->comboBox_PowerChargerConnectorOutputType->addItem(tr("COT_7_PIN"),1);
    ui->comboBox_PowerChargerConnectorOutputType->addItem(tr("COT_9_PIN"),2);

    ui->comboBox_PowerChargerConnectorOutputVoltage->addItem(tr("380V"),0);
    ui->comboBox_PowerChargerConnectorOutputVoltage->addItem(tr("220V"),1);
    ui->comboBox_PowerChargerConnectorOutputVoltage->addItem(tr("500V"),2);
    ui->comboBox_PowerChargerConnectorOutputVoltage->addItem(tr("750V"),3);



    ui->lineEdit_charging_connector_id->setText(Global_Param::getInstance().ACpowercharger.realtime_info.charging_connector.charging_connector_id);
    ui->lineEdit_power_charger_connector_rated_output_power->setText(Global_Param::getInstance().ACpowercharger.realtime_info.charging_connector.power_charger_connector_rated_output_power);
    ui->lineEdit_realtime_output_voltage->setText(Global_Param::getInstance().ACpowercharger.realtime_info.charging_connector.realtime_output_voltage);
    ui->lineEdit_realtime_output_current->setText(Global_Param::getInstance().ACpowercharger.realtime_info.charging_connector.realtime_output_current);


    if(Global_Param::getInstance().ACpowercharger.realtime_info.connectivity_state.network_operator <=2)
    {
        ui->comboBox_NetworkOperator->setCurrentIndex(Global_Param::getInstance().ACpowercharger.realtime_info.connectivity_state.network_operator);
    }
    if(Global_Param::getInstance().ACpowercharger.realtime_info.connectivity_state.network_operator ==254)
    {
        ui->comboBox_NetworkOperator->setCurrentIndex(3);
    }
    if(Global_Param::getInstance().ACpowercharger.realtime_info.connectivity_state.network_operator ==255)
    {
        ui->comboBox_NetworkOperator->setCurrentIndex(4);
    }

    if(Global_Param::getInstance().ACpowercharger.realtime_info.connectivity_state.network_type <=3)
    {
        ui->comboBox_NetworkType->setCurrentIndex(Global_Param::getInstance().ACpowercharger.realtime_info.connectivity_state.network_type);
    }
    if(Global_Param::getInstance().ACpowercharger.realtime_info.connectivity_state.network_type ==254)
    {
        ui->comboBox_NetworkType->setCurrentIndex(4);
    }
    if(Global_Param::getInstance().ACpowercharger.realtime_info.connectivity_state.network_type ==255)
    {
        ui->comboBox_NetworkType->setCurrentIndex(5);
    }


    ui->comboBox_DeviceWorkState->setCurrentIndex(Global_Param::getInstance().ACpowercharger.realtime_info.device_work_state);
    ui->comboBox_ChargingConnectorWorkState->setCurrentIndex(Global_Param::getInstance().ACpowercharger.realtime_info.charging_connector.charging_connector_work_state);
    ui->comboBox_ChargingConnectorConnectionState->setCurrentIndex(Global_Param::getInstance().ACpowercharger.realtime_info.charging_connector.charging_connector_connection_state);
    ui->comboBox_ChargingConnectorFaultState->setCurrentIndex(Global_Param::getInstance().ACpowercharger.realtime_info.charging_connector.charging_connector_fault_state);
    ui->comboBox_PowerChargerConnectorOutputType->setCurrentIndex(Global_Param::getInstance().ACpowercharger.realtime_info.charging_connector.power_charger_connector_output_type);
    ui->comboBox_PowerChargerConnectorOutputVoltage->setCurrentIndex(Global_Param::getInstance().ACpowercharger.realtime_info.charging_connector.power_charger_connector_rated_output_voltage);

}

RealtimeInfoDialog::~RealtimeInfoDialog()
{
    qDebug()<<"~RealtimeInfoDialog";
    delete ui;
}

void RealtimeInfoDialog::on_pushButton_save_clicked()
{
    switch (ui->comboBox_NetworkOperator->currentData().toInt()) {
    case 0:
        Global_Param::getInstance().ACpowercharger.realtime_info.connectivity_state.network_operator = NO_CHINA_MOBILE;
        break;
    case 1:
        Global_Param::getInstance().ACpowercharger.realtime_info.connectivity_state.network_operator = NO_CHINA_UNICOM;
        break;
    case 2:
        Global_Param::getInstance().ACpowercharger.realtime_info.connectivity_state.network_operator = NO_CHINA_TELECOM;
        break;
    case 254:
        Global_Param::getInstance().ACpowercharger.realtime_info.connectivity_state.network_operator = NO_OTHER;
        break;
    case 255:
        Global_Param::getInstance().ACpowercharger.realtime_info.connectivity_state.network_operator = NO_UNKNOWN;
        break;
    default:
        break;
    }

    switch (ui->comboBox_NetworkType->currentData().toInt()) {
    case 0:
        Global_Param::getInstance().ACpowercharger.realtime_info.connectivity_state.network_type = NT_RJ45;
        break;
    case 1:
        Global_Param::getInstance().ACpowercharger.realtime_info.connectivity_state.network_type = NT_RADIO_2G;
        break;
    case 2:
        Global_Param::getInstance().ACpowercharger.realtime_info.connectivity_state.network_type = NT_RADIO_3G;
        break;
    case 3:
        Global_Param::getInstance().ACpowercharger.realtime_info.connectivity_state.network_type = NT_RADIO_4G;
        break;
    case 254:
        Global_Param::getInstance().ACpowercharger.realtime_info.connectivity_state.network_type = NT_OTHER;
        break;
    case 255:
        Global_Param::getInstance().ACpowercharger.realtime_info.connectivity_state.network_type = NT_UNKNOWN;
        break;
    default:
        break;
    }

    switch (ui->comboBox_DeviceWorkState->currentData().toInt()) {
    case 0:
        Global_Param::getInstance().ACpowercharger.realtime_info.device_work_state = ACPowerCharger_DeviceWorkState_DWS_FREE;
        break;
    case 1:
        Global_Param::getInstance().ACpowercharger.realtime_info.device_work_state = ACPowerCharger_DeviceWorkState_DWS_IN_CHARGING;
        break;
    default:
        break;
    }


    Global_Param::getInstance().ACpowercharger.realtime_info.charging_connector.charging_connector_id = ui->lineEdit_charging_connector_id->text();

    switch (ui->comboBox_ChargingConnectorWorkState->currentData().toInt()) {
    case 0:
        Global_Param::getInstance().ACpowercharger.realtime_info.charging_connector.charging_connector_work_state = CCWS_FREE;
        break;
    case 1:
        Global_Param::getInstance().ACpowercharger.realtime_info.charging_connector.charging_connector_work_state = CCWS_IN_CHARGING;
        break;
    case 3:
        Global_Param::getInstance().ACpowercharger.realtime_info.charging_connector.charging_connector_work_state = CCWS_CHARGING_COMPLETE;
        break;
    default:
        break;
    }


    switch (ui->comboBox_ChargingConnectorConnectionState->currentData().toInt()) {
    case 0:
        Global_Param::getInstance().ACpowercharger.realtime_info.charging_connector.charging_connector_connection_state = CCCS_CONNECTED;
        break;
    case 1:
        Global_Param::getInstance().ACpowercharger.realtime_info.charging_connector.charging_connector_connection_state = CCCS_DISCONNECTED;
        break;
    default:
        break;
    }

    switch (ui->comboBox_ChargingConnectorFaultState->currentData().toInt()) {
    case 0:
        Global_Param::getInstance().ACpowercharger.realtime_info.charging_connector.charging_connector_fault_state = CCFS_NO_FAULT;
        break;
    case 1:
        Global_Param::getInstance().ACpowercharger.realtime_info.charging_connector.charging_connector_fault_state = CCFS_HAVING_FAULT;
        break;
    default:
        break;
    }

    switch (ui->comboBox_PowerChargerConnectorOutputType->currentData().toInt()) {
    case 0:
        Global_Param::getInstance().ACpowercharger.realtime_info.charging_connector.power_charger_connector_output_type = COT_3_PHASE;
        break;
    case 1:
        Global_Param::getInstance().ACpowercharger.realtime_info.charging_connector.power_charger_connector_output_type = COT_7_PIN;
        break;
    case 2:
        Global_Param::getInstance().ACpowercharger.realtime_info.charging_connector.power_charger_connector_output_type = COT_9_PIN;
        break;
    default:
        break;
    }


    this->accept();
}

void RealtimeInfoDialog::on_pushButton_quit_clicked()
{
    this->reject();
}

bool RealtimeInfoDialog::Get_checkBox_ConnectivityState(){
    return ui->checkBox_ConnectivityState->isChecked();
}

bool RealtimeInfoDialog::Get_checkBox_ChargingConnector(){
    return ui->checkBox_ChargingConnector->isChecked();
}

bool RealtimeInfoDialog::Get_checkBox_NetworkOperator(){
    return ui->checkBox_NetworkOperator->isChecked();
}

bool RealtimeInfoDialog::Get_checkBox_NetworkType(){
    return ui->checkBox_NetworkType->isChecked();
}

bool RealtimeInfoDialog::Get_checkBox_DeviceWorkState(){
    return ui->checkBox_DeviceWorkState->isChecked();
}

bool RealtimeInfoDialog::Get_checkBox_charging_connector_id(){
    return ui->checkBox_charging_connector_id->isChecked();
}

bool RealtimeInfoDialog::Get_checkBox_ChargingConnectorWorkState(){
    return ui->checkBox_ChargingConnectorWorkState->isChecked();
}

bool RealtimeInfoDialog::Get_checkBox_ChargingConnectorConnectionState(){
    return ui->checkBox_ChargingConnectorConnectionState->isChecked();
}

bool RealtimeInfoDialog::Get_checkBox_ChargingConnectorFaultState(){
    return ui->checkBox_ChargingConnectorFaultState->isChecked();
}

bool RealtimeInfoDialog::Get_checkBox_PowerChargerConnectorOutputType(){
    return ui->checkBox_PowerChargerConnectorOutputType->isChecked();
}

bool RealtimeInfoDialog::Get_checkBox_PowerChargerConnectorOutputVoltage(){
    return ui->checkBox_PowerChargerConnectorOutputVoltage->isChecked();
}

bool RealtimeInfoDialog::Get_checkBox_power_charger_connector_rated_output_power(){
    return ui->checkBox_power_charger_connector_rated_output_power->isChecked();
}

bool RealtimeInfoDialog::Get_checkBox_realtime_output_voltage(){
    return ui->checkBox_realtime_output_voltage->isChecked();
}

bool RealtimeInfoDialog::Get_checkBox_realtime_output_current(){
    return ui->checkBox_realtime_output_current->isChecked();
}




