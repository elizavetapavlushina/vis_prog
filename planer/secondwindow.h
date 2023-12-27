#ifndef SECONDWINDOW_H
#define SECONDWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlTableModel>

namespace Ui {
class SecondWindow;
}

class SecondWindow : public QMainWindow
{
    Q_OBJECT

public:
    SecondWindow(QWidget *parent = nullptr);
    ~SecondWindow();
    SecondWindow *window;

private:
    Ui::SecondWindow *ui;
    QString currentFile ="";

    QSqlDatabase db;
    QSqlTableModel *modelAdd;


public slots:
    void SecondGetDataTable(QSqlTableModel *newModel);

private slots:
    void on_actionNew_triggered();

    void on_actionOpen_triggered();

    void on_actionSave_as_triggered();

    void on_actionExit_triggered();

    void on_actionCopy_triggered();

    void on_actionPaste_triggered();

    void on_actionCut_triggered();

    void on_actionUndo_triggered();

    void on_actionRedo_triggered();

    void on_AddToData_clicked();
    void on_Add_Image_clicked();

    void on_Exit_clicked();
};

#endif // SECONDWINDOW_H
