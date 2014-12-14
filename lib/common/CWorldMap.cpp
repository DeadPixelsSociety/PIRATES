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
  // Destroy all Players dynamically memory allowed in CWorldMap::addPlayer
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

void  CWorldMap::update(std::string in)
{
    int i = 0;
    while (in[i])
    {
        switch (in[i])
        {
            case NWorldMap::PLAYER :
                m_vPlayers[in[i + 1]]->update(in.substr(i + 3, in[i + 2]));
                i += in[i + 2] + 3;
                break;
            default :
                i++;
                break;
        }
    }
}


