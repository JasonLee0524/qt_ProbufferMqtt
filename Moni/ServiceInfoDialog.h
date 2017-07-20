#ifndef SERVICEINFODIALOG_H
#define SERVICEINFODIALOG_H

#include <QDialog>

namespace Ui {
class ServiceInfoDialog;
}

class ServiceInfoDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ServiceInfoDialog(QWidget *parent = 0);
    ~ServiceInfoDialog();


    bool Get_checkBox_ServiceEvent();

    bool Get_checkBox_service_id();

    bool Get_checkBox_charging_event_timestamp();

    bool Get_checkBox_charging_connector_id();

    bool Get_checkBox_realtime_charged_energy();

    bool Get_checkBox_charged_energy_total();

    bool Get_checkBox_ServiceFinishResult();



private slots:
    void on_pushButton_save_clicked();

    void on_pushButton_quit_clicked();

private:
    Ui::ServiceInfoDialog *ui;
};

#endif // SERVICEINFODIALOG_H
