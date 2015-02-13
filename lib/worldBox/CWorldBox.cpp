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

std::string  CWorldBox::update(CWorldMap *worldMap, sf::Time elapsed)
{
    std::string sUpdate;

    for (std::vector<CPlayer*>::iterator it = worldMap->m_vPlayers.begin(); it != worldMap->m_vPlayers.end(); it++)
    {
        if ((*it)->m_iState[NPlayer::DIRECTION] == NPlayer::LEFT)
        {
            std::cout << "changement coordonnées\n";
            sUpdate += NWorldMap::PLAYER;
            sUpdate += (char)0;
            sUpdate += NPlayer::POSITION;
        }
    }

    return sUpdate;
}

