
#pragma execution_character_set("utf-8")
#include "peer.h"

Peer::Peer()
{
}

QString Peer::ID()
{
    return Name + "@" + Domain;
}
