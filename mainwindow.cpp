#pragma execution_character_set("utf-8")
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QtNetwork>
#include<QDesktopWidget>
#include<QTcpServer>
#include<QDesktopServices>
#include<QProcess>
QString userid;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),

    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //系统托盘
    init();

    msgr = new Messenger(this);//消息管理器 转到messager
    connect(msgr, SIGNAL(peersUpdated()), this , SLOT(onUpdateList()));//好友更新
    connect(msgr, SIGNAL(receivedPM(QString,QString)), this, SLOT(onReceivedPM(QString,QString)));//好友聊天接收消息
   // connect(this, SIGNAL(sendtarget(QString)), msgr, SLOT(gettarget(QString)));
    msgr->setName(QHostInfo::localHostName());//给me赋予名字
    ui->lblWelcome->setText( msgr->Name());//显示
    connect(msgr,SIGNAL(rejected()),this,SLOT(ref()));
    msgr->start();//开始广播
}
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::init()
{
    //托盘窗口
   tray=new QSystemTrayIcon(this);
   tray->setIcon(QIcon(":/main.png"));
   tray->show();
   connect(tray,SIGNAL(actived(QSystemTrayIcon::ActivationReason)),this,SLOT(TrayIconAction(QSystemTrayIcon::ActivationReason)));
          //初始化窗口功能
           menu=new QMenu(this);
           reset=new QAction(this);
           reset->setText("cortfly");
           reset->setIcon(QIcon(":/main.png"));
           connect(reset,SIGNAL(triggered()),this,SLOT(showNormal()));

           quit=new QAction(this);
           quit->setText("退出");
           connect(quit,SIGNAL(triggered()),qApp,SLOT(quit()));
           lab=new QAction(this);
           lab->setText("实验室论坛");
            lab->setIcon(QIcon(":/lab.png"));
           connect(lab,SIGNAL(triggered()),this,SLOT(on_pushButton_clicked()));
          servercon=new QAction(this);
          servercon->setText("连接服务器");
           servercon->setIcon(QIcon(":/ser.png"));
          connect(servercon,SIGNAL(triggered()),this,SLOT(on_pushButton_3_clicked()));

     tray->setContextMenu(menu);
     menu->addAction(reset);

     menu->addAction(lab);
   menu->addAction(servercon);
      menu->addAction(quit);



}

void MainWindow::onUpdateList()
{
    ui->listUsers->clear();
    QList<Peer>& peers = msgr->getPeers();
    for(int i=0; i<peers.count(); i++)
    { QListWidgetItem *item =new QListWidgetItem(QIcon(":/send.png"), peers[i].ID());
        item->setSizeHint(QSize(50,50));
        item->setBackgroundColor(QColor(255, 255, 255));
        ui->listUsers->addItem(item);
    }
}



void MainWindow::on_listUsers_doubleClicked(const QModelIndex &index)
{
     userid = ui->listUsers->currentItem()->text();
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
        newpm->setWindowIcon(QIcon(":/send.png"));
        newpm->show();
        return newpm;
    }
}

void MainWindow::TrayIconAction(QSystemTrayIcon::ActivationReason reason)
{
    if(reason==QSystemTrayIcon::Trigger)
        this->showNormal();
}

void MainWindow::getFileName(QString name)
{
   msgr->sendfile(name,userid);
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




void MainWindow::on_pushButton_clicked()
{ QDesktopServices::openUrl( QUrl("http://10.108.14.139/bit834/"));

}

void MainWindow::ref()
{ qDebug()<<"111";
emit reject();


}

void MainWindow::on_pushButton_3_clicked()
{
    QProcess process(this);
    process.startDetached("mstsc.exe");


}

void MainWindow::on_pushButton_2_clicked()
{

}
