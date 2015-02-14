//
//  @ Project : PIRATES
//  @ File Name : CServer.h
//  @ Date : 20/10/2014
//  @ Author :
//


#ifndef CSERVER_H
#define CSERVER_H


#include <vector>
#include <iostream>
#include <string>

#include <common/SFML.h>
#include <common/CWorldMap.h>
#include <worldBox/CWorldBox.h>


#define SERVER_PORT 56747


struct SClient
{
    sf::UdpSocket*  pSocket;
    sf::IpAddress   ip;
    unsigned short  port;
};


class CServer
{
    public :
        CServer(int nbMaxPlayers);
        ~CServer();

        void    loopGame();

    private :
        void    loopSocket();

        int m_iNbMaxPlayers;

        sf::Thread      m_threadLoopSocket;
        sf::Mutex       m_mutex;

        CWorldMap       m_worldMap;
        CWorldBox       m_worldBox;

        std::vector<SClient>    m_vClients;

        bool  m_running;
};


#endif


