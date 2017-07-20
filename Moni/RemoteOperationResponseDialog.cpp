#include "RemoteOperationResponseDialog.h"
#include "ui_RemoteOperationResponseDialog.h"
#include <QDesktopWidget>
#include <QDebug>
#include "Global_Param.h"
RemoteOperationResponseDialog::RemoteOperationResponseDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RemoteOperationResponseDialog)
{
    ui->setupUi(this);
    m_LocalConfigurationDialog = NULL;
    m_LocalConfigurationDialog = new LocalConfigurationDialog(this);


    ui->checkBox_RemoteConfigurationResponse->setChecked(true);
        ui->checkBox_RemoteConfigurationResponse_request_id->setChecked(true);
        ui->checkBox_RemoteConfigurationResponse_device_id->setChecked(true);
        ui->checkBox_RemoteConfigurationResponseType->setChecked(true);
        ui->checkBox_RemoteConfigurationResponse_failureReason->setChecked(true);
        ui->checkBox_LocalConfigurationInfo->setChecked(true);

    ui->checkBox_RemoteControlResponse->setChecked(true);
        ui->checkBox_RemoteControlResponse_request_id->setChecked(true);
        ui->checkBox_RemoteControlResponse_device_id->setChecked(true);
        ui->checkBox_RemoteControlResponseType->setChecked(true);
        ui->checkBox_RemoteControlResponse_failureReason->setChecked(true);

    ui->checkBox_RemoteUpgradeResponse->setChecked(true);
        ui->checkBox_RemoteUpgradeResponse_request_id->setChecked(true);
        ui->checkBox_RemoteUpgradeResponse_device_id->setChecked(true);

    ui->comboBox_RemoteConfigurationResponseType->addItem("RCONFRT_RECEIVED",0);
    ui->comboBox_RemoteConfigurationResponseType->addItem("RCONFRT_FINISHED_OK",1);
    ui->comboBox_RemoteConfigurationResponseType->addItem("RCONFRT_FINISHED_FAILED",2);

    ui->lineEdit_RemoteConfigurationResponse_request_id->setText(Global_Param::getInstance().RemoteOperationResponse.remote_configuration_response.request_id);
    ui->lineEdit_RemoteConfigurationResponse_device_id->setText(Global_Param::getInstance().RemoteOperationResponse.remote_configuration_response.device_id);
    ui->lineEdit_RemoteControlResponse_failureReason->setText(Global_Param::getInstance().RemoteOperationResponse.remote_configuration_response.failureReason );
    ui->comboBox_RemoteConfigurationResponseType->setCurrentIndex(Global_Param::getInstance().RemoteOperationResponse.remote_configuration_response.remote_configuration_response_type);

    ui->lineEdit_RemoteControlResponse_request_id->setText(Global_Param::getInstance().RemoteOperationResponse.remote_control_response.request_id);
    ui->lineEdit_RemoteControlResponse_device_id->setText(Global_Param::getInstance().RemoteOperationResponse.remote_control_response.device_id);
    ui->comboBox_RemoteControlResponseType->setCurrentIndex(Global_Param::getInstance().RemoteOperationResponse.remote_control_response.remote_control_response_type);
    ui->lineEdit_RemoteControlResponse_failureReason->setText(Global_Param::getInstance().RemoteOperationResponse.remote_control_response.failureReason);

    ui->lineEdit_RemoteUpgradeResponse_request_id->setText(Global_Param::getInstance().RemoteOperationResponse.remote_upgrade_response.request_id);
    ui->lineEdit_RemoteUpgradeResponse_device_id->setText(Global_Param::getInstance().RemoteOperationResponse.remote_upgrade_response.device_id);

    SetData();

}

RemoteOperationResponseDialog::~RemoteOperationResponseDialog()
{
    delete ui;
}

void RemoteOperationResponseDialog::on_pushButton_save_clicked()
{
    switch (ui->comboBox_RemoteConfigurationResponseType->currentData().toInt()) {
    case 0:
        Global_Param::getInstance().RemoteOperationResponse.remote_configuration_response.remote_configuration_response_type = RCONFRT_RECEIVED;
        break;
    case 1:
        Global_Param::getInstance().RemoteOperationResponse.remote_configuration_response.remote_configuration_response_type = RCONFRT_FINISHED_OK;
        break;
    case 2:
        Global_Param::getInstance().RemoteOperationResponse.remote_configuration_response.remote_configuration_response_type = RCONFRT_FINISHED_FAILED;
        break;
    default:
        break;
    }

    switch (ui->comboBox_RemoteControlResponseType->currentData().toInt()) {
    case 0:
        Global_Param::getInstance().RemoteOperationResponse.remote_control_response.remote_control_response_type = RCONTRT_RECEIVED;
        break;
    case 1:
        Global_Param::getInstance().RemoteOperationResponse.remote_control_response.remote_control_response_type = RCONTRT_FINISHED_OK;
        break;
    case 2:
        Global_Param::getInstance().RemoteOperationResponse.remote_control_response.remote_control_response_type = RCONTRT_FINISHED_FAILED;
        break;
    default:
        break;
    }

    Global_Param::getInstance().RemoteOperationResponse.remote_configuration_response.request_id = ui->lineEdit_RemoteConfigurationResponse_request_id->text();
    Global_Param::getInstance().RemoteOperationResponse.remote_configuration_response.device_id = ui->lineEdit_RemoteConfigurationResponse_device_id->text();
    Global_Param::getInstance().RemoteOperationResponse.remote_configuration_response.failureReason = ui->lineEdit_RemoteControlResponse_failureReason->text();
    Global_Param::getInstance().RemoteOperationResponse.remote_configuration_response.configuration_info = Global_Param::getInstance().ACpowercharger.LocalConfiguration_info.configuration_info;

    Global_Param::getInstance().RemoteOperationResponse.remote_control_response.request_id = ui->lineEdit_RemoteControlResponse_request_id->text();
    Global_Param::getInstance().RemoteOperationResponse.remote_control_response.device_id = ui->lineEdit_RemoteControlResponse_device_id->text();
    Global_Param::getInstance().RemoteOperationResponse.remote_control_response.failureReason = ui->lineEdit_RemoteControlResponse_failureReason->text();

    Global_Param::getInstance().RemoteOperationResponse.remote_upgrade_response.request_id = ui->lineEdit_RemoteUpgradeResponse_request_id->text();
    Global_Param::getInstance().RemoteOperationResponse.remote_upgrade_response.device_id = ui->lineEdit_RemoteUpgradeResponse_device_id->text();


    SetData();

    this->accept();
}

void RemoteOperationResponseDialog::on_pushButton_quit_clicked()
{
    this->reject();
}

void RemoteOperationResponseDialog::on_pushButton_LocalConfigurationInfo_clicked()
{
    m_LocalConfigurationDialog->show();
    m_LocalConfigurationDialog->move ((QApplication::desktop()->width() - this->width())/2,(QApplication::desktop()->height() - this->height())/2);
    m_LocalConfigurationDialog->setFixedSize(800,600);
}

void RemoteOperationResponseDialog::SetData(){
    m_RemoteOperationResponseData.Clear();

    if(ui->checkBox_RemoteConfigurationResponse->isChecked()){
        RemoteConfigurationResponse* RemoteConfigurationResponse_info = m_RemoteOperationResponseData.mutable_remote_configuration_response();
        if(ui->checkBox_RemoteConfigurationResponse_request_id->isChecked())
            RemoteConfigurationResponse_info->set_request_id(Global_Param::getInstance().RemoteOperationResponse.remote_configuration_response.request_id.toUtf8());
        if(ui->checkBox_RemoteConfigurationResponse_device_id->isChecked())
            RemoteConfigurationResponse_info->set_device_id(Global_Param::getInstance().RemoteOperationResponse.remote_configuration_response.device_id.toUtf8());
        if(ui->checkBox_RemoteConfigurationResponseType->isChecked())
            RemoteConfigurationResponse_info->set_remote_configuration_response_type(Global_Param::getInstance().RemoteOperationResponse.remote_configuration_response.remote_configuration_response_type);
        if(ui->checkBox_RemoteConfigurationResponse_failureReason->isChecked())
            RemoteConfigurationResponse_info->set_failurereason(Global_Param::getInstance().RemoteOperationResponse.remote_configuration_response.failureReason.toUtf8());
        if(ui->checkBox_LocalConfigurationInfo->isChecked())
        {
            Global_Param::getInstance().RemoteOperationResponse.remote_configuration_response.configuration_info = Global_Param::getInstance().ACpowercharger.LocalConfiguration_info.configuration_info;
            if(m_LocalConfigurationDialog->Get_checkBox_LocalConfigurationInfo())
            {
                LocalConfigurationInfo* LocalConfigurationInfo_data = RemoteConfigurationResponse_info->add_configuration_info();
                if(m_LocalConfigurationDialog->Get_checkBox_configuration_key())
                    LocalConfigurationInfo_data->set_configuration_key(Global_Param::getInstance().RemoteOperationResponse.remote_configuration_response.configuration_info.configuration_key.toUtf8());
                if(m_LocalConfigurationDialog->Get_checkBox_configuration_value())
                    LocalConfigurationInfo_data->set_configuration_value(Global_Param::getInstance().RemoteOperationResponse.remote_configuration_response.configuration_info.configuration_value.toUtf8());
                if(m_LocalConfigurationDialog->Get_checkBox_LocalConfigurationInfoAccessType())
                    LocalConfigurationInfo_data->set_local_configuration_info_access_type(Global_Param::getInstance().RemoteOperationResponse.remote_configuration_response.configuration_info.local_configuration_info_access_type);
                if(m_LocalConfigurationDialog->Get_checkBox_has_been_updated())
                    LocalConfigurationInfo_data->set_has_been_updated(Global_Param::getInstance().RemoteOperationResponse.remote_configuration_response.configuration_info.has_been_updated.toInt());
                if(m_LocalConfigurationDialog->Get_checkBox_failureReason())
                    LocalConfigurationInfo_data->set_failurereason(Global_Param::getInstance().RemoteOperationResponse.remote_configuration_response.configuration_info.failureReason.toUtf8());
            }

        }
    }
    if(ui->checkBox_RemoteConfigurationResponse->isChecked()){
        RemoteControlResponse* RemoteControlResponse_info = m_RemoteOperationResponseData.mutable_remote_control_response();
        if(ui->checkBox_RemoteControlResponse_request_id->isChecked())
            RemoteControlResponse_info->set_request_id(Global_Param::getInstance().RemoteOperationResponse.remote_control_response.request_id.toUtf8());
        if(ui->checkBox_RemoteControlResponse_device_id->isChecked())
            RemoteControlResponse_info->set_device_id(Global_Param::getInstance().RemoteOperationResponse.remote_control_response.device_id.toUtf8());
        if(ui->checkBox_RemoteControlResponseType->isChecked())
            RemoteControlResponse_info->set_remote_control_response_type(Global_Param::getInstance().RemoteOperationResponse.remote_control_response.remote_control_response_type);
        if(ui->checkBox_RemoteControlResponse_failureReason->isChecked())
            RemoteControlResponse_info->set_failurereason(Global_Param::getInstance().RemoteOperationResponse.remote_control_response.failureReason.toUtf8());
    }
    if(ui->checkBox_RemoteUpgradeResponse->isChecked()){
        RemoteUpgradeResponse* RemoteUpgradeResponse_info = m_RemoteOperationResponseData.mutable_remote_upgrade_response();
        if(ui->checkBox_RemoteUpgradeResponse_request_id->isChecked())
            RemoteUpgradeResponse_info->set_request_id(Global_Param::getInstance().RemoteOperationResponse.remote_upgrade_response.request_id.toUtf8());
        if(ui->checkBox_RemoteUpgradeResponse_device_id->isChecked())
            RemoteUpgradeResponse_info->set_device_id(Global_Param::getInstance().RemoteOperationResponse.remote_upgrade_response.device_id.toUtf8());
    }

}
