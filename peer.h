#pragma execution_character_set("utf-8")
#ifndef PEER_H
#define PEER_H

#include <QtCore>
#include <QtNetwork>

class Peer
{
public:
    explicit Peer();
    QString Name;
    QString Domain;
    QHostAddress Host;
    QTime Lastseen;
    QString ID();
    QString target;
    
};

#endif // PEER_H
