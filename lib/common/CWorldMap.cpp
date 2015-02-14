//
//  @ Project :   PIRATES
//  @ File Name : CWorldMap.cpp
//  @ Date :      12/11/2014
//  @ Author :    Romain
//


#include <common/CWorldMap.h>


CWorldMap::CWorldMap() :
m_vPlayers()
{

}

CWorldMap::~CWorldMap()
{
  for (std::vector<CPlayer*>::iterator it = m_vPlayers.begin(); it != m_vPlayers.end(); it++)
    free(*it);
}


void  CWorldMap::addPlayer(std::string name, int x, int y)
{
  m_vPlayers.push_back(new CPlayer(name, x, y));
}

void  CWorldMap::removePlayer(std::string name)
{
  for (std::vector<CPlayer*>::iterator it = m_vPlayers.begin(); it != m_vPlayers.end(); it++)
  {
    if ((*it)->getName() == name)
      m_vPlayers.erase(it);
  }
}

void    CWorldMap::clear()
{
    for(std::vector<CPlayer*>::iterator it = m_vPlayers.begin(); it != m_vPlayers.end(); it++)
        (*it)->clear();
}

int    CWorldMap::update(CMapQuery &in)
{
    int i;

    clear();
    while (in >> i)
    {
        switch (i)
        {
            case NWorldMap::PLAYER :
                i = m_vPlayers[in.next()]->update(in);
                break;
            default :
                return i;
        }
    }
    return i;
}


