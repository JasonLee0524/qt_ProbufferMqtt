#include "BasicInfoDialog.h"
#include "ui_BasicInfoDialog.h"
#include <QDebug>
#include "Global_Param.h"
#include "Protobuf/messageall.pb.h"

BasicInfoDialog::BasicInfoDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BasicInfoDialog)
{
    ui->setupUi(this);
  //  this->setAttribute(Qt::WA_DeleteOnClose);


    //默认全选中
    ui->checkBox_power->setChecked(true);
    ui->checkBox_power_charger_type->setChecked(true);
    ui->checkBox_charging_connector_quantity->setChecked(true);
    ui->checkBox_software_version->setChecked(true);
    ui->checkBox_hardware_version->setChecked(true);
    ui->checkBox_CommonBasicInfo->setChecked(true);
    ui->checkBox_ServiceStateInfo->setChecked(false);
    ui->checkBox_ServiceState->setChecked(false);
    ui->checkBox_ServiceStateReason->setChecked(false);

    //充电桩类型
    ui->comboBox_power_charger_type->addItem(tr("AC充电类型"),0);
    ui->comboBox_power_charger_type->addItem(tr("DC充电类型"),1);
    ui->comboBox_power_charger_type->addItem(tr("AC/DC充电类型"),2);
    ui->comboBox_power_charger_type->addItem(tr("其他充电类型"),254);
    ui->comboBox_power_charger_type->addItem(tr("未知电类型在"),255);

    ui->comboBox_ServiceState->addItem(tr("正在服务"),0);
    ui->comboBox_ServiceState->addItem(tr("等待服务"),1);
    ui->comboBox_ServiceState->addItem(tr("停止服务"),2);
    ui->comboBox_ServiceState->addItem(tr("暂停服务"),3);
    ui->comboBox_ServiceState->addItem(tr("正在建设"),4);
    ui->comboBox_ServiceState->addItem(tr("下线"),5);
    ui->comboBox_ServiceState->addItem(tr("其他状态"),254);
    ui->comboBox_ServiceState->addItem(tr("未知"),255);

    ui->comboBox_ServiceStateReason->addItem(tr("电池电量不够"),0);
    ui->comboBox_ServiceStateReason->addItem(tr("充电车续航里程不足"),1);
    ui->comboBox_ServiceStateReason->addItem(tr("充电车驾驶员交接班"),2);
    ui->comboBox_ServiceStateReason->addItem(tr("下班(服务运营时间之外)"),3);
    ui->comboBox_ServiceStateReason->addItem(tr("升级"),4);
    ui->comboBox_ServiceStateReason->addItem(tr("故障停机"),5);
    ui->comboBox_ServiceStateReason->addItem(tr("设备保养"),6);
    ui->comboBox_ServiceStateReason->addItem(tr("补能中"),7);
    ui->comboBox_ServiceStateReason->addItem(tr("其他原因"),254);
    ui->comboBox_ServiceStateReason->addItem(tr("未知"),255);

    ui->lineEdit_power->setText(Global_Param::getInstance().ACpowercharger.basicinfo.power);
    ui->lineEdit_charging_connector_quantity->setText(Global_Param::getInstance().ACpowercharger.basicinfo.charging_connector_quantity);
    ui->lineEdit_software_version->setText(Global_Param::getInstance().ACpowercharger.basicinfo.common_basic_info.software_version);
    ui->lineEdit_hardware_version->setText(Global_Param::getInstance().ACpowercharger.basicinfo.common_basic_info.hardware_version);

    if(Global_Param::getInstance().ACpowercharger.basicinfo.power_charger_type <=2)
    {
        ui->comboBox_power_charger_type->setCurrentIndex(Global_Param::getInstance().ACpowercharger.basicinfo.power_charger_type);
    }
    if(Global_Param::getInstance().ACpowercharger.basicinfo.power_charger_type ==254)
    {
        ui->comboBox_power_charger_type->setCurrentIndex(3);
    }
    if(Global_Param::getInstance().ACpowercharger.basicinfo.power_charger_type ==255)
    {
        ui->comboBox_power_charger_type->setCurrentIndex(4);
    }

    if(Global_Param::getInstance().ACpowercharger.basicinfo.common_basic_info.service_state_info.service_state <=5)
    {
        ui->comboBox_ServiceState->setCurrentIndex(Global_Param::getInstance().ACpowercharger.basicinfo.common_basic_info.service_state_info.service_state);
    }
    if(Global_Param::getInstance().ACpowercharger.basicinfo.common_basic_info.service_state_info.service_state ==254)
    {
        ui->comboBox_ServiceState->setCurrentIndex(6);
    }
    if(Global_Param::getInstance().ACpowercharger.basicinfo.common_basic_info.service_state_info.service_state ==255)
    {
        ui->comboBox_ServiceState->setCurrentIndex(7);
    }

    if(Global_Param::getInstance().ACpowercharger.basicinfo.common_basic_info.service_state_info.service_state_reason <=7)
    {
        ui->comboBox_ServiceStateReason->setCurrentIndex(Global_Param::getInstance().ACpowercharger.basicinfo.common_basic_info.service_state_info.service_state_reason);
    }
    if(Global_Param::getInstance().ACpowercharger.basicinfo.common_basic_info.service_state_info.service_state_reason ==254)
    {
        ui->comboBox_ServiceStateReason->setCurrentIndex(8);
    }
    if(Global_Param::getInstance().ACpowercharger.basicinfo.common_basic_info.service_state_info.service_state_reason ==255)
    {
        ui->comboBox_ServiceStateReason->setCurrentIndex(9);
    }

}

BasicInfoDialog::~BasicInfoDialog()
{
    qDebug()<<"~BasicInfoDialog";
    delete ui;
}

void BasicInfoDialog::on_pushButton_save_clicked()
{

    qDebug()<<ui->comboBox_ServiceStateReason->currentData().toInt();

    switch (ui->comboBox_power_charger_type->currentData().toInt()) {
    case 0:
        Global_Param::getInstance().ACpowercharger.basicinfo.power_charger_type = ACPowerCharger_PowerChargerType_PCT_AC_ONLY;
        break;
    case 1:
        Global_Param::getInstance().ACpowercharger.basicinfo.power_charger_type = ACPowerCharger_PowerChargerType_PCT_DC_ONLY;
        break;
    case 2:
        Global_Param::getInstance().ACpowercharger.basicinfo.power_charger_type = ACPowerCharger_PowerChargerType_PCT_AC_DC_HYBRID;
        break;
    case 254:
        Global_Param::getInstance().ACpowercharger.basicinfo.power_charger_type = ACPowerCharger_PowerChargerType_PCT_OTHER;
        break;
    case 255:
        Global_Param::getInstance().ACpowercharger.basicinfo.power_charger_type = ACPowerCharger_PowerChargerType_PCT_UNKNOWN;
        break;
    default:
        break;
    }
    Global_Param::getInstance().ACpowercharger.basicinfo.charging_connector_quantity = ui->lineEdit_charging_connector_quantity->text();
    Global_Param::getInstance().ACpowercharger.basicinfo.power = ui->lineEdit_power->text();

    Global_Param::getInstance().ACpowercharger.basicinfo.common_basic_info.software_version = ui->lineEdit_software_version->text();
    Global_Param::getInstance().ACpowercharger.basicinfo.common_basic_info.hardware_version = ui->lineEdit_hardware_version->text();

    switch (ui->comboBox_ServiceState->currentData().toInt()) {
    case 0:
        Global_Param::getInstance().ACpowercharger.basicinfo.common_basic_info.service_state_info.service_state = SS_ON_GOING;
        break;
    case 1:
        Global_Param::getInstance().ACpowercharger.basicinfo.common_basic_info.service_state_info.service_state = SS_WAITING;
        break;
    case 2:
        Global_Param::getInstance().ACpowercharger.basicinfo.common_basic_info.service_state_info.service_state = SS_STOP;
        break;
    case 3:
        Global_Param::getInstance().ACpowercharger.basicinfo.common_basic_info.service_state_info.service_state = SS_PAUSE;
        break;
    case 4:
        Global_Param::getInstance().ACpowercharger.basicinfo.common_basic_info.service_state_info.service_state = SS_UNDER_CONSTRUCTION;
        break;
    case 5:
        Global_Param::getInstance().ACpowercharger.basicinfo.common_basic_info.service_state_info.service_state = SS_OFFLINE;
        break;
    case 254:
        Global_Param::getInstance().ACpowercharger.basicinfo.common_basic_info.service_state_info.service_state = SS_OTHER;
        break;
    case 255:
        Global_Param::getInstance().ACpowercharger.basicinfo.common_basic_info.service_state_info.service_state = SS_UNKNOWN;
        break;
    default:
        break;
    }

    switch (ui->comboBox_ServiceStateReason->currentData().toInt()) {
    case 0:
        Global_Param::getInstance().ACpowercharger.basicinfo.common_basic_info.service_state_info.service_state_reason = SSR_OUT_OF_POWER;
        break;
    case 1:
        Global_Param::getInstance().ACpowercharger.basicinfo.common_basic_info.service_state_info.service_state_reason = SSR_LACK_OF_RANGE;
        break;
    case 2:
        Global_Param::getInstance().ACpowercharger.basicinfo.common_basic_info.service_state_info.service_state_reason = SSR_ALTERNATIVE_TRANSLATIONS;
        break;
    case 3:
        Global_Param::getInstance().ACpowercharger.basicinfo.common_basic_info.service_state_info.service_state_reason = SSR_OFF_WORK;
        break;
    case 4:
        Global_Param::getInstance().ACpowercharger.basicinfo.common_basic_info.service_state_info.service_state_reason = SSR_UPGRADE;
        break;
    case 5:
        Global_Param::getInstance().ACpowercharger.basicinfo.common_basic_info.service_state_info.service_state_reason = SSR_DOWNTIME;
        break;
    case 6:
        Global_Param::getInstance().ACpowercharger.basicinfo.common_basic_info.service_state_info.service_state_reason = SSR_MAINTENANCE;
        break;
    case 7:
        Global_Param::getInstance().ACpowercharger.basicinfo.common_basic_info.service_state_info.service_state_reason = SSR_SUPPLEMENTATION;
        break;
    case 254:
        Global_Param::getInstance().ACpowercharger.basicinfo.common_basic_info.service_state_info.service_state_reason = SSR_OTHER;
        break;
    case 255:
        Global_Param::getInstance().ACpowercharger.basicinfo.common_basic_info.service_state_info.service_state_reason = SSR_UNKNOWN;
        break;
    default:
        break;
    }

    qDebug()<<"service_state_reason:"<<Global_Param::getInstance().ACpowercharger.basicinfo.common_basic_info.service_state_info.service_state_reason;
    this->accept();
}

void BasicInfoDialog::on_pushButton_quit_clicked()
{
    this->reject();
}

bool BasicInfoDialog::Get_checkBox_power_charger_type(){
    return ui->checkBox_power_charger_type->isChecked();
}

bool BasicInfoDialog::Get_checkBox_charging_connector_quantity(){
    return ui->checkBox_charging_connector_quantity->isChecked();
}

bool BasicInfoDialog::Get_checkBox_power(){
    return ui->checkBox_power->isChecked();
}

bool BasicInfoDialog::Get_checkBox_software_version(){
    return ui->checkBox_software_version->isChecked();
}

bool BasicInfoDialog::Get_checkBox_hardware_version(){
    return ui->checkBox_hardware_version->isChecked();
}

bool BasicInfoDialog::Get_checkBox_ServiceState(){
    return ui->checkBox_ServiceState->isChecked();
}

bool BasicInfoDialog::Get_checkBox_ServiceStateReason(){
    return ui->checkBox_ServiceStateReason->isChecked();
}

bool BasicInfoDialog::Get_checkBox_CommonBasicInfo(){
    return ui->checkBox_CommonBasicInfo->isChecked();
}

bool BasicInfoDialog::Get_checkBox_ServiceStateInfo(){
    return ui->checkBox_ServiceStateInfo->isChecked();
}
