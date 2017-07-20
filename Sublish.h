#ifndef SUBLISH_H
#define SUBLISH_H

#include <QWidget>
#include "mqttform.h"

namespace Ui {
class Sublish;
}

class Sublish : public MqttForm
{
    Q_OBJECT

public:
    explicit Sublish(QWidget *parent = 0);
    ~Sublish();

private slots:
    void on_unsubButton_clicked();

    void on_subButton_clicked();

private:
    Ui::Sublish *ui;

};

#endif // SUBLISH_H
