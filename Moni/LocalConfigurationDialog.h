#ifndef LOCALCONFIGURATIONDIALOG_H
#define LOCALCONFIGURATIONDIALOG_H

#include <QDialog>

namespace Ui {
class LocalConfigurationDialog;
}

class LocalConfigurationDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LocalConfigurationDialog(QWidget *parent = 0);
    ~LocalConfigurationDialog();

    bool Get_checkBox_full();

    bool Get_checkBox_LocalConfigurationInfo();

    bool Get_checkBox_configuration_key();

    bool Get_checkBox_configuration_value();

    bool Get_checkBox_LocalConfigurationInfoAccessType();

    bool Get_checkBox_has_been_updated();

    bool Get_checkBox_failureReason();


private slots:
    void on_pushButton_save_clicked();

    void on_pushButton_quit_clicked();

private:
    Ui::LocalConfigurationDialog *ui;
};

#endif // LOCALCONFIGURATIONDIALOG_H
