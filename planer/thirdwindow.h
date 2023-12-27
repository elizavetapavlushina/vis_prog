#ifndef THIRDWINDOW_H
#define THIRDWINDOW_H

#include <QDialog>
#include <QTextStream>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QDebug>
#include <QListWidgetItem>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlQueryModel>
#include <QSqlTableModel>
#include <QSql>
#include <QSqlRelationalTableModel>
#include <QStyledItemDelegate>
#include <QTableView>
#include <QWidget>
#include <QListWidgetItem>
#include <QFormLayout>
#include <QComboBox>
#include <QStandardItem>
#include <QStringListModel>
#include <QListView>
#include <QVBoxLayout>
#include <QVector>
#include "secondwindow.h"
#include "fourwindow.h"
#include <QSettings>

namespace Ui {
class ThirdWindow;
}

class ThirdWindow : public QDialog
{
    Q_OBJECT

public:
    explicit ThirdWindow(QWidget *parent = 0);
    ~ThirdWindow();


signals:
    void SendData(QSqlTableModel*, int);
    void SecondSendData(QSqlTableModel*);


public slots:


private slots:
    void on_Delete_clicked();

    void on_tableView_clicked(const QModelIndex &index);

    void on_Open_clicked();

private:
    Ui::ThirdWindow *ui;
    QSqlDatabase db;
    int currentRow;
    QSqlTableModel *model;
    class FourWindow *fourWindow;
    class SecondWindow *secondWindow;
    QSettings *settings;
    int IdColumn;
};

#endif // THIRDWINDOW_H
