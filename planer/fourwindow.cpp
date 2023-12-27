#include "fourwindow.h"
#include "ui_fourwindow.h"
#include "thirdwindow.h"

FourWindow::FourWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FourWindow)
{
    ui->setupUi(this);
    setWindowTitle("School Planer.Редактирование задачи/события");
    setWindowIcon(QIcon("C:/Users/elpav/Documents/planer/images/icons8-checklist-32.png"));
    this->setFixedSize(723,555);
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("C:/Users/elpav/Documents/databaseSchoolPlaner.db");
    if(db.open()){
        qDebug() << "DataBase successfully connected";
        model = new QSqlTableModel(this, db);
        model->setTable("Activity");
        model->select();
    }
    else{
        qDebug() << db.lastError().text();
    }

}

FourWindow::~FourWindow()
{
    delete ui;
}


void FourWindow::on_actionNew_triggered()
{
    currentFile.clear();
    ui->textEdit->setText(QString());
}

void FourWindow::on_actionOpen_triggered()
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
           }

           file.close();
    }
}

void FourWindow::on_actionSave_as_triggered()
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


       QString date = dateEdit->date().toString();
       QString time = timeEdit->time().toString();
       QString text = textEdit->toPlainText();
       QString comboBoxText = comboBox->currentText();

       stream << "Date: " << date << endl;
       stream << "Time: " << time << endl;
       stream << "Text: " << text << endl;
       stream << "ComboBox: " << comboBoxText << endl;


       file.close();
}

void FourWindow::on_actionExit_triggered()
{
    window4 = new FourWindow(this);
    window4->close();
}

void FourWindow::on_actionCopy_triggered()
{
    ui->textEdit->copy();
}

void FourWindow::on_actionPaste_triggered()
{
    ui->textEdit->paste();
}

void FourWindow::on_actionCut_triggered()
{
    ui->textEdit->cut();
}

void FourWindow::on_actionUndo_triggered()
{
    ui->textEdit->undo();
}

void FourWindow::on_actionRedo_triggered()
{
    ui->textEdit->redo();
}

void FourWindow::GetDataTable(QSqlTableModel *newModel, int newCurrentRow){
    currentRow = newCurrentRow;
    model = newModel;
}

void FourWindow::on_AddToData_clicked()

{

    int indexValue;
    if(model->rowCount() == 0){
        indexValue = 0;
    }
    else{
        indexValue = model->rowCount();
    }
    model->removeRow(currentRow);
    model->select();
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

void FourWindow::on_Exit_clicked()
{
    QWidget::close();
    ThirdWindow *window_1;
    window_1 = new ThirdWindow(this);
    window_1->show();

}

void FourWindow::on_Add_Image_clicked()
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

void FourWindow::setDataFromTableModel(int IdColumn, int currentRow)
{
    QDate date1;
    QTime time;
    QString text;
    QString combo;
    QString header;
    QPixmap image;
    if(currentRow >= 0){
        QSqlQuery query;
        query.prepare("SELECT * FROM Activity WHERE IndRow=:indRow");
        query.bindValue(":indRow", IdColumn);

        if(query.exec() && query.next()){
                    QString date_string = query.value("Date").toString();
                    date1 = QDate::fromString(date_string, "ddd MMM dd yyyy");
                    QVariant timeVariant = query.value("Time");
                    time = timeVariant.toTime();
                    text = query.value("Text").toString();
                    combo = query.value("Kind").toString();
                    QVariant imageVariant = query.value("Image");
                    header = query.value("Header").toString();
                    QByteArray imageData = imageVariant.toByteArray();
                    image.loadFromData(imageData);
        }
    ui->AddImage->setPixmap(image);
    ui->dateEdit->setDisplayFormat("ddd MMM dd yyyy");
    ui->dateEdit->setDate(date1);
    ui->timeEdit->setTime(time);
    ui->textEdit->setText(text);
    ui->comboBox->setCurrentText(combo);
    ui->AddImage->setPixmap(image);
    ui->lineEdit->setText(header);
    }
}
