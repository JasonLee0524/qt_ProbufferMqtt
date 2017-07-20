#ifndef TESTDIALOG_H
#define TESTDIALOG_H

#include <QDialog>
#include "mqttform.h"

namespace Ui {
class TestDialog;
}

class TestDialog : public QDialog, MqttForm
{
    Q_OBJECT

public:
    explicit TestDialog(QWidget *parent = 0,QMQTT::Client *client = 0);
    ~TestDialog();

private slots:
    void on_pushButton_start_clicked();

    void on_pushButton_finish_clicked();

private:
    Ui::TestDialog *ui;
};

#endif // TESTDIALOG_H
