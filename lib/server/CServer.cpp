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
m_worldBox(),
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
    sf::Packet          packet;
    std::string         sUpdate;
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
                packet << port << iNbPlayers;
                client.send(packet);
                packet.clear();
                client.receive(packet);
                packet >> m_vClients.back().port;
                client.disconnect();
                m_worldMap.addPlayer(std::string("Player ") + std::to_string(iNbPlayers), 50, 50);
                iNbPlayers++;
            }
        }

        if (socketSelector.wait())
        {
            for (std::vector<SClient>::iterator it = m_vClients.begin(); it != m_vClients.end(); it++)
            {
                if (socketSelector.isReady(*(it->pSocket)))
                {
                    if (it->pSocket->receive(packet, it->ip, it->port) == sf::Socket::Done)
                    {
                        packet >> sUpdate;
                        packet.clear();
                    }
                }
            }
        }

        if (!sUpdate.empty())
        {
            m_mutex.lock();
            m_worldMap.update(sUpdate);
            sUpdate.clear();
            m_mutex.unlock();
        }

        sf::sleep(sf::milliseconds(50));
    }
}

void  CServer::loopGame()
{
    sf::Clock   clock;
    sf::Packet  packet;
    std::string sUpdate;

    while (m_running)
    {
        sf::Time elapsed = clock.restart();
        sUpdate.clear();
        sUpdate = m_worldBox.update(&m_worldMap, elapsed);

        if (!sUpdate.empty())
        {
            m_worldMap.printUpdate(sUpdate);
            m_worldMap.update(sUpdate);
            packet.clear();
            packet << sUpdate;
            for (std::vector<SClient>::iterator it = m_vClients.begin(); it != m_vClients.end(); it++)
                it->pSocket->send(packet, it->ip, it->port);
        }

        sf::sleep(sf::milliseconds(50));
    }
}


