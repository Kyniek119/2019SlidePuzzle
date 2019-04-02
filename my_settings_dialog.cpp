#include "my_settings_dialog.h"
#include "ui_my_settings_dialog.h"

my_settings_dialog::my_settings_dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::my_settings_dialog)
{
    ui->setupUi(this);
}

my_settings_dialog::~my_settings_dialog()
{
    delete ui;
}

int my_settings_dialog::getRows(){
    return this->rows;
}

int my_settings_dialog::getColumns(){
    return this->columns;
}

void my_settings_dialog::on_btn_start_game_clicked(){
    rows = ui->sb_rows->value();
    columns = ui->sb_columns->value();
    this->close();
}
