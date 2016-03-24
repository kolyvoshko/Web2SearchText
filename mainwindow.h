#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "Logic/program_logic.h"
#include <QMainWindow>
#include <QTimer>
#include <QThread>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);

    ~MainWindow();

private:
    Ui::MainWindow *ui;
    ProgramLogic *pl;

private slots:
    void start();
    void pause() {pl->pause();}
    void stop()  {pl->stop();}


};

#endif // MAINWINDOW_H
