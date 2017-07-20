#include "AlarmDialog.h"
#include "ui_AlarmDialog.h"
#include "Global_Param.h"
#include <QDebug>
AlarmDialog::AlarmDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AlarmDialog)
{
    ui->setupUi(this);
  //  this->setAttribute(Qt::WA_DeleteOnClose);

    ui->checkBox_alarm_state->setChecked(true);
    ui->checkBox_alarm_timestamp->setChecked(true);
    ui->checkBox_alarm_type_id->setChecked(true);

    ui->comboBox_alarm_state->addItem(tr("告警清除"),0);
    ui->comboBox_alarm_state->addItem(tr("告警开始"),1);


    ui->lineEdit_alarm_type_id->setText(Global_Param::getInstance().ACpowercharger.alarm.alarm_type_id);
    ui->lineEdit_alarm_timestamp->setText(Global_Param::getInstance().ACpowercharger.alarm.alarm_timestamp);
    ui->comboBox_alarm_state->setCurrentIndex(Global_Param::getInstance().ACpowercharger.alarm.alarm_state);
}

AlarmDialog::~AlarmDialog()
{
    qDebug()<<"~AlarmDialog";
    delete ui;
}

void AlarmDialog::on_pushButton_save_clicked()
{
    Global_Param::getInstance().ACpowercharger.alarm.alarm_type_id = ui->lineEdit_alarm_type_id->text();
    Global_Param::getInstance().ACpowercharger.alarm.alarm_timestamp = ui->lineEdit_alarm_timestamp->text();

    if(ui->comboBox_alarm_state->currentData().toInt() == 0)
        Global_Param::getInstance().ACpowercharger.alarm.alarm_state = AS_INACTIVE;
    if(ui->comboBox_alarm_state->currentData().toInt() == 1)
        Global_Param::getInstance().ACpowercharger.alarm.alarm_state = AS_ACTIVE;

    this->accept();
}

void AlarmDialog::on_pushButton_quit_clicked()
{
    this->reject();
}

bool AlarmDialog::Get_checkBox_alarm_type_id(){
    return ui->checkBox_alarm_type_id->isChecked();
}

bool AlarmDialog::Get_checkBox_alarm_timestamp(){
    return ui->checkBox_alarm_timestamp->isChecked();
}

bool AlarmDialog::Get_checkBox_alarm_state(){
    return ui->checkBox_alarm_state->isChecked();
}
