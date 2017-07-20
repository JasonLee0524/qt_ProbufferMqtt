#ifndef REMOTEOPERATIONDIALOG_H
#define REMOTEOPERATIONDIALOG_H

#include <QDialog>
#include "Protobuf/messageall.pb.h"
namespace Ui {
class RemoteOperationDialog;
}

class RemoteOperationDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RemoteOperationDialog(QWidget *parent = 0);
    ~RemoteOperationDialog();

    RemoteOperation m_RemoteOperationData;

private slots:
    void on_pushButton_save_clicked();

    void on_pushButton_quit_clicked();

private:
    Ui::RemoteOperationDialog *ui;
    void SetData();
};

#endif // REMOTEOPERATIONDIALOG_H
