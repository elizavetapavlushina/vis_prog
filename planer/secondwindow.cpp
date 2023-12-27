#include "secondwindow.h"
#include "ui_secondwindow.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QImage>
#include <QBuffer>
#include <thirdwindow.h>

SecondWindow::SecondWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SecondWindow)
{
    ui->setupUi(this);
    QDate currentDate = QDate::currentDate();
    ui->dateEdit->setDate(currentDate);
    QTime currentTime = QTime::currentTime();
    ui->timeEdit->setTime(currentTime);
    this->setFixedSize(738,555);
    setWindowTitle("School Planer.Добавление задачи/события");
    setWindowIcon(QIcon("C:/Users/elpav/Documents/planer/images/icons8-checklist-32.png"));
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("C:/Users/elpav/Documents/databaseSchoolPlaner.db");

    if(db.open()){
        qDebug() << "DataBase successfully connected";
        modelAdd = new QSqlTableModel(this, db);
        modelAdd->setTable("Activity");
        modelAdd->select();

    }
    else{
        qDebug() << db.lastError().text();
    }
}

SecondWindow::~SecondWindow()
{
    delete ui;
}


void SecondWindow::on_actionNew_triggered()
{
    currentFile.clear();
    ui->textEdit->setText(QString());
}

void SecondWindow::on_actionOpen_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this,"Open the File");
    QFile file(fileName);
    currentFile = fileName;

    if (!file.open(QIODevice::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this,"Warning","Cannot Open file " + file.errorString());
        return;
    }
    else {
        QTextStream stream(&file);

           QString line;
           while (!stream.atEnd()) {
               line = stream.readLine();

               if (line.startsWith("Date: ")) {
                   QString dateStr = line.mid(6);
                   QDate date = QDate::fromString(dateStr);

                   QDateEdit* dateEdit = ui->dateEdit;
                   dateEdit->setDate(date);
               }
               else if (line.startsWith("Time: ")) {
                   QString timeStr = line.mid(6);
                   QTime time = QTime::fromString(timeStr);

                   QTimeEdit* timeEdit = ui->timeEdit;
                   timeEdit->setTime(time);
               }
               else if (line.startsWith("Text: ")) {
                   QString text = line.mid(6);

                   QTextEdit* textEdit = ui->textEdit;
                   textEdit->setPlainText(text);
               }
               else if(line.startsWith("Header: ")){
                   QString head = line.mid(6);
                   QLineEdit* header = ui->lineEdit;
                   header->setText(head);
               }
               else if(line.startsWith("ComboBox")){
                   QString kind = line.mid(6);
                   QComboBox* box = ui->comboBox;
                   box->setCurrentText(kind);
               }
           }

           file.close();
    }
}

void SecondWindow::on_actionSave_as_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this,"Save as");
    QFile file(fileName);
    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this,"Warning","Cannot Save file " + file.errorString());
        return;
    }

    currentFile = fileName;
    setWindowTitle(fileName);
    QTextStream stream(&file);

       QDateEdit* dateEdit = ui->dateEdit;
       QTimeEdit* timeEdit = ui->timeEdit;
       QTextEdit* textEdit = ui->textEdit;
       QComboBox* comboBox = ui->comboBox;
       QLineEdit* lineEdit = ui->lineEdit;

       QString date = dateEdit->date().toString();
       QString time = timeEdit->time().toString();
       QString text = textEdit->toPlainText();
       QString comboBoxText = comboBox->currentText();
       QString line = lineEdit->text();

       stream << "Date: " << date << endl;
       stream << "Time: " << time << endl;
       stream << "Text: " << text << endl;
       stream << "ComboBox: " << comboBoxText << endl;
       stream << "Header: " << line << endl;


       file.close();
}

void SecondWindow::on_actionExit_triggered()
{
    window = new SecondWindow(this);
    window->close();
}

void SecondWindow::on_actionCopy_triggered()
{
    ui->textEdit->copy();
}

void SecondWindow::on_actionPaste_triggered()
{
    ui->textEdit->paste();
}

void SecondWindow::on_actionCut_triggered()
{
    ui->textEdit->cut();
}

void SecondWindow::on_actionUndo_triggered()
{
    ui->textEdit->undo();
}

void SecondWindow::on_actionRedo_triggered()
{
    ui->textEdit->redo();
}


void SecondWindow::SecondGetDataTable(QSqlTableModel *newModel){
    modelAdd = newModel;
}

void SecondWindow::on_AddToData_clicked()
{

    int indexValue;
    if(modelAdd->rowCount() == 0){
        indexValue = 0;
    }
    else{
        indexValue = modelAdd->rowCount();
    }
    QString dateValue = ui->dateEdit->date().toString();
    QString timeValue = ui->timeEdit->time().toString();
    QString textValue = ui->textEdit->toPlainText();
    QString comboBoxValue = ui->comboBox->currentText();
    QString lineValue = ui->lineEdit->text();

    QLabel* label = ui->AddImage;

    QByteArray byteArray;
    const QPixmap* pixmapPointer = label->pixmap();
    if(pixmapPointer != nullptr)
    {
        QPixmap pixmap = *pixmapPointer;


        QBuffer buffer(&byteArray);
        buffer.open(QIODevice::WriteOnly);
        pixmap.save(&buffer, "PNG");
    }

    if (ui->dateEdit->date() < QDate::currentDate())
    {
        QMessageBox::critical(nullptr, "Ошибка", "Выбранная дата меньше текущей даты.");
    }
    else
    {

        QSqlQuery query;
        query.prepare("INSERT INTO Activity(IndRow, Date, Time, Text, Kind, Image, Header) VALUES (:indexRow, :date, :time, :text, :combobox, :imageData, :header)");
        query.bindValue(":indexRow", indexValue);
        query.bindValue(":date", dateValue);
        query.bindValue(":time", timeValue);
        query.bindValue(":text", textValue);
        query.bindValue(":combobox", comboBoxValue);
        query.bindValue(":imageData", byteArray);
        query.bindValue(":header", lineValue);

        if (query.exec()) {
        qDebug() << "Data successfully inserted into the database.";
        } else {
            qDebug() << "Error executing SQL query:" << query.lastError().text();
        }
    }
}


void SecondWindow::on_Add_Image_clicked()
{
    QString filepath = QFileDialog::getOpenFileName(nullptr, "Выберите изображение", QDir::currentPath(), "*.png *.jpg *.jpeg *.bmp");
    QImage image(filepath);
    QPixmap pix(filepath);
    int w = ui->AddImage->width();
    int h = ui->AddImage->height();
    if(!image.isNull())
    {
        ui->AddImage->setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));

    }
    else
    {
        QMessageBox::critical(this, "Error", "Не удалось загрузить изображение");
    }
}


void SecondWindow::on_Exit_clicked()
{
    QWidget::close();
}



