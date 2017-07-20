#ifndef BASICINFODIALOG_H
#define BASICINFODIALOG_H

#include <QDialog>

namespace Ui {
class BasicInfoDialog;
}

class BasicInfoDialog : public QDialog
{
    Q_OBJECT

public:
    explicit BasicInfoDialog(QWidget *parent = 0);
    ~BasicInfoDialog();


    bool Get_checkBox_power_charger_type();

    bool Get_checkBox_charging_connector_quantity();

    bool Get_checkBox_power();

    bool Get_checkBox_software_version();

    bool Get_checkBox_hardware_version();

    bool Get_checkBox_ServiceState();

    bool Get_checkBox_ServiceStateReason();

    bool Get_checkBox_CommonBasicInfo();

    bool Get_checkBox_ServiceStateInfo();

private slots:
    void on_pushButton_save_clicked();

    void on_pushButton_quit_clicked();

private:
    Ui::BasicInfoDialog *ui;
};

#endif // BASICINFODIALOG_H
