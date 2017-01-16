#pragma execution_character_set("utf-8")
#include "pmwindow.h"
#include "ui_pmwindow.h"
#include<tcpserver.h>
#include<QTime>
#include<QColorDialog>

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


void PMWindow::on_fontComboBox_currentFontChanged(const QFont &f)
{
    ui->txtInput->setCurrentFont(f);
    ui->txtInput->setFocus();
}

void PMWindow::on_comboBox_currentIndexChanged(const QString &arg1)
{
    ui->txtInput->setFontPointSize(arg1.toDouble());
    ui->txtInput->setFocus();
}

//加粗

void PMWindow::on_toolButton_4_clicked(bool checked)
{
    if(checked)
    ui->txtInput->setFontWeight(QFont::Bold);
    else
       ui->txtInput->setFontWeight(QFont::Normal);
    ui->txtInput->setFocus();

}
//斜体
void PMWindow::on_toolButton_clicked(bool checked)
{
    ui->txtInput->setFontItalic(checked);
    ui->txtInput->setFocus();

}


void PMWindow::on_toolButton_2_clicked()
{
  QColor color  =QColorDialog::getColor(color,this);

 if(color.isValid())
 {ui->txtInput->setTextColor(color);
     ui->txtInput->setFocus();

 }
}
