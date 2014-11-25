#include "CServer.h"


CServer::CServer(int iNbMaxPlayer) :
m_clock(),
m_threadLoopSocket(&CServer::LoopSocket),
m_threadLoopGame(&CServer::LoopGame),
m_worldMap(),
m_worldBox(),
m_lSocket(),
m_socketSelector(),
m_running(true)
{
  // Ouverture et mise en écoute des nbMaxPlayer Sockets permettant au serveur
  // de recevoir les données des clients
  for (int i = 0; i < nbMaxPlayer; i++)
  {
    m_lSocket.push_back(new sf::UdpSocket());
    m_lSocket.back()->bind(54000);
    m_socketSelector.add(m_lSocket.back());
  }

  // Lancement des deux threads en parallèles
  m_threadLoopSocket.launch();
  m_threadLoopGame.launch();
}

CServer::~CServer()
{
  m_running(false);
  
  for (std::list<sf::UdpSocket*>::iterator it = m_lSocket.begin(); it < m_lSocket.end(); it++)
    delete *it;
}

void  CServer::LoopSocket()
{
  sf::Packet  packet;
  std::string sPacketData;
  
  while (m_running)
  {
    if (m_socketSelector.wait())
    {
      // Boucle permet de lire toutes les sockets prêtes à recevoir
      // Cette boucle ne s'exécute que si au moins une des sockets est prête
      for (std::list<sf::UdpSocket*>::iterator it = m_lSocket.begin(); it < m_lSocket.end(); it++)
      {
        if (m_socketSelector.isReady(*it))
        {
          if (*it.receive(packet) == sf::Socket::Done)
          {
            packet >> sPacketData;
            switch (*sPacketData)
            {
              case UPDATE :
                m_worldMap.update(sPacketData);
                break;
              case NEW :
                m_worldMap.addPlayer(sPacketData + 1, 0, 0);
                break;
              case QUIT :
                m_worldMap.removePlayer(sPacketData + 1);
                break;
              default :
                break;
            }
          }
        }
      }
    }
    sf::sleep(sf::milliseconds(10));
  }
}

void  CServer::LoopGame()
{
  while (m_running)
  {
    sf::Time elapsed = clock.restart();
    m_worldBox.update(elapsed);
  
    sf::sleep(sf::milliseconds(10));
  }
}

