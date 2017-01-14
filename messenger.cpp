/*
 * 消息管理器，主要负责各种消息得处理（核心）
 * update 增加私聊好友之间得通讯功能 2017/1/13
 */
#pragma execution_character_set("utf-8")
#include "messenger.h"
#include"tcpclient.h"
#include"tcpserver.h"
#include<QFileDialog>
#include<QMessageBox>
#include"mainwindow.h"
Messenger::Messenger(QObject *parent) :
    QObject(parent)
{
    connect(&_timerdiscovery, SIGNAL(timeout()), this, SLOT(onTimerdiscovery()));
     connect(&_udp, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
 ser=new TcpServer();
  connect(ser,SIGNAL(sendFileName(QString)),this,SLOT(getFileName(QString)));

  getFileName(QString name);
    _myips = QNetworkInterface::allAddresses();
}
void Messenger::start()
{
   _udp.bind(2880, QUdpSocket::ReuseAddressHint);
   _timerdiscovery.start(500);//5秒之后发射timeout()信号 进入ontimerdiscovery
}

void Messenger::setName(QString name)
{
    _me.Name = name;
    _me.Domain = QHostInfo::localHostName();
}
//messagename 等于mypeer得id name@domin
QString Messenger::Name()
{
    return _me.ID();
}

void Messenger::onTimerdiscovery()
{   //udp数据包在探测阶段 包括四段288+0+discovery标志+自己得id
    QString packet = PCK_HEADER "DISCOVERY:" + _me.ID();
//   logSent(packet, QHostAddress::Broadcast);//debug日志
    _udp.writeDatagram(packet.toUtf8(),QHostAddress::Broadcast, 2880);//发送广播使用2880端口告诉别人我已经登陆
    // 检查好友列表
    for(int i=0; i<_peers.count(); i++)
        if(_peers[i].Lastseen.secsTo(QTime::currentTime()) > 10)
        {
            _peers.removeAt(i);
            emit peersUpdated();
        }
}
void Messenger::onReadyRead()
{
    while (_udp.hasPendingDatagrams())
    {
        QByteArray datagram;
        datagram.resize(_udp.pendingDatagramSize());
        QHostAddress sender;
        quint16 senderPort;

        _udp.readDatagram(datagram.data(), datagram.size(), &sender, &senderPort);

        bool flag = true;
        for(int i=0; i < _myips.count(); ++i)
            if(sender.toString() == _myips[i].toString())
                flag = false;
        if (flag)
        {
         //   logReceived(datagram, sender);
            processTheDatagram(datagram, sender);
        }
    }
}
//发送文件名




void Messenger::log(QString data, QString dest, bool isSent)
{
    QString msg;
    msg += isSent? "Sent     ":"Received ";
    msg += QString::number(data.length()) + " bytes";
    msg += isSent? " to   ":" from ";
    QString fill;
    fill.fill(' ', 15 - dest.size());
    msg += dest + fill + "  Data: ";
    msg += data;
    qDebug() << msg.toStdString().c_str();
    return;
}

void Messenger::logSent(QString data, QHostAddress dest)
{
    return log(data, dest.toString(), true);
}

void Messenger::logReceived(QString data, QHostAddress dest)
{
    return log(data, dest.toString(), false);
}

PeerList& Messenger::getPeers()
{
    return _peers;
}


void Messenger::processTheDatagram(QByteArray data, QHostAddress sender)
{
    QString str_packet = QString(data);
    QStringList packet = str_packet.split(':');
    if(packet.count()<4)
    {
        qWarning("Warning: Unknown Packet. ");
        return;
    }
    if(packet[0] != "288")
    {
        qWarning("Warning: Protocol Mismatch. ");
        return;
    }
    if(packet[1] != "0")
    {
        qWarning("Warning: Protocol Version Mismatch. ");
        return;
    }
    if(packet[2] == "DISCOVERY")
    {
        int found = -1;
        //好友去重检查，这里使用name+@+hostname 作为标识
        for(int i=0; i<_peers.count(); i++)
            if(_peers[i].ID() == packet[3]) found = i;
        if(found == -1)
        {
            //增加新好友
            Peer newpeer;
            QString peerid = packet[3];
            QStringList peerids = peerid.split('@');
            if(peerids.count() != 2)
            {
                qWarning("Warning: Wronge new Peer ID.");
                return;
            }
            newpeer.Name = peerids[0];
            newpeer.Domain = peerids[1];
            newpeer.Host = sender;
            newpeer.Lastseen = QTime::currentTime();
            _peers.append(newpeer);
            emit peersUpdated();
        }
        else
        {//更新好友得最后登陆时间
            _peers[found].Lastseen = QTime::currentTime();
        }
    }

    if(packet[2] == "PM")
    {
        QString from = packet[3];
        QString text = packet[4];
        for(int i=5; i<packet.count(); i++)
            text += ":" + packet[i];
        emit receivedPM(from, text);
    }
    if(packet[2]=="filename")
    {
        QString from = packet[3];
        QString filename = packet[4];
        haspendingfile(from,filename);

    }

}

void Messenger::sendPM(QString text, QString to)
{
    target=to;
    QHostAddress adr;
    for(int i=0; i<_peers.count(); i++)
    {
        if(_peers[i].ID() == to)
            adr = _peers[i].Host;
    }
    QString packet = PCK_HEADER "PM:" + _me.ID() + ":" + text;
  //  logSent(packet, adr);
    _udp.writeDatagram(packet.toUtf8(), adr, 2880);
}

void Messenger::haspendingfile(QString clientid, QString fileName)
{
 //   int btn=QMessageBox::information( ,"接收文件","来自的文件，是否接收？" ,QMessageBox::Yes,QMessageBox::No);


        QString name=QFileDialog::getSaveFileName(0,"保存文件",fileName);
      TcpClient   *client=new TcpClient();
        client->show();


}
void Messenger::getFileName(QString name)
{
    qDebug()<<"11111"<<name;
}




