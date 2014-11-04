//
//  @ Project : PIRATES
//  @ File Name : CServer.h
//  @ Date : 20/10/2014
//  @ Author : 
//


#ifndef _CSERVER_H
#define _CSERVER_H


#include "CWorldMap.h"
#include "CWorld.h"


class CServer
{
  public :
          CServer();
          ~CServer();
  	void  Initialize(int iNbMaxPlayer);
  	void  LoopIn();
  	void  LoopGame();
  	void  LoopOut();
  	
  private :
    sf::Thread    m_threadLoopIn;
    sf::Thread    m_threadLoopGame;
    sf::Thread    m_threadLoopOut;
  
  	CWorldMap     m_pMap;
  	CWorld        m_world;
  	
  	sf::Clock     m_clock;
  	sf::UdpSocket m_socket;
};

#endif  //_CSERVER_H
