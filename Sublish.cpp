#include "Sublish.h"
#include "ui_Sublish.h"

Sublish::Sublish(QWidget *parent) :
    MqttForm(parent),
    ui(new Ui::Sublish)
{
    ui->setupUi(this);

}

Sublish::~Sublish()
{

    delete ui;
}

void Sublish::on_unsubButton_clicked()
{
    QString topic = ui->topicLineEdit->text();
    _client->unsubscribe(topic);

}

void Sublish::on_subButton_clicked()
{
    QString topic = ui->topicLineEdit->text();
    quint8 qos = ui->qosLineEdit->text().toInt();
    qDebug("Qos: %d", qos);
    _client->subscribe(topic, qos);
}
