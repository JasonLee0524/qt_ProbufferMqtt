#ifndef REMOTEOPERATIONRESPONSEDIALOG_H
#define REMOTEOPERATIONRESPONSEDIALOG_H

#include <QDialog>
#include "LocalConfigurationDialog.h"
#include "Protobuf/messageall.pb.h"
namespace Ui {
class RemoteOperationResponseDialog;
}

class RemoteOperationResponseDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RemoteOperationResponseDialog(QWidget *parent = 0);
    ~RemoteOperationResponseDialog();


    RemoteOperationResponse m_RemoteOperationResponseData;

private slots:
    void on_pushButton_save_clicked();

    void on_pushButton_quit_clicked();

    void on_pushButton_LocalConfigurationInfo_clicked();

private:
    Ui::RemoteOperationResponseDialog *ui;
    LocalConfigurationDialog* m_LocalConfigurationDialog;
    void SetData();
};

#endif // REMOTEOPERATIONRESPONSEDIALOG_H
