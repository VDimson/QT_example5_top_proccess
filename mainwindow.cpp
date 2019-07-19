#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    tmr=new QTimer(this);
   tmr->start(1000);
proc_top=new QProcess(this);
    connect(proc_top,SIGNAL(finished(int)),this,SLOT(Read_Top()));
    connect(tmr,SIGNAL(timeout()),this,SLOT(TimerUp()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::Read_Top()
{
    QString vihlp;
    vihlp=proc_top->readAllStandardOutput();
    ui->textEdit->clear();
    ui->textEdit->setText(vihlp);

    QStringList Stroki=vihlp.split("\n",QString::SkipEmptyParts);

    //for (int i=1;i<Stroki.count();++i)
    //{
    if (Stroki.isEmpty())
    {
        ui->textEdit->setText("Пустое значение!");
        ui->progressBar->setValue(0);
        return;

    }
    if (Stroki.count()>6)
    {
     QString Stroka=Stroki.at(6);
     QStringList ItemStroka=Stroka.split(" ",QString::SkipEmptyParts);
     ui->statusBar->showMessage(ItemStroka.at(8),1000);
     QString prStr;
     prStr=ItemStroka.at(8);
     QStringList prList;
     prList=prStr.split(",",QString::SkipEmptyParts);
     int pr;
     bool ok;
     QString prS;
     prS=prList.at(0);
     pr=prS.toInt(&ok,10);
     ui->progressBar->setValue(pr);


    }

    //}
}

void MainWindow::on_pushButton_clicked()
{
    if (statusButton)
    {

    proc_top->close();
    tmr->stop();
    statusButton=false;
    ui->pushButton->setText("Старт");
    }
    else
    {
       tmr->start(1000);
        statusButton=true;
        ui->pushButton->setText("Стоп");

    }

}
void MainWindow::TimerUp()
{
    QString paramStr="top -b -u "+ui->lineEdit->text()+" -n 1\n";
    //paramStr="top -b -u root -n 1\n";
    //ui->statusBar->showMessage(paramStr);
    //const char* param; //определяем символьную переменную
    //disp=disp_com.toStdString().allocator_type//перевод строки в символную переменную

    //param=paramStr.toLocal8Bit().data();
    //proc_top->start("sh");
    proc_top->start(paramStr);
   // proc_top->waitForStarted();
   // proc_top->write("top -b -u root -n 1");
    //proc_top->write(param);
    //proc_top->waitForBytesWritten();
    //proc_top->closeWriteChannel();
}
