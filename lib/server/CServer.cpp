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
    std::cout << "Launch loop socket\n";
    sf::TcpListener     listener;
    sf::TcpSocket       client;
    sf::SocketSelector  socketSelector;
    unsigned short      port = SERVER_PORT;
    sf::Packet          packet;
    std::string         sPacketData;
    int                 iNbPlayers = 0;

    //listener.setBlocking(false);
    //client.setBlocking(false);
    if (listener.listen(SERVER_PORT) != sf::Socket::Done)
        std::cerr << "Error during listening at " << SERVER_PORT;

    while (m_running)
    {
        sPacketData.clear();

        if (iNbPlayers < m_iNbMaxPlayers)
        {
            if (listener.accept(client) == sf::Socket::Done)
            {
                std::cout << "Accepting new client\n";
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
                std::cout << "Port client : " << m_vClients.back().port << "\n";
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
                        std::cout << "Receive client packet\n";
                        packet >> sPacketData;
                        packet.clear();
                    }
                }
            }
        }

        if (!sPacketData.empty())
        {
            std::cout << "Update WorldMap : " << sPacketData << "\n";
            m_mutex.lock();
            m_worldMap.update(sPacketData);
            m_mutex.unlock();
            m_sUpdate += sPacketData;
        }

        sf::sleep(sf::milliseconds(50));
    }
}

void  CServer::loopGame()
{
    sf::Clock   clock;
    sf::Packet  packet;

    while (m_running)
    {
        sf::Time elapsed = clock.restart();
        m_worldBox.update(elapsed);

        if (!m_sUpdate.empty())
        {
            std::cout << "Send clien data\n";
            packet.clear();
            packet << m_sUpdate;
            for (std::vector<SClient>::iterator it = m_vClients.begin(); it != m_vClients.end(); it++)
                it->pSocket->send(packet, it->ip, it->port);
            m_sUpdate.clear();
        }

        sf::sleep(sf::milliseconds(50));
    }
}


