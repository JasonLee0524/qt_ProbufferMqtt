#ifndef TESTWIDGET_H
#define TESTWIDGET_H

#include <QWidget>
#include "mqttform.h"
namespace Ui {
class TestWidget;
}

class TestWidget : public MqttForm
{
    Q_OBJECT

public:
    explicit TestWidget(QWidget *parent = 0,QMQTT::Client *client = 0);
    ~TestWidget();

private slots:
    void on_pushButton_start_clicked();

    void on_pushButton_finish_clicked();

    void on_pushButton_clicked();

    void on_pushButton_settime_clicked();

private:
    Ui::TestWidget *ui;
};

#endif // TESTWIDGET_H
