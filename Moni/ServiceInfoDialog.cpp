#include "ServiceInfoDialog.h"
#include "ui_ServiceInfoDialog.h"
#include <QDebug>
#include "Global_Param.h"

ServiceInfoDialog::ServiceInfoDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ServiceInfoDialog)
{
    ui->setupUi(this);
 //  this->setAttribute(Qt::WA_DeleteOnClose);

    //默认全选中
    ui->checkBox_service_id->setChecked(true);
    ui->checkBox_ServiceEvent->setChecked(true);
    ui->checkBox_charging_event_timestamp->setChecked(true);
    ui->checkBox_charging_connector_id->setChecked(true);
    ui->checkBox_realtime_charged_energy->setChecked(true);
    ui->checkBox_charged_energy_total->setChecked(true);
    ui->checkBox_ServiceFinishResult->setChecked(true);

    ui->comboBox_ServiceEvent->addItem(tr("开始"),0);
    ui->comboBox_ServiceEvent->addItem(tr("结束"),1);

    ui->comboBox_ServiceFinishResult->addItem(tr("成功"),0);
    ui->comboBox_ServiceFinishResult->addItem(tr("失败"),1);


    ui->lineEdit_service_id->setText(Global_Param::getInstance().ACpowercharger.service_info.service_id);
    ui->lineEdit_charging_event_timestamp->setText(Global_Param::getInstance().ACpowercharger.service_info.charging_event_timestamp);
    ui->lineEdit_charging_connector_id->setText(Global_Param::getInstance().ACpowercharger.service_info.charging_connector_id);
    ui->lineEdit_realtime_charged_energy->setText(Global_Param::getInstance().ACpowercharger.service_info.realtime_charged_energy);
    ui->lineEdit_charged_energy_total->setText(Global_Param::getInstance().ACpowercharger.service_info.charged_energy_total);
    ui->comboBox_ServiceEvent->setCurrentIndex(Global_Param::getInstance().ACpowercharger.service_info.service_event);
    ui->comboBox_ServiceFinishResult->setCurrentIndex(Global_Param::getInstance().ACpowercharger.service_info.service_finish_result);

}

ServiceInfoDialog::~ServiceInfoDialog()
{
    qDebug()<<"~ServiceInfoDialog";
    delete ui;
}

void ServiceInfoDialog::on_pushButton_save_clicked()
{
    switch (ui->comboBox_ServiceEvent->currentData().toInt()) {
    case 0:
        Global_Param::getInstance().ACpowercharger.service_info.service_event = SE_START;
        break;
    case 1:
        Global_Param::getInstance().ACpowercharger.service_info.service_event = SE_FINISH;
        break;
    default:
        break;
    }

    switch (ui->comboBox_ServiceFinishResult->currentData().toInt()) {
    case 0:
        Global_Param::getInstance().ACpowercharger.service_info.service_finish_result = SFR_OK;
        break;
    case 1:
        Global_Param::getInstance().ACpowercharger.service_info.service_finish_result = SFR_ERROR;
        break;
    default:
        break;
    }

    Global_Param::getInstance().ACpowercharger.service_info.service_id = ui->lineEdit_service_id->text();
    Global_Param::getInstance().ACpowercharger.service_info.charging_event_timestamp = ui->lineEdit_charging_event_timestamp->text();
    Global_Param::getInstance().ACpowercharger.service_info.charging_connector_id = ui->lineEdit_charging_connector_id->text();
    Global_Param::getInstance().ACpowercharger.service_info.realtime_charged_energy = ui->lineEdit_realtime_charged_energy->text();
    Global_Param::getInstance().ACpowercharger.service_info.charged_energy_total = ui->lineEdit_charged_energy_total->text();


    this->accept();
}

void ServiceInfoDialog::on_pushButton_quit_clicked()
{
    this->reject();
}


bool ServiceInfoDialog::Get_checkBox_ServiceEvent(){
    return ui->checkBox_ServiceEvent->isChecked();
}

bool ServiceInfoDialog::Get_checkBox_service_id(){
    return ui->checkBox_service_id->isChecked();
}

bool ServiceInfoDialog::Get_checkBox_charging_event_timestamp(){
    return ui->checkBox_charging_event_timestamp->isChecked();
}

bool ServiceInfoDialog::Get_checkBox_charging_connector_id(){
    return ui->checkBox_charging_connector_id->isChecked();
}

bool ServiceInfoDialog::Get_checkBox_realtime_charged_energy(){
    return ui->checkBox_realtime_charged_energy->isChecked();
}

bool ServiceInfoDialog::Get_checkBox_charged_energy_total(){
    return ui->checkBox_charged_energy_total->isChecked();
}

bool ServiceInfoDialog::Get_checkBox_ServiceFinishResult(){
    return ui->checkBox_ServiceFinishResult->isChecked();
}

