#include "Publish.h"
#include "ui_Publish.h"
#include <QDebug>
#include "Global_Param.h"
Publish::Publish(QWidget *parent) :
     MqttForm(parent),
    ui(new Ui::Publish)
{
    ui->setupUi(this);

}

Publish::~Publish()
{

    delete ui;
}


void Publish::on_pubButton_clicked()
{
    Global_Param::getInstance().m_publish = ui->topicLineEdit->text();
    qDebug()<<"m_publish:"<< Global_Param::getInstance().m_publish;
    Global_Param::getInstance().m_publishtopic = ui->qosLineEdit->text();
     qDebug()<<"m_publishtopic:"<< Global_Param::getInstance().m_publishtopic;

}
