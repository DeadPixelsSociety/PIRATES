//
//  @ Project : PIRATES
//  @ File Name : CWorldBox.cpp
//  @ Date : 20/10/2014
//  @ Author : Romain
//


#include <worldBox/CWorldBox.h>



CWorldBox::CWorldBox() :
m_gravity(0.0f, -9.8f),
m_world(m_gravity)
{
  b2BodyDef       groundBodyDef;
  b2PolygonShape  groundBox;


  groundBodyDef.position.Set(0.0f, -9.8f);
  m_pGroundBody = m_world.CreateBody(&groundBodyDef);
  groundBox.SetAsBox(100.0f, 100.0f);   // Half-width and Half-height
  m_pGroundBody->CreateFixture(&groundBox, 0.0f);
}

CWorldBox::~CWorldBox()
{

}

CMapQuery  CWorldBox::update(CWorldMap *worldMap, sf::Time elapsed)
{
    CMapQuery mapQuery;

    for (std::vector<CPlayer*>::iterator it = worldMap->m_vPlayers.begin(); it != worldMap->m_vPlayers.end(); it++)
    {
        if ((*it)->m_iState[NPlayer::DIRECTION])
        {
            switch((*it)->m_iState[NPlayer::DIRECTION])
            {
                case NPlayer::UP :
                    (*it)->m_vPosition.y -= 3;
                    break;
                case NPlayer::RIGHT :
                    (*it)->m_vPosition.x += 3;
                    break;
                case NPlayer::DOWN :
                    (*it)->m_vPosition.y += 3;
                    break;
                case NPlayer::LEFT :
                    (*it)->m_vPosition.x -= 3;
                    break;
                default :
                    break;
            }
            mapQuery << NWorldMap::PLAYER << (int)std::distance(worldMap->m_vPlayers.begin(), it);
            mapQuery << NPlayer::POSITION << (*it)->m_vPosition.x << (*it)->m_vPosition.y;
        }
    }

    return mapQuery;
}

