#include "thirdwindow.h"
#include "ui_thirdwindow.h"
#include "secondwindow.h"
#include "fourwindow.h"
#include <QSortFilterProxyModel>


ThirdWindow::ThirdWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ThirdWindow)
{
    ui->setupUi(this);
    fourWindow = new FourWindow;
    secondWindow = new SecondWindow;
    connect(this, &ThirdWindow::SendData, fourWindow, &FourWindow::GetDataTable);
    connect(this, &ThirdWindow::SecondSendData, secondWindow, SecondWindow::SecondGetDataTable);
    setWindowTitle("School Planer.Список ваших задач/событий");
    setWindowIcon(QIcon("C:/Users/elpav/Documents/planer/images/icons8-checklist-32.png"));
    this->setFixedSize(490,544);
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("C:/Users/elpav/Documents/databaseSchoolPlaner.db");
    if(db.open()){
        qDebug() << "DataBase successfully connected";
        model = new QSqlTableModel(this, db);
        model->setTable("Activity");
        model->select();
        model->setHeaderData(1, Qt::Horizontal, "Дата");
        model->setHeaderData(4, Qt::Horizontal, "Тип");
        model->setHeaderData(6, Qt::Horizontal, "Заголовок");

        ui->tableView->setModel(model);
        ui->tableView->setColumnHidden(0,true);
        ui->tableView->setColumnHidden(2,true);
        ui->tableView->setColumnHidden(3,true);
        ui->tableView->setColumnHidden(5,true);
        ui->tableView->setColumnWidth(6,250);
        ui->tableView->setRowHeight(0,60);
        ui->tableView->setRowHeight(1,60);
        ui->tableView->setRowHeight(2,60);
        ui->tableView->setRowHeight(3,60);
        ui->tableView->setRowHeight(4,60);
        ui->tableView->setRowHeight(5,60);
        ui->tableView->setRowHeight(6,60);
        ui->tableView->setRowHeight(7,60);
        ui->tableView->setRowHeight(8,60);
        ui->tableView->setRowHeight(9,60);
        ui->tableView->setRowHeight(10,60);
        ui->tableView->setRowHeight(11,60);
        ui->tableView->setRowHeight(12,60);
        ui->tableView->setRowHeight(13,60);
        ui->tableView->setRowHeight(14,60);
        ui->tableView->setRowHeight(15,60);
        ui->tableView->setRowHeight(16,60);
        ui->tableView->setRowHeight(17,60);
        ui->tableView->setRowHeight(18,60);
        ui->tableView->setRowHeight(19,60);
        ui->tableView->setRowHeight(20,60);
        ui->tableView->setSortingEnabled(true);

        QSortFilterProxyModel *proxyModel = new QSortFilterProxyModel(parent);
        proxyModel->setSourceModel(model);
        ui->tableView->setModel(proxyModel);
        QLineEdit *lineEdit = new QLineEdit;
        lineEdit = ui->search;
        QObject::connect(lineEdit, &QLineEdit::textChanged, [proxyModel](const QString &text){
            QRegExp regExp(text, Qt::CaseInsensitive, QRegExp::Wildcard);
            proxyModel->setFilterRegExp(regExp);
            proxyModel->setFilterKeyColumn(6);
        });

    }
    else{
        qDebug() << db.lastError().text();
    }
    emit SecondSendData(model);
}

ThirdWindow::~ThirdWindow()
{
    delete ui;
}

void ThirdWindow::on_Delete_clicked()
{
    model->removeRow(currentRow);
    model->select();
}

void ThirdWindow::on_tableView_clicked(const QModelIndex &index)
{
    currentRow = index.row();
    QModelIndex columnIndex = ui->tableView->model()->index(currentRow,0);
    QVariant data = ui->tableView->model()->data(columnIndex);
    IdColumn = data.toInt();
}

void ThirdWindow::on_Open_clicked()
{
        fourWindow->setDataFromTableModel(IdColumn, currentRow);
        fourWindow->show();
        QWidget::close();
}
