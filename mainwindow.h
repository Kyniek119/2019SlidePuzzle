#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <puzzleboard.h>
#include "my_settings_dialog.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void Mouse_current_pos();
    void Mouse_pressed();
    void Mouse_left();
    void Board_changed();

    void on_actionNew_triggered();
    void on_actionExit_triggered();

private:
    Ui::MainWindow *ui;
    PuzzleBoard *board;
    my_settings_dialog *my_settings_dialog;
};

#endif // MAINWINDOW_H
