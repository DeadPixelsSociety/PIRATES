#ifndef CSERVER_H
#define CSERVER_H


#include <map>
#include <iostream>
#include <string>

#include <common/SFML.h>
#include <common/CWorldMap.h>
#include <server/CWorldBox.h>


#define PERIOD          20
#define PING_TIMEOUT    5


struct SClient
{
    sf::UdpSocket   socket;
    sf::IpAddress   ip;
    sf::Clock       ping;
};


class CServer
{
    public :
        CServer(int nbMaxPlayers);
        ~CServer();

        void    loopGame();

    private :
        void    loopSocket();
        void    sendClients(CMapQuery& in);
        void    deleteClient(int id);

        int m_nbMaxPlayers;

        sf::Thread      m_threadLoopSocket;

        CWorldMap       m_worldMap;
        CWorldBox       m_worldBox;

        std::map<int, SClient*>    m_mClients;

        bool  m_running;
};


#endif


