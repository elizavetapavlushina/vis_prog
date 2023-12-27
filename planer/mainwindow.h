#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <secondwindow.h>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>
#include <thirdwindow.h>
#include <QSettings>
#include <QTimer>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();
    void loadSettings();

    void saveSettings();

    void TimerSlot();

private:
    Ui::MainWindow *ui;
    SecondWindow *window;
    ThirdWindow *window_1;
    QSettings *settings;
    QTimer *timer;
    int ms;
    int s;
    int m;


};

#endif // MAINWINDOW_H
