#ifndef ALARMDIALOG_H
#define ALARMDIALOG_H

#include <QDialog>
#include <QCheckBox>
namespace Ui {
class AlarmDialog;
}

class AlarmDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AlarmDialog(QWidget *parent = 0);
    ~AlarmDialog();

    bool Get_checkBox_alarm_type_id();
    bool Get_checkBox_alarm_timestamp();
    bool Get_checkBox_alarm_state();


private slots:
    void on_pushButton_save_clicked();

    void on_pushButton_quit_clicked();

private:
    Ui::AlarmDialog *ui;
};

#endif // ALARMDIALOG_H
