#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "my_board_label.h"
#include <QMessageBox>
#include <QPixmap>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->lbl_Mouse_Area, SIGNAL(Mouse_Pos()), this, SLOT(Mouse_current_pos()));
    connect(ui->lbl_Mouse_Area, SIGNAL(Mouse_Pressed()), this, SLOT(Mouse_pressed()));
    connect(ui->lbl_Mouse_Area, SIGNAL(Mouse_Left()), this, SLOT(Mouse_left()));
    connect(ui->lbl_Mouse_Area, SIGNAL(Board_Changed()), this, SLOT(Board_changed()));
    QPixmap pix(":/img/default_board_5x5.jpg");
    ui->lbl_Mouse_Area->setPixmap(pix.scaled(ui->lbl_Mouse_Area->width(), ui->lbl_Mouse_Area->height(), Qt::KeepAspectRatio));
    ui->rb_NumberView->setChecked(true);

}

MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::Mouse_current_pos(){
    ui->lbl_mouse_current_pos->setText(QString("X = %1, Y = %2").arg(ui->lbl_Mouse_Area->x).arg(ui->lbl_Mouse_Area->y));
    ui->lbl_mouse_event_name->setText("Mouse moving!");
}

void MainWindow::Mouse_pressed(){
    ui->lbl_mouse_event_name->setText("Mouse pressed!");
}

void MainWindow::Mouse_left(){
    ui->lbl_mouse_event_name->setText("Mouse left!");
}

void MainWindow::Board_changed(){
    ui->lbl_moves_count->setNum(ui->lbl_Mouse_Area->getMoveCount());
    ui->lbl_Mouse_Area->repaint();
}

void MainWindow::on_actionNew_triggered(){
    //QMessageBox::information(this, "New game", "New game will be started.");
    my_settings_dialog = new class my_settings_dialog(this);
    my_settings_dialog->setModal(true);
    my_settings_dialog->exec();
    this->board = new PuzzleBoard(my_settings_dialog->getRows(),my_settings_dialog->getColumns());
    this->board->shuffle();
    ui->lbl_Mouse_Area->initializeBoard(this->board);
    ui->lbl_Mouse_Area->printBoard();
}

void MainWindow::on_actionExit_triggered(){
    this->close();
}
