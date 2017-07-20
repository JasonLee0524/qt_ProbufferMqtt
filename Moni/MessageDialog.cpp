#include "MessageDialog.h"
#include "ui_MessageDialog.h"
#include "Global_Param.h"
#include <QDebug>

MessageDialog::MessageDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MessageDialog)
{
    ui->setupUi(this);

    ui->checkBox_version->setChecked(true);
    ui->checkBox_id->setChecked(true);
    ui->checkBox_publish_ts->setChecked(true);
    ui->checkBox_ttl->setChecked(true);
    ui->checkBox_MessageType->setChecked(true);
    ui->checkBox_sub_type->setChecked(true);
    ui->checkBox_ParamType->setChecked(true);
    ui->checkBox_ParamType_key->setChecked(true);
    ui->checkBox_ParamType_value->setChecked(true);

    ui->comboBox_MessageType->addItem("NOTIFICATION",0);
    ui->comboBox_MessageType->addItem("CONTROL_COMMAND",1);
    ui->comboBox_MessageType->addItem("COMMAND_RESULT",2);
    ui->comboBox_MessageType->addItem("DATA_REPORT",3);
    ui->comboBox_MessageType->addItem("CLIENT_STATUS",4);

    ui->comboBox_ParamType_key->addItem("ACPowerCharger",0);
    ui->comboBox_ParamType_key->addItem("RemoteOperation",1);
    ui->comboBox_ParamType_key->addItem("RemoteOperationResponse",2);


    ui->lineEdit_version->setText(Global_Param::getInstance().message.version);
    ui->lineEdit_id->setText(Global_Param::getInstance().message.id);
    ui->lineEdit_publish_ts->setText(Global_Param::getInstance().message.publish_ts);
    ui->lineEdit_ttl->setText(Global_Param::getInstance().message.ttl);
    ui->lineEdit_sub_type->setText(Global_Param::getInstance().message.sub_type);
   // ui->lineEdit_ParamType_key->setText(Global_Param::getInstance().message.params.ParamType_Proto_key);
    if(Global_Param::getInstance().message.params.ParamType_Proto_key == "ACPowerCharger")
         ui->comboBox_ParamType_key->setCurrentIndex(0);
    if(Global_Param::getInstance().message.params.ParamType_Proto_key == "RemoteOperation")
         ui->comboBox_ParamType_key->setCurrentIndex(1);
    if(Global_Param::getInstance().message.params.ParamType_Proto_key == "RemoteOperationResponse")
         ui->comboBox_ParamType_key->setCurrentIndex(2);

    ui->comboBox_MessageType->setCurrentIndex(Global_Param::getInstance().message.type);

}

MessageDialog::~MessageDialog()
{
    delete ui;
}

void MessageDialog::on_pushButton_save_clicked()
{
    Global_Param::getInstance().message.version = ui->lineEdit_version->text();
    Global_Param::getInstance().message.id = ui->lineEdit_id->text();
    Global_Param::getInstance().message.publish_ts = ui->lineEdit_publish_ts->text();
    Global_Param::getInstance().message.ttl = ui->lineEdit_ttl->text();
    Global_Param::getInstance().message.sub_type = ui->lineEdit_sub_type->text();
 //   Global_Param::getInstance().message.params.ParamType_Proto_key = ui->lineEdit_ParamType_key->text();
    switch (ui->comboBox_ParamType_key->currentData().toInt()) {
    case 0:
        Global_Param::getInstance().message.params.ParamType_Proto_key = "ACPowerCharger";
        break;
    case 1:
        Global_Param::getInstance().message.params.ParamType_Proto_key = "RemoteOperation";
        break;
    case 2:
        Global_Param::getInstance().message.params.ParamType_Proto_key = "RemoteOperationResponse";
        break;
    default:
        break;
    }

    switch (ui->comboBox_MessageType->currentData().toInt()) {
    case 0:
        Global_Param::getInstance().message.type = Message_MessageType_NOTIFICATION;
        break;
    case 1:
        Global_Param::getInstance().message.type = Message_MessageType_CONTROL_COMMAND;
        break;
    case 2:
        Global_Param::getInstance().message.type = Message_MessageType_COMMAND_RESULT;
        break;
    case 3:
        Global_Param::getInstance().message.type = Message_MessageType_DATA_REPORT;
        break;
    case 4:
        Global_Param::getInstance().message.type = Message_MessageType_CLIENT_STATUS;
        break;
    default:
        break;
    }
    this->accept();
}

void MessageDialog::on_pushButton_quit_clicked()
{
    this->reject();
}

bool MessageDialog::Get_checkBox_version(){
    return ui->checkBox_version->isChecked();
}

bool MessageDialog::Get_checkBox_id(){
    return ui->checkBox_id->isChecked();
}

bool MessageDialog::Get_checkBox_publish_ts(){
    return ui->checkBox_publish_ts->isChecked();
}

bool MessageDialog::Get_checkBox_ttl(){
    return ui->checkBox_ttl->isChecked();
}

bool MessageDialog::Get_checkBox_MessageType(){
    return ui->checkBox_MessageType->isChecked();
}

bool MessageDialog::Get_checkBox_sub_type(){
    return ui->checkBox_sub_type->isChecked();
}

bool MessageDialog::Get_checkBox_ParamType(){
    return ui->checkBox_ParamType->isChecked();
}

bool MessageDialog::Get_checkBox_ParamType_key(){
    return ui->checkBox_ParamType_key->isChecked();
}

bool MessageDialog::Get_checkBox_ParamType_value(){
    return ui->checkBox_ParamType_value->isChecked();
}
