#ifndef MY_SETTINGS_DIALOG_H
#define MY_SETTINGS_DIALOG_H

#include <QDialog>

namespace Ui {
class my_settings_dialog;
}

class my_settings_dialog : public QDialog
{
    Q_OBJECT

public:
    explicit my_settings_dialog(QWidget *parent = nullptr);
    ~my_settings_dialog();

    int getRows();
    int getColumns();

private slots:
    void on_btn_start_game_clicked();

private:
    Ui::my_settings_dialog *ui;

    int rows = 4;
    int columns = 4;
    QString imageURL;
};

#endif // MY_SETTINGS_DIALOG_H
