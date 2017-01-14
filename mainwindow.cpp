#pragma execution_character_set("utf-8")
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QtNetwork>
#include<QDesktopWidget>
#include<QTcpServer>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    msgr = new Messenger(this);//消息管理器 转到messager
 qDebug()<<"3333";

    connect(msgr, SIGNAL(peersUpdated()), this , SLOT(onUpdateList()));//好友更新
    connect(msgr, SIGNAL(receivedPM(QString,QString)), this, SLOT(onReceivedPM(QString,QString)));//好友聊天接收消息

    msgr->setName(QHostInfo::localHostName());//给me赋予名字
    ui->lblWelcome->setText( msgr->Name());//显示
    msgr->start();//开始广播
}
MainWindow::~MainWindow()
{
   delete ui;
}

void MainWindow::onUpdateList()
{
    ui->listUsers->clear();
    QList<Peer>& peers = msgr->getPeers();
    for(int i=0; i<peers.count(); i++)
        ui->listUsers->addItem(new QListWidgetItem(QIcon(":/image/20071126092635267.png"), peers[i].ID()));
}



void MainWindow::on_listUsers_doubleClicked(const QModelIndex &index)
{
    QString userid = ui->listUsers->currentItem()->text();

    makePMWindow(userid);

}

PMWindow* MainWindow::makePMWindow(QString title)
{
    if(pms.keys().contains(title))
    {
        pms[title]->setFocus();
        return pms[title];
    }
    else
    {
        PMWindow* newpm = new PMWindow();
        pms.insert(title, newpm);
        pmr.insert(newpm, title);
        connect(newpm, SIGNAL(enteredText(QString)), this, SLOT(onPMSend(QString)));
        connect(newpm, SIGNAL(closedWindow()), this, SLOT(onPMClosed()));
        newpm->setWindowTitle(title);
        newpm->show();
        return newpm;
    }
}



void MainWindow::onPMSend(QString text)
{
    PMWindow* to = qobject_cast<PMWindow*>(sender());
    msgr->sendPM(text, pmr[to]);
}


void MainWindow::onPMClosed()
{
    PMWindow* window = qobject_cast<PMWindow*>(sender());
    //msgr->sendPM("Closed chat window.", pmr[window]);
    pms.remove(pmr[window]);
    pmr.remove(window);
}

void MainWindow::onReceivedPM(QString from, QString text)
{
    makePMWindow(from)->receivedPM(text);
}



void MainWindow::on_nichnameButton_clicked()
{    DialogNickName *dlgName = new DialogNickName(this);
     connect(dlgName, SIGNAL(setName(QString)), this, SLOT(onSetName(QString)));
      connect(dlgName,SIGNAL(setImage(QString)),this,SLOT(onsetimage(QString)));
    dlgName->setModal(true);
    dlgName->setWindowTitle("资料卡:");
        dlgName->move ((QApplication::desktop()->width()-800),(QApplication::desktop()->height() - dlgName->height())/2);
    dlgName->show();
}
void MainWindow::onSetName(QString name)
{
    msgr->setName(name);
    ui->lblWelcome->setText( msgr->Name());

}


void MainWindow::onsetimage(QString filename)
{
    ui->nichnameButton->setIcon(QIcon(filename));


}

void MainWindow::getfileName(QString)
{

}

