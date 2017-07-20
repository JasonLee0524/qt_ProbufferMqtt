#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <fstream>
#include <QDebug>
#include "Protobuf/messageall.pb.h"
#include <QTextCodec>
#include <QDesktopWidget>
#include <QTime>
MainWindow::MainWindow(QMQTT::Client *client, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_client = client;
    this->setAttribute(Qt::WA_DeleteOnClose);
    ui->ConWidget->init(m_client);
    ui->PubWidget->init(m_client);
    ui->SubWidget->init(m_client);
    m_TestWidget = NULL;
    m_Moni =  NULL;


    ui->tabWidget->setTabEnabled(ui->tabWidget->indexOf(ui->PubWidget),false);
    ui->tabWidget->setTabEnabled(ui->tabWidget->indexOf(ui->SubWidget),false);
  //  ui->pushButton_moniqi->setEnabled(false);
    ui->pushButton_test->setEnabled(false);
    //mainwindow slots
    connect(m_client, SIGNAL(connected()), this, SLOT(onMQTT_Connected()));
    connect(m_client, SIGNAL(disconnected()), this, SLOT(onMQTT_disConnected()));
    connect(m_client, SIGNAL(error(QMQTT::ClientError)),this,SLOT(onMQTT_error(QMQTT::ClientError)));

    connect(m_client,SIGNAL(published(const QMQTT::Message &)),this,SLOT(onMQTT_Published(const QMQTT::Message &)));
    connect(m_client, SIGNAL(received(const QMQTT::Message &)), this, SLOT(onMQTT_Received(const QMQTT::Message &)));

    connect(m_client, SIGNAL(subscribed(const QString &)), this, SLOT(onMQTT_subscribed(const QString &)));
    connect(m_client, SIGNAL(unsubscribed(const QString &)), this, SLOT(onMQTT_unsubscribed(const QString &)));

}

MainWindow::~MainWindow()
{
    if(m_Moni!= NULL){
        m_Moni->deleteLater();
        m_Moni = NULL;
    }
    if(m_TestWidget != NULL){
        delete m_TestWidget;
       // m_TestWidget->deleteLater();
        m_TestWidget = NULL;
    }
    if(m_client != NULL){
        m_client->disconnected();
        m_client->deleteLater();
        m_client = NULL;
    }

    delete ui;
}


void MainWindow::log(const QString & msg)
{
    qDebug()<<msg;
}

void MainWindow::onMQTT_Connected(){
    if(m_client->hostName() == ""){
        log(tr("connected to %1:%2").arg(m_client->host().toString()).arg(m_client->port()));
    }
    else{
        log(tr("connected to %1:%2").arg(m_client->hostName()).arg(m_client->port()));
    }


    ui->tabWidget->setTabEnabled(ui->tabWidget->indexOf(ui->PubWidget),true);
    ui->tabWidget->setTabEnabled(ui->tabWidget->indexOf(ui->SubWidget),true);
  //  ui->pushButton_moniqi->setEnabled(true);
    ui->pushButton_test->setEnabled(true);
}

void MainWindow::onMQTT_disConnected(){
    log(tr("disconnected"));
    ui->tabWidget->setTabEnabled(ui->tabWidget->indexOf(ui->PubWidget),false);
    ui->tabWidget->setTabEnabled(ui->tabWidget->indexOf(ui->SubWidget),false);
  //  ui->pushButton_moniqi->setEnabled(false);
     ui->pushButton_test->setEnabled(false);

}

void MainWindow::onMQTT_Published(const QMQTT::Message & message){
    log(tr("message published to %1").arg(message.topic()));
   // log("Pubilsh:"+message.payload());
}

void MainWindow::onMQTT_Received(const QMQTT::Message &message)
{
   log(tr("message recevied from %1: qos=%2").arg(message.topic()).arg(message.qos()));
   qDebug()<<"message:"<<message.payload().toHex();
   qDebug()<<"message_size1:"<<message.payload().size();

   QByteArray encodedString = message.payload();
   QTextCodec *codec = QTextCodec::codecForName("UTF-8");
   QString str = codec->toUnicode(encodedString);
   std::string str_message = str.toStdString();
   qDebug()<<"message_size2:"<<str_message.size();


   Message messageResp;
   messageResp.Clear();
   messageResp.ParseFromString(str_message);
   qDebug()<<messageResp.version();
   qDebug()<<QString::fromStdString(messageResp.id());
   qDebug()<<messageResp.publish_ts();
   qDebug()<<messageResp.ttl();
   qDebug()<<messageResp.type();
   qDebug()<<QString::fromStdString(messageResp.sub_type());

   for(int i = 0 ; i < messageResp.params_size(); i++){
       if(messageResp.params(i).key() == "ACPowerCharger"){
         std::string str_logonResp = messageResp.params(i).value();
         ACPowerCharger logonResp;
         logonResp.ParseFromString(str_logonResp);

         qDebug()<<QString::fromStdString(logonResp.device_id());
         qDebug()<<logonResp.message_timestamp();


         qDebug()<<"basicinfo";
         qDebug()<<logonResp.basicinfo().power_charger_type();
         qDebug()<<logonResp.basicinfo().charging_connector_quantity();
         qDebug()<<QString::number(logonResp.basicinfo().power());
         qDebug()<<QString::fromStdString(logonResp.basicinfo().common_basic_info().software_version());
         qDebug()<<QString::fromStdString(logonResp.basicinfo().common_basic_info().hardware_version());
         qDebug()<<logonResp.basicinfo().common_basic_info().service_state_info().service_state();
         qDebug()<<logonResp.basicinfo().common_basic_info().service_state_info().service_state_reason();

         qDebug()<<"RealtimeInfo";
         qDebug()<<logonResp.realtime_info().connectivity_state().network_operator();
         qDebug()<<logonResp.realtime_info().connectivity_state().network_type();
         qDebug()<<logonResp.realtime_info().device_work_state();
         for(int num = 0; num < logonResp.realtime_info().charging_connector_size(); num++){
             qDebug()<<QString::fromStdString(logonResp.realtime_info().charging_connector(num).charging_connector_id());
             qDebug()<<logonResp.realtime_info().charging_connector(num).charging_connector_work_state();
             qDebug()<<logonResp.realtime_info().charging_connector(num).charging_connector_connection_state();
             qDebug()<<logonResp.realtime_info().charging_connector(num).charging_connector_fault_state();
             qDebug()<<logonResp.realtime_info().charging_connector(num).power_charger_connector_output_type();
         }
         for(int j = 0 ; j < logonResp.alarms_size(); j++){
                 qDebug()<<"alarm";
                 qDebug()<<logonResp.alarms(j).alarm_type_id();
                 qDebug()<<logonResp.alarms(j).alarm_timestamp();
                 qDebug()<<logonResp.alarms(j).alarm_state();
         }
      }
   }

}

void MainWindow::onMQTT_subscribed(const QString &topic)
{
    log(tr("subscribed %1").arg(topic));
}

void MainWindow::onMQTT_unsubscribed(const QString &topic)
{
    log(tr("unsubscribed %1").arg(topic));
}

void MainWindow::onMQTT_error(QMQTT::ClientError err)
{
    //todo: should emit on server suback

    QString errInfo;

    switch(err) {
    // 0	The connection was refused by the peer (or timed out).
    case QAbstractSocket::ConnectionRefusedError:
        errInfo = tr("Connection Refused");
    //	 1	The remote host closed the connection. Note that the client socket (i.e., this socket) will be closed after the remote close notification has been sent.
    case QAbstractSocket::RemoteHostClosedError:
        errInfo = tr("Remote Host Closed");
    //	2	The host address was not found.
    case QAbstractSocket::HostNotFoundError:
        errInfo = tr("Host Not Found Error");
    // 	3	The socket operation failed because the application lacked the required privileges.
    case QAbstractSocket::SocketAccessError:
        errInfo = tr("Socket Access Error");
    // 	4	The local system ran out of resources (e.g., too many sockets).
    case QAbstractSocket::SocketResourceError:
        errInfo = tr("Socket Resource Error");
    // 	5	The socket operation timed out.
    case QAbstractSocket::SocketTimeoutError:
        errInfo = tr("Socket Timeout Error");
    default:
        errInfo = tr("Socket Error");
    }

    log(errInfo);

}

void MainWindow::on_pushButton_moniqi_clicked()
{
    m_Moni = new Moni_main(NULL,m_client);
    m_Moni->login();
    m_Moni->show();
    m_Moni->move ((QApplication::desktop()->width() - this->width())/2,(QApplication::desktop()->height() - this->height())/2);
 //   m_Moni->setFixedSize(800,600);
}

void MainWindow::on_pushButton_test_clicked()
{
    m_TestWidget = new TestWidget (NULL,m_client);
   // m_TestWidget->setAttribute(Qt::WA_ShowModal,true);
    m_TestWidget->show();
    m_TestWidget->move ((QApplication::desktop()->width() - this->width())/2,(QApplication::desktop()->height() - this->height())/2);
    m_TestWidget->setFixedSize(800,600);
}
