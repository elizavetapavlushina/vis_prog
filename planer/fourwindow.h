#ifndef FOURWINDOW_H
#define FOURWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>
#include <QImage>
#include <QBuffer>
#include "thirdwindow.h"

namespace Ui {
class FourWindow;
}

class FourWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit FourWindow(QWidget *parent = 0);
    ~FourWindow();
    FourWindow *window4;
    void setDataFromTableModel(int IdColumn, int currentRow);

public slots:
    void GetDataTable(QSqlTableModel *newModel, int newCurrentRow);

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
    void on_Add_Image_clicked();
    void on_AddToData_clicked();
    void on_Exit_clicked();




private:
    Ui::FourWindow *ui;
    QSqlDatabase db;
    QString currentFile ="";
    QSqlTableModel *model;
    int currentRow;
};

#endif // FOURWINDOW_H
