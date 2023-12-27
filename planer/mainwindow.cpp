#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "secondwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("SchoolPlaner");
    setWindowIcon(QIcon("C:/Users/elpav/Documents/planer/images/icons8-checklist-32.png"));
    this->setFixedSize(653,447);
    timer = new QTimer(this);
    ms = 0;
    s = 0;
    m = 0;
    connect(timer, SIGNAL(timeout()),this,SLOT(TimerSlot()));
    timer->start(1);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    window = new SecondWindow(this);
    window->show();

}

void MainWindow::on_pushButton_2_clicked()
{
    window_1 = new ThirdWindow(this);
    window_1->show();
}


void MainWindow::on_pushButton_3_clicked()
{
    QApplication::quit();
}

void MainWindow::saveSettings()
{
    settings->setValue("geometry",geometry());
}

void MainWindow::loadSettings()
{
    setGeometry(settings->value("geometry", QRect(200,200,300,300)).toRect());
}


void MainWindow::TimerSlot()
{
    ms++;
    if(ms>=1000){
        ms =0;
        s++;
    }
    if(s>=60){
        s =0;
        m++;
    }
    ui->label_2->setText(QString::number(m)+" : ");
    ui->label_3->setText(QString::number(s));
}
