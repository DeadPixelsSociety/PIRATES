//
//  @ Project :   PIRATES
//  @ File Name : CServer.cpp
//  @ Date :      20/10/2014
//  @ Author :    ROmain
//


#include "CServer.h"


CServer::CServer(int iNbMaxPlayer) :
m_clock(),
m_threadLoopSocket(&CServer::LoopSocket),
m_threadLoopGame(&CServer::LoopGame),
m_worldMap(),
m_worldBox(),
m_lSocket(),
m_socketSelector()
{
  // Ouverture et mise en écoute des nbMaxPlayer Sockets permettant au serveur
  // de recevoir les données des clients
  for (int i = 0; i < nbMaxPlayer; i++)
  {
    m_lSocket.push_back(sf::UdpSocket());
    m_lSocket->bind(54000);
    m_socketSelector.add(m_lSocket);
  }

  // Lancement des deux threads en parallèles
  m_threadLoopSocket.launch();
  m_threadLoopGame.launch();
}

CServer::~CServer()
{

}

void  CServer::LoopSocket()
{
  if (m_socketSelector.wait())
  {
    // Boucle permettant de lire toutes les sockets prêtes à recevoir
    // Cette boucle ne s'exécute que si au moins une des sockets est prête
    for (std::list<sf::UdpSocket*>::iterator it = m_lSocket.begin(); it < m_lSocket.end(); it++)
    {
      if (m_socketSelector.isReady(*it))
      {
        sf::Packet  packet;
        if (*it.receive(packet) == sf::Socket::Done)
        {
          // Traitement du packet
          // mise à jour de worldMap en fonction des données reçues
          // attention à bien safe-thread les données
        }
      }
    }
  }
  sf::sleep(sf::milliseconds(10));
}

void  CServer::LoopGame()
{

  sf::Time elapsed = clock.restart();
  m_world.update(elapsed);
  
  sf::sleep(sf::milliseconds(10));
}

