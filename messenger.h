#pragma execution_character_set("utf-8")
#ifndef MESSENGER_H
#define MESSENGER_H
#include <QtCore>
#include <QtNetwork>
#include <QObject>
#include <QString>
#include "peer.h"
class QUdpSocket;

class TcpServer;
#define PCK_HEADER "288:0:"

typedef QList<Peer> PeerList;

class Messenger : public QObject
{
    Q_OBJECT
public:
    explicit Messenger(QObject *parent = 0);
    QString Name();
    QString ID();
    PeerList& getPeers();
    void sendPM(QString text, QString to);
protected:
    void haspendingfile(QString clientid,QString fileName);
signals:

    void peersUpdated();
    void receivedPM(QString from, QString text);
    
public slots:
    void setName(QString name);
    void start();
void getFileName(QString name);
private slots:
    void onTimerdiscovery();
    void onReadyRead();

 // void gettarget(QString userid);
private:
QString target;
    Peer _me;
    PeerList _peers;
    QUdpSocket _udp;
    QTimer _timerdiscovery;
    QList<QHostAddress> _myips;
    void log(QString data, QString dest, bool isSent);
    void logSent(QString data, QHostAddress dest);
    void logReceived(QString data, QHostAddress dest);
    void processTheDatagram(QByteArray data, QHostAddress sender);
QString fileName;
TcpServer  *ser;
};

#endif // MESSENGER_H
