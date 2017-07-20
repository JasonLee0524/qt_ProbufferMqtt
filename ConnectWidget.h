#ifndef CONNECTWIDGET_H
#define CONNECTWIDGET_H

#include "mqttform.h"
#include <QTcpSocket>
namespace Ui {
class ConnectWidget;
}

class ConnectWidget : public MqttForm
{
    Q_OBJECT

public:
    explicit ConnectWidget(QWidget *parent = 0);
    ~ConnectWidget();


private slots:
    void on_pushButton_connect_clicked();

    void on_pushButton_disconnect_clicked();

    void on_pushButton_clear_clicked();

    void on_checkBox_toggled(bool checked);

private:
    Ui::ConnectWidget *ui;
};

#endif // CONNECTWIDGET_H
