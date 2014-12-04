//
//  @ Project :   PIRATES
//  @ File Name : CWorldMap.cpp
//  @ Date :      12/11/2014
//  @ Author :    Romain
//


#include "CWorldMap.h"


CWorldMap::CWorldMap() :
m_lPlayers()
{
  
}

CWorldMap::~CWorldMap()
{
  // Destroy all Players dynamically memory allowed in CWorldMap::addPlayer
  for (std::list<CPlayer*>::iterator it = m_lPlayers.begin(); it != m_lPlayers.end(); it++)
    free(*it);
}


void  CWorldMap::addPlayer(std::string name, int x, int y)
{
  m_lPlayers.push_back(new CPlayer(name, x, y));
}

void  CWorldMap::removePlayer(std::string name)
{
  for (std::list<CPlayer*>::iterator it = m_lPlayers.begin(); it != m_lPlayers.end(); it++)
  {
    if ((*it)->getName() == name)
      m_lPlayers.erase(it);
  }
}

void  CWorldMap::update(std::string in)
{
  // lire la chaine in formatée pour modifier la map
}
