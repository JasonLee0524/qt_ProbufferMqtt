#include "LocalConfigurationDialog.h"
#include "ui_LocalConfigurationDialog.h"
#include "Global_Param.h"
#include <QDebug>

LocalConfigurationDialog::LocalConfigurationDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LocalConfigurationDialog)
{
    ui->setupUi(this);

    ui->checkBox_full->setChecked(true);
    ui->checkBox_LocalConfigurationInfo->setChecked(true);
        ui->checkBox_configuration_key->setChecked(true);
        ui->checkBox_configuration_value->setChecked(true);
        ui->checkBox_LocalConfigurationInfoAccessType->setChecked(true);
        ui->checkBox_has_been_updated->setChecked(true);
        ui->checkBox_failureReason->setChecked(true);


    ui->comboBox_LocalConfigurationInfoAccessType->addItem(tr("只读"),0);
    ui->comboBox_LocalConfigurationInfoAccessType->addItem(tr("只写"),1);


    ui->lineEdit_full->setText(Global_Param::getInstance().ACpowercharger.LocalConfiguration_info.full);
    ui->lineEdit_configuration_key->setText(Global_Param::getInstance().ACpowercharger.LocalConfiguration_info.configuration_info.configuration_key);
    ui->lineEdit_configuration_value->setText(Global_Param::getInstance().ACpowercharger.LocalConfiguration_info.configuration_info.configuration_value);
    ui->lineEdit_has_been_updated->setText(Global_Param::getInstance().ACpowercharger.LocalConfiguration_info.configuration_info.has_been_updated);
    ui->lineEdit_failureReason->setText(Global_Param::getInstance().ACpowercharger.LocalConfiguration_info.configuration_info.failureReason);

    ui->comboBox_LocalConfigurationInfoAccessType->setCurrentIndex(Global_Param::getInstance().ACpowercharger.LocalConfiguration_info.configuration_info.local_configuration_info_access_type);

}

LocalConfigurationDialog::~LocalConfigurationDialog()
{
    delete ui;
}

void LocalConfigurationDialog::on_pushButton_save_clicked()
{
    if(ui->comboBox_LocalConfigurationInfoAccessType->currentData().toInt() == 0)
        Global_Param::getInstance().ACpowercharger.LocalConfiguration_info.configuration_info.local_configuration_info_access_type = LCIAT_READONLY;
    if(ui->comboBox_LocalConfigurationInfoAccessType->currentData().toInt() == 1)
        Global_Param::getInstance().ACpowercharger.LocalConfiguration_info.configuration_info.local_configuration_info_access_type = LCIAT_READWRITE;

    Global_Param::getInstance().ACpowercharger.LocalConfiguration_info.full = ui->lineEdit_full->text();
    Global_Param::getInstance().ACpowercharger.LocalConfiguration_info.configuration_info.configuration_key = ui->lineEdit_configuration_key->text();
    Global_Param::getInstance().ACpowercharger.LocalConfiguration_info.configuration_info.configuration_value = ui->lineEdit_configuration_value->text();
    Global_Param::getInstance().ACpowercharger.LocalConfiguration_info.configuration_info.has_been_updated = ui->lineEdit_has_been_updated->text();
    Global_Param::getInstance().ACpowercharger.LocalConfiguration_info.configuration_info.failureReason = ui->lineEdit_failureReason->text();


    this->accept();
}

void LocalConfigurationDialog::on_pushButton_quit_clicked()
{
    this->reject();
}

bool LocalConfigurationDialog::Get_checkBox_full(){
    return ui->checkBox_full->isChecked();
}

bool LocalConfigurationDialog::Get_checkBox_LocalConfigurationInfo(){
    return ui->checkBox_LocalConfigurationInfo->isChecked();
}

bool LocalConfigurationDialog::Get_checkBox_configuration_key(){
    return ui->checkBox_configuration_key->isChecked();
}

bool LocalConfigurationDialog::Get_checkBox_configuration_value(){
    return ui->checkBox_configuration_value->isChecked();
}


bool LocalConfigurationDialog::Get_checkBox_LocalConfigurationInfoAccessType(){
    return ui->checkBox_LocalConfigurationInfoAccessType->isChecked();
}


bool LocalConfigurationDialog::Get_checkBox_has_been_updated(){
    return ui->checkBox_has_been_updated->isChecked();
}

bool LocalConfigurationDialog::Get_checkBox_failureReason(){
    return ui->checkBox_failureReason->isChecked();
}


