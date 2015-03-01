#include <server/CServer.h>


unsigned short  tcpPort = 56747;
unsigned short  udpPort = 56748;
unsigned short  udpPortClient = 56749;


CServer::CServer(int nbMaxPlayers) :
m_nbMaxPlayers(nbMaxPlayers),
m_threadLoopSocket(&CServer::loopSocket, this),
m_worldBox("../asset/maps/collision.tmx"),
m_running(true)
{
  m_threadLoopSocket.launch();
}

CServer::~CServer()
{
    m_running = false;
    for (auto client : m_mClients)
    {
        client.second->socket.unbind();
        delete client.second;
    }
    m_threadLoopSocket.wait();
}

void  CServer::loopSocket()
{
    sf::TcpListener     listener;
    sf::TcpSocket       tcpClient;
    sf::SocketSelector  socketSelector;
    sf::Clock           phase;
    CMapQuery           mapQuery;
    int                 nbPlayers = 0;

    listener.listen(tcpPort);
    listener.setBlocking(false);
    while (m_running)
    {
        if (nbPlayers < m_nbMaxPlayers)
        {
            if (listener.accept(tcpClient) == sf::Socket::Done)
            {
                m_mClients[nbPlayers] = new SClient();
                m_mClients[nbPlayers]->ip = tcpClient.getRemoteAddress();
                m_mClients[nbPlayers]->socket.bind(udpPort);
                socketSelector.add(m_mClients[nbPlayers]->socket);

                mapQuery.clear();
                mapQuery << nbPlayers;
                tcpClient.send(mapQuery);

                mapQuery.clear();
                for (int i = 0; i < nbPlayers; i++)
                    mapQuery << NWorldMap::Add << NWorldMap::Player << i << "Player " + std::to_string(i);
                tcpClient.send(mapQuery);
                tcpClient.disconnect();

                mapQuery.clear();
                mapQuery << NWorldMap::Add << NWorldMap::Player << nbPlayers << "Player " + std::to_string(nbPlayers);
                sendClients(mapQuery);
                m_worldMap.update(mapQuery);

                nbPlayers++;
            }
        }
        if (socketSelector.wait())
        {
            for (auto client : m_mClients)
            {
                if (socketSelector.isReady(client.second->socket))
                {
                    mapQuery.clear();
                    if (client.second->socket.receive(mapQuery, client.second->ip, udpPortClient) == sf::Socket::Done)
                    {
                        m_worldMap.update(mapQuery);
                        client.second->ping.restart();
                    }
                }
            }
        }
        for (auto client : m_mClients)
        {
            if (client.second->ping.getElapsedTime() > sf::seconds(PING_TIMEOUT))
                deleteClient(client.first);
        }
        sf::sleep(sf::milliseconds(PERIOD) - phase.restart());
    }
}

void    CServer::loopGame()
{
    sf::Clock   phase;
    CMapQuery   mapQuery;

    while (m_running)
    {
        mapQuery.clear();
        mapQuery = m_worldBox.update(m_worldMap.getMObjects());
        sendClients(mapQuery);
        sf::sleep(sf::milliseconds(PERIOD) - phase.restart());
    }
}

void    CServer::sendClients(CMapQuery& mapQuery)
{
    for (auto client : m_mClients)
        client.second->socket.send(mapQuery, client.second->ip, udpPortClient);
}

void    CServer::deleteClient(int id)
{
    CMapQuery   mapQuery;

    m_mClients[id]->socket.unbind();
    delete m_mClients[id];
    m_mClients.erase(id);
    mapQuery << NWorldMap::Delete << NWorldMap::Player << id;
    sendClients(mapQuery);
}

