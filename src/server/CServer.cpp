//
//  @ Project : PIRATES
//  @ File Name : CServer.cpp
//  @ Date : 20/10/2014
//  @ Author : 
//


#include "CServer.h"


CServer::CServer() :
m_clock(),
m_threadLoopIn(&CServer::LoopIn),
m_threadLoopGame(&CServer::LoopGame),
m_threadLoopOut(&CServer::LoopOut)
{
  
}

CServer::~CServer()
{

}

void CServer::Initialize(int iNbMaxPlayer)
{
  m_threadLoopIn.launch();
  m_threadLoopGame.launch();
  m_threadLoopOut.launch();
}

void  CServer::LoopIn()
{
  handleIncomingPackets();
  handleIncomingConnection();
}

void  CServer::LoopGame()
{

  sf::Time elapsed = clock.restart();
  m_world.update(elapsed):
  
  sf::sleep(sf::)
}

void  CServer::LoopOut()
{
  handleOutComingPackets();
}
