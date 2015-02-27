//
//  @ Project :   PIRATES
//  @ File Name : CServer.cpp
//  @ Date :      20/10/2014
//  @ Author :    Romain
//


#include <server/CServer.h>


CServer::CServer(int nbMaxPlayers) :
m_iNbMaxPlayers(nbMaxPlayers),
m_threadLoopSocket(&CServer::loopSocket, this),
m_mutex(),
m_worldMap(),
m_worldBox("../asset/maps/collision.tmx"),
m_vClients(),
m_running(true)
{
  m_threadLoopSocket.launch();
}

CServer::~CServer()
{
    m_running = false;
    m_threadLoopSocket.wait();
    for (std::vector<SClient>::iterator it = m_vClients.begin(); it != m_vClients.end(); it++)
        delete it->pSocket;
}

void  CServer::loopSocket()
{
    sf::TcpListener     listener;
    sf::TcpSocket       client;
    sf::SocketSelector  socketSelector;
    unsigned short      port = SERVER_PORT;
    CMapQuery           mapQuery;
    int                 iNbPlayers = 0;

    if (listener.listen(SERVER_PORT) != sf::Socket::Done)
        std::cerr << "Error during listening at " << SERVER_PORT;

    while (m_running)
    {
        if (iNbPlayers < m_iNbMaxPlayers)
        {
            if (listener.accept(client) == sf::Socket::Done)
            {
                listener.setBlocking(false);
                port++;
                m_vClients.push_back(SClient());
                m_vClients.back().ip = client.getRemoteAddress();
                m_vClients.back().pSocket = new sf::UdpSocket();
                m_vClients.back().pSocket->bind(port);
                socketSelector.add(*(m_vClients.back().pSocket));

                mapQuery.clear();
                mapQuery << port << iNbPlayers;
                client.send(mapQuery);

                mapQuery.clear();
                client.receive(mapQuery);
                mapQuery >> m_vClients.back().port;

                mapQuery.clear();
                for (int i = 0; i < iNbPlayers; i++)
                    mapQuery << NWorldMap::Add << NWorldMap::Player << i << sf::Vector2f(0, 0) << "Player " + std::to_string(i);
                client.send(mapQuery);
                client.disconnect();

                mapQuery.clear();
                mapQuery << NWorldMap::Add << NWorldMap::Player << iNbPlayers << sf::Vector2f(0, 0) << "Player " + std::to_string(iNbPlayers);
                for (std::vector<SClient>::iterator it = m_vClients.begin(); it != m_vClients.end(); it++)
                    it->pSocket->send(mapQuery, it->ip, it->port);
                m_worldMap.update(mapQuery);

                iNbPlayers++;
            }
        }

        if (socketSelector.wait())
        {
            for (std::vector<SClient>::iterator it = m_vClients.begin(); it != m_vClients.end(); it++)
            {
                if (socketSelector.isReady(*(it->pSocket)))
                {
                    mapQuery.clear();
                    if (it->pSocket->receive(mapQuery, it->ip, it->port) == sf::Socket::Done)
                    {
                        m_mutex.lock();
                        m_worldMap.update(mapQuery);
                        m_mutex.unlock();
                    }
                }
            }
        }

        sf::sleep(sf::milliseconds(20));
    }
}

void  CServer::loopGame()
{
    sf::Clock   clock;
    CMapQuery   mapQuery;

    while (m_running)
    {
        sf::Time elapsed = clock.restart();
        mapQuery.clear();
        m_mutex.lock();
        mapQuery = m_worldBox.update(m_worldMap.getVObjects(), elapsed);
        m_mutex.unlock();

        for (std::vector<SClient>::iterator it = m_vClients.begin(); it != m_vClients.end(); it++)
            it->pSocket->send(mapQuery, it->ip, it->port);

        sf::sleep(sf::milliseconds(20));
    }
}


