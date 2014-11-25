//
//  @ Project : PIRATES
//  @ File Name : CServer.h
//  @ Date : 20/10/2014
//  @ Author : 
//


#ifndef _CSERVER_H
#define _CSERVER_H


#include "SFML.h"
#include "CWorldMap.h"
#include "CWorldBox.h"


class CServer
{
  public :
          CServer(int nbMaxPlayer);
          ~CServer();
          
  	void  LoopSocket();
  	void  LoopGame();
  	
  	
  private :
    sf::Thread    m_threadLoopSocket; // Thread gérant la partie réseau
    sf::Thread    m_threadLoopGame;   // Thread gérant la partie physique
  
  	CWorldMap     m_worldMap; // Carte des élements dynamiques et de leurs états
  	CWorldBox     m_worldBox; // Univers physique Box2D
  	
  	sf::Clock     m_clock;
  	
  	std::list<sf::UdpSocket*> m_lSocket;
  	sf::SocketSelector        m_socketSelector;
  	
  	bool  m_running;
};

#endif  //_CSERVER_H
