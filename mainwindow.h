#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QProcess>
#include <QTimer>
#include <QTime>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
public slots:
void Read_Top();
void TimerUp();
private slots:
void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    QProcess *proc_top;
    QTimer *tmr;
    QTime  *time;
const char* param;
QString paramStr;
bool statusButton=true;

};

#endif // MAINWINDOW_H
