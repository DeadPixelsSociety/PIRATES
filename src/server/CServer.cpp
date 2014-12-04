//
//  @ Project :   PIRATES
//  @ File Name : CServer.cpp
//  @ Date :      20/10/2014
//  @ Author :    Romain
//


#include "CServer.h"


CServer::CServer(int iNbMaxPlayer) :
m_clock(),
m_threadLoopSocket(&CServer::LoopSocket, this),
m_threadLoopGame(&CServer::LoopGame, this),
m_worldMap(),
m_worldBox(),
m_lSocket(),
m_socketSelector(),
m_running(true)
{
  // Ouverture et mise en écoute des nbMaxPlayer Sockets permettant au serveur
  // de recevoir les données des clients
  for (int i = 0; i < iNbMaxPlayer; i++)
  {
    m_lSocket.push_back(new sf::UdpSocket());
    m_lSocket.back()->bind(56747);
    m_socketSelector.add(*(m_lSocket.back()));
  }

  // Lancement des deux threads en parallèles
  m_threadLoopSocket.launch();
  m_threadLoopGame.launch();
}

CServer::~CServer()
{
  m_running = false;
  
  for (std::list<sf::UdpSocket*>::iterator it = m_lSocket.begin(); it != m_lSocket.end(); it++)
    delete *it;
}

void  CServer::LoopSocket()
{
  sf::IpAddress ip = "127.0.0.1";
  unsigned short port = 56747;
  sf::Packet  packet;
  std::string sPacketData;
  
  while (m_running)
  {
    if (m_socketSelector.wait())
    {
      // Boucle permet de lire toutes les sockets prêtes à recevoir
      // Cette boucle ne s'exécute que si au moins une des sockets est prête
      for (std::list<sf::UdpSocket*>::iterator it = m_lSocket.begin(); it != m_lSocket.end(); it++)
      {
        sf::UdpSocket &client = **it;
        if (m_socketSelector.isReady(client))
        {
          if (client.receive(packet, ip, port) == sf::Socket::Done)
          {
            packet >> sPacketData;
            m_worldMap.update(sPacketData);
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
    sf::Time elapsed = m_clock.restart();
    m_worldBox.update(elapsed);
  
    sf::sleep(sf::milliseconds(10));
  }
}

