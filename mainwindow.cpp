#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "my_qlabel.h"
#include <QPixmap>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->lbl_Mouse_Area, SIGNAL(Mouse_Pos()), this, SLOT(Mouse_current_pos()));
    connect(ui->lbl_Mouse_Area, SIGNAL(Mouse_Pressed()), this, SLOT(Mouse_pressed()));
    connect(ui->lbl_Mouse_Area, SIGNAL(Mouse_Left()), this, SLOT(Mouse_left()));
    QPixmap pix("C:/Users/krzys/SlidePuzzle/default_board_5x5.jpg");
    ui->lbl_Mouse_Area->setPixmap(pix.scaled(ui->lbl_Mouse_Area->width(), ui->lbl_Mouse_Area->height(), Qt::KeepAspectRatio));
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
