#pragma execution_character_set("utf-8")
#include "pmwindow.h"
#include "ui_pmwindow.h"
#include<tcpserver.h>
#include<QTime>

PMWindow::PMWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PMWindow)
{
    ui->setupUi(this);
    ui->txtInput->setFocus();
  //  ser=new TcpServer();
   //MainWindow *w=new MainWindow();

}

PMWindow::~PMWindow()
{
    delete ui;
}

void PMWindow::on_btnSend_clicked()
{
    emit enteredText(ui->txtInput->toPlainText());
     ui->txtChat->setTextColor(Qt::blue);
    ui->txtChat->append("我 "+QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
    ui->txtChat->setTextColor(Qt::black);
    ui->txtChat->append(+"  "+ui->txtInput->toPlainText());
    ui->txtInput->clear();
    ui->txtInput->setFocus();
}

void PMWindow::receivedPM(QString text)
{
    ui->txtChat->setTextColor(Qt::green);
    ui->txtChat->append(this->windowTitle()+" "+QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
     ui->txtChat->setTextColor(Qt::black);
    ui->txtChat->append(+"  "+text);
}
void PMWindow::on_txtInput_returnPressed()
{
    on_btnSend_clicked();
}
void PMWindow::closeEvent(QCloseEvent *event)
{
    emit closedWindow();
    event->accept();
    this->deleteLater();
}

void PMWindow::on_toolButton_3_clicked()
{
   TcpServer *sendwin=new TcpServer(this);
   sendwin->show();

}
