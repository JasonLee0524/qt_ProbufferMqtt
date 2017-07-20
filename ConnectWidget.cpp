#include "ConnectWidget.h"
#include "ui_ConnectWidget.h"
#include "qmqtt/qmqtt_client.h"
#include "Global_Param.h"
ConnectWidget::ConnectWidget(QWidget *parent) :
    MqttForm(parent),
    ui(new Ui::ConnectWidget)
{
    ui->setupUi(this);

}

ConnectWidget::~ConnectWidget()
{
    delete ui;
}

void ConnectWidget::on_pushButton_connect_clicked()
{
    QString clientId = ui->lineEdit_ClientId->text();
    QString username = ui->lineEdit_User->text();
    QString passwd = ui->lineEdit_Passwd->text();

    if(!_client->isConnectedToHost()) {
        QHostAddress hostAdd(ui->lineEdit_ip->text());
        _client->setHost(hostAdd);
        _client->setHostName(ui->lineEdit_HostName->text());
        _client->setPort(ui->lineEdit_port->text().toInt

                         ());
        if(!clientId.isEmpty())
            _client->setClientId(clientId);
        if(!username.isEmpty())
            _client->setUsername(username);
        if(!passwd.isEmpty())
            _client->setPassword(passwd);
        _client->connectToHost();
    }

}

void ConnectWidget::on_pushButton_disconnect_clicked()
{
    if(_client->isConnectedToHost()) {
        _client->disconnectFromHost();
    }
}


void ConnectWidget::on_pushButton_clear_clicked()
{
     ui->lineEdit_HostName->clear();
}

void ConnectWidget::on_checkBox_toggled(bool checked)
{
     Global_Param::getInstance().m_base64 = checked;
}
