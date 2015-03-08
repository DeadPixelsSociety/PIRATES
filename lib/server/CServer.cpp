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
    CQuery              query;
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

                query.clear();
                query << nbPlayers;
                tcpClient.send(query);

                query.clear();
                for (int i = 0; i < nbPlayers; i++)
                    query << NWorldMap::Add << NWorldMap::Player << i << "Player " + std::to_string(i);
                tcpClient.send(query);
                tcpClient.disconnect();

                query.clear();
                query << NWorldMap::Add << NWorldMap::Player << nbPlayers << "Player " + std::to_string(nbPlayers);
                sendClients(query);
                m_worldMap.update(query);

                nbPlayers++;
            }
        }
        if (socketSelector.wait())
        {
            for (auto client : m_mClients)
            {
                if (socketSelector.isReady(client.second->socket))
                {
                    query.clear();
                    if (client.second->socket.receive(query, client.second->ip, udpPortClient) == sf::Socket::Done)
                    {
                        m_worldMap.update(query);
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
    CQuery      query;

    while (m_running)
    {
        query.clear();
        query = m_worldBox.update(m_worldMap.getMObjects());
        sendClients(query);
        sf::sleep(sf::milliseconds(PERIOD) - phase.restart());
    }
}

void    CServer::sendClients(CQuery& query)
{
    for (auto client : m_mClients)
        client.second->socket.send(query, client.second->ip, udpPortClient);
}

void    CServer::deleteClient(int id)
{
    CQuery   query;

    m_mClients[id]->socket.unbind();
    delete m_mClients[id];
    m_mClients.erase(id);
    query << NWorldMap::Delete << NWorldMap::Player << id;
    sendClients(query);
}

