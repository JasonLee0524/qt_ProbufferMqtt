#include "RemoteOperationDialog.h"
#include "ui_RemoteOperationDialog.h"
#include "Global_Param.h"
#include <QDebug>
RemoteOperationDialog::RemoteOperationDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RemoteOperationDialog)
{
    ui->setupUi(this);

    ui->checkBox_message_timestamp->setChecked(true);
    ui->checkBox_RemoteConfiguration->setChecked(true);
        ui->checkBox_Configuration_request_id->setChecked(true);
        ui->checkBox_RemoteConfigurationInfo->setChecked(true);
            ui->checkBox_configuration_key->setChecked(true);
            ui->checkBox_configuration_value->setChecked(true);

    ui->checkBox_RemoteControl->setChecked(true);
        ui->checkBox_Control_request_id->setChecked(true);
        ui->checkBox_RemoteControlCommand->setChecked(true);
        ui->checkBox_RemoteControlParam->setChecked(true);
            ui->checkBox_key->setChecked(true);
            ui->checkBox_value->setChecked(true);

    ui->checkBox_RemoteUpgrade->setChecked(true);
        ui->checkBox_Upgrade_request_id->setChecked(true);
        ui->checkBox_software_version->setChecked(true);
        ui->checkBox_ftp_address->setChecked(true);

    ui->comboBox_RemoteControlCommand->addItem("紧急断电",0);
    ui->comboBox_RemoteControlCommand->addItem("重启",1);
    ui->comboBox_RemoteControlCommand->addItem("枪使能",2);
    ui->comboBox_RemoteControlCommand->addItem("枪禁用",3);
    ui->comboBox_RemoteControlCommand->addItem("开始充电",4);
    ui->comboBox_RemoteControlCommand->addItem("结束充电",5);
    ui->comboBox_RemoteControlCommand->addItem("远程开启",6);

    ui->lineEdit_message_timestamp->setText( Global_Param::getInstance().RemoteOperation.message_timestamp);
    ui->lineEdit_Configuration_request_id->setText(Global_Param::getInstance().RemoteOperation.remote_configuration.request_id);
    ui->lineEdit_configuration_key->setText(Global_Param::getInstance().RemoteOperation.remote_configuration.remote_configuration_info.configuration_key);
    ui->lineEdit_configuration_value->setText(Global_Param::getInstance().RemoteOperation.remote_configuration.remote_configuration_info.configuration_value);

    ui->lineEdit_Control_request_id->setText(Global_Param::getInstance().RemoteOperation.remote_control.request_id);
    ui->lineEdit_key->setText(Global_Param::getInstance().RemoteOperation.remote_control.remote_control_param.key);
    ui->lineEdit_value->setText(Global_Param::getInstance().RemoteOperation.remote_control.remote_control_param.value);
    ui->comboBox_RemoteControlCommand->setCurrentIndex(Global_Param::getInstance().RemoteOperation.remote_control.remote_control_command);

    ui->lineEdit_Upgrade_request_id->setText(Global_Param::getInstance().RemoteOperation.remote_upgrade.request_id);
    ui->lineEdit_software_version->setText(Global_Param::getInstance().RemoteOperation.remote_upgrade.software_version);
    ui->lineEdit_ftp_address->setText(Global_Param::getInstance().RemoteOperation.remote_upgrade.ftp_address);

    SetData();

}

RemoteOperationDialog::~RemoteOperationDialog()
{
    delete ui;
}

void RemoteOperationDialog::on_pushButton_save_clicked()
{
    switch (ui->comboBox_RemoteControlCommand->currentData().toInt()) {
    case 0:
         Global_Param::getInstance().RemoteOperation.remote_control.remote_control_command = RCC_SHUTDOWN;
        break;
    case 1:
         Global_Param::getInstance().RemoteOperation.remote_control.remote_control_command = RCC_REBOOT;
        break;
    case 2:
         Global_Param::getInstance().RemoteOperation.remote_control.remote_control_command = RCC_ENABLE_CONNECTOR;
        break;
    case 3:
         Global_Param::getInstance().RemoteOperation.remote_control.remote_control_command = RCC_DISABLE_CONNECTOR;
        break;
    case 4:
         Global_Param::getInstance().RemoteOperation.remote_control.remote_control_command = RCC_START_CHARGING;
        break;
    case 5:
         Global_Param::getInstance().RemoteOperation.remote_control.remote_control_command = RCC_STOP_CHARGING;
        break;
    case 6:
         Global_Param::getInstance().RemoteOperation.remote_control.remote_control_command = RCC_STARTUP;
        break;
    default:
        break;
    }

    //RemoteOperation
    Global_Param::getInstance().RemoteOperation.message_timestamp = ui->lineEdit_message_timestamp->text();
    //RemoteConfiguration
    Global_Param::getInstance().RemoteOperation.remote_configuration.request_id = ui->lineEdit_Configuration_request_id->text();
    Global_Param::getInstance().RemoteOperation.remote_configuration.remote_configuration_info.configuration_key = ui->lineEdit_configuration_key->text();
    Global_Param::getInstance().RemoteOperation.remote_configuration.remote_configuration_info.configuration_value = ui->lineEdit_configuration_value->text();
    //RemoteControl
    Global_Param::getInstance().RemoteOperation.remote_control.request_id = ui->lineEdit_Control_request_id->text();
    Global_Param::getInstance().RemoteOperation.remote_control.remote_control_param.key = ui->lineEdit_key->text();
    Global_Param::getInstance().RemoteOperation.remote_control.remote_control_param.value = ui->lineEdit_value->text();
    //RemoteUpgrade
    Global_Param::getInstance().RemoteOperation.remote_upgrade.request_id = ui->lineEdit_Upgrade_request_id->text();
    Global_Param::getInstance().RemoteOperation.remote_upgrade.software_version = ui->lineEdit_software_version->text();
    Global_Param::getInstance().RemoteOperation.remote_upgrade.ftp_address = ui->lineEdit_ftp_address->text();

    SetData();
    this->accept();
}

void RemoteOperationDialog::on_pushButton_quit_clicked()
{
    this->reject();
}

void RemoteOperationDialog::SetData(){
    m_RemoteOperationData.Clear();

    if(ui->checkBox_message_timestamp->isChecked()){
        m_RemoteOperationData.set_message_timestamp(Global_Param::getInstance().RemoteOperation.message_timestamp.toInt());
    }
    if(ui->checkBox_RemoteConfiguration->isChecked()){
        RemoteConfiguration* RemoteConfiguration_info = m_RemoteOperationData.mutable_remote_configuration();
        if(ui->checkBox_Configuration_request_id->isChecked())
            RemoteConfiguration_info->set_request_id(Global_Param::getInstance().RemoteOperation.remote_configuration.request_id.toUtf8());
        if(ui->checkBox_RemoteConfigurationInfo->isChecked()){
            RemoteConfigurationInfo* RemoteConfigurationInfo_info = RemoteConfiguration_info->add_remote_configuration_info();
            if(ui->checkBox_configuration_key->isChecked()){
                RemoteConfigurationInfo_info->set_configuration_key(Global_Param::getInstance().RemoteOperation.remote_configuration.remote_configuration_info.configuration_key.toUtf8());
            }
            if(ui->checkBox_configuration_value->isChecked()){
                RemoteConfigurationInfo_info->set_configuration_value(Global_Param::getInstance().RemoteOperation.remote_configuration.remote_configuration_info.configuration_value.toUtf8());
            }
        }
    }
    if(ui->checkBox_RemoteControl->isChecked()){
        RemoteControl* RemoteControl_info = m_RemoteOperationData.mutable_remote_control();
        if(ui->checkBox_Control_request_id->isChecked())
            RemoteControl_info->set_request_id(Global_Param::getInstance().RemoteOperation.remote_control.request_id.toUtf8());
        if(ui->checkBox_RemoteControlCommand->isChecked())
            RemoteControl_info->set_remote_control_command(Global_Param::getInstance().RemoteOperation.remote_control.remote_control_command);
        if(ui->checkBox_RemoteControlParam->isChecked()){
            RemoteControlParam* RemoteControlParam_info = RemoteControl_info->add_remote_control_param();
            if(ui->checkBox_key->isChecked()){
                RemoteControlParam_info->set_key(Global_Param::getInstance().RemoteOperation.remote_control.remote_control_param.key.toUtf8());
            }
            if(ui->checkBox_value->isChecked()){
                RemoteControlParam_info->set_value(Global_Param::getInstance().RemoteOperation.remote_control.remote_control_param.value.toUtf8());
            }
        }
    }

    if(ui->checkBox_RemoteUpgrade->isChecked()){
        RemoteUpgrade* RemoteUpgrade_info = m_RemoteOperationData.mutable_remote_upgrade();
        if(ui->checkBox_Upgrade_request_id->isChecked())
            RemoteUpgrade_info->set_request_id( Global_Param::getInstance().RemoteOperation.remote_upgrade.request_id.toUtf8());
        if(ui->checkBox_software_version->isChecked())
            RemoteUpgrade_info->set_software_version( Global_Param::getInstance().RemoteOperation.remote_upgrade.software_version.toUtf8());
        if(ui->checkBox_ftp_address->isChecked())
            RemoteUpgrade_info->set_ftp_address( Global_Param::getInstance().RemoteOperation.remote_upgrade.ftp_address.toUtf8());
    }
}

