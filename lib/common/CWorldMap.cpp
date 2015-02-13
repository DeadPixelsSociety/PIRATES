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

int  CWorldMap::update(std::string in)
{
    unsigned int i = 0;
    while (i < in.length())
    {
        switch (in[i])
        {
            case NWorldMap::PLAYER :
                i += m_vPlayers[(int)in[i + 1]]->update(in.erase(0, 2));
                break;
            default :
                return i;
                break;
        }
    }
    return i;
}

void CWorldMap::printUpdate(std::string in)
{
    for (unsigned int i = 0; i < in.length(); i++)
    {
        std::cout << (int)in[i] << ".";
    }
    std::cout << std::endl;
}


