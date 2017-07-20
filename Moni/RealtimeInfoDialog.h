#ifndef REALTIMEINFODIALOG_H
#define REALTIMEINFODIALOG_H

#include <QDialog>

namespace Ui {
class RealtimeInfoDialog;
}

class RealtimeInfoDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RealtimeInfoDialog(QWidget *parent = 0);
    ~RealtimeInfoDialog();


    bool Get_checkBox_ConnectivityState();

    bool Get_checkBox_ChargingConnector();

    bool Get_checkBox_NetworkOperator();

    bool Get_checkBox_NetworkType();

    bool Get_checkBox_DeviceWorkState();

    bool Get_checkBox_charging_connector_id();

    bool Get_checkBox_ChargingConnectorWorkState();

    bool Get_checkBox_ChargingConnectorConnectionState();

    bool Get_checkBox_ChargingConnectorFaultState();

    bool Get_checkBox_PowerChargerConnectorOutputType();

    bool Get_checkBox_PowerChargerConnectorOutputVoltage();

    bool Get_checkBox_power_charger_connector_rated_output_power();

    bool Get_checkBox_realtime_output_voltage();

    bool Get_checkBox_realtime_output_current();


private slots:
    void on_pushButton_save_clicked();

    void on_pushButton_quit_clicked();

private:
    Ui::RealtimeInfoDialog *ui;
};

#endif // REALTIMEINFODIALOG_H
