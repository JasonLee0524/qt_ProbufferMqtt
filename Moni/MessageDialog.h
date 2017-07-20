#ifndef MESSAGEDIALOG_H
#define MESSAGEDIALOG_H

#include <QDialog>

namespace Ui {
class MessageDialog;
}

class MessageDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MessageDialog(QWidget *parent = 0);
    ~MessageDialog();

    bool Get_checkBox_version();

    bool Get_checkBox_id();

    bool Get_checkBox_publish_ts();

    bool Get_checkBox_ttl();

    bool Get_checkBox_MessageType();

    bool Get_checkBox_sub_type();

    bool Get_checkBox_ParamType();

    bool Get_checkBox_ParamType_key();

    bool Get_checkBox_ParamType_value();

private slots:
    void on_pushButton_save_clicked();

    void on_pushButton_quit_clicked();

private:
    Ui::MessageDialog *ui;
};

#endif // MESSAGEDIALOG_H
