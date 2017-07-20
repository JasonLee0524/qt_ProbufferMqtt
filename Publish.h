#ifndef PUBLISH_H
#define PUBLISH_H

#include <QWidget>
#include "mqttform.h"
namespace Ui {
class Publish;
}

class Publish : public MqttForm
{
    Q_OBJECT

public:
    explicit Publish(QWidget *parent = 0);
    ~Publish();

private slots:
    void on_pubButton_clicked();

private:
    Ui::Publish *ui;


};

#endif // PUBLISH_H
