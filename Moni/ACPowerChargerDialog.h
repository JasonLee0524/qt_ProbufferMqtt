#ifndef ACPOWERCHARGERDIALOG_H
#define ACPOWERCHARGERDIALOG_H

#include <QDialog>
#include "AlarmDialog.h"
#include "BasicInfoDialog.h"
#include "RealtimeInfoDialog.h"
#include "ServiceInfoDialog.h"
#include "Protobuf/messageall.pb.h"
#include "LocalConfigurationDialog.h"
#include "RemoteOperationResponseDialog.h"
namespace Ui {
class ACPowerChargerDialog;
}

class ACPowerChargerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ACPowerChargerDialog(QWidget *parent = 0);
    ~ACPowerChargerDialog();

    ACPowerCharger m_ACPowerChargerData;

private slots:
    void on_pushButton_BasicInfo_clicked();

    void on_pushButton_RealtimeInfo_clicked();

    void on_pushButton_ServiceInfo_clicked();

    void on_pushButton_Alarm_clicked();

    void on_pushButton_save_clicked();

    void on_pushButton_quit_clicked();

    void on_pushButton_LocalConfiguration_clicked();

private:
    Ui::ACPowerChargerDialog *ui;

    void initUI();
    AlarmDialog* m_AlarmDialog;
    BasicInfoDialog* m_BasicInfoDialog;
    RealtimeInfoDialog* m_RealtimeInfoDialog;
    ServiceInfoDialog* m_ServiceInfoDialog;
    LocalConfigurationDialog* m_LocalConfigurationDialog;
};

#endif // ACPOWERCHARGERDIALOG_H
