//
//  @ Project : PIRATES
//  @ File Name : CWorldBox.cpp
//  @ Date : 20/10/2014
//  @ Author : Romain
//


#include <worldBox/CWorldBox.h>



CWorldBox::CWorldBox() :
m_mapQuery(),
m_elapsed(),
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

CMapQuery  CWorldBox::update(std::vector<CMapObject*>& vObjects, sf::Time elapsed)
{
    m_mapQuery.clear();
    m_elapsed = elapsed;

    for (std::vector<CMapObject*>::iterator it = vObjects.begin(); it != vObjects.end(); it++)
        update((CPlayer*)*it);

    return m_mapQuery;
}

void    CWorldBox::update(CPlayer* player)
{
    if (player->getState(NPlayer::Direction))
    {
        switch(player->getState(NPlayer::Direction))
        {
            case NPlayer::Up :
                player->addPosY(-3);
                break;
            case NPlayer::Right :
                player->addPosX(3);
                break;
            case NPlayer::Down :
                player->addPosY(3);
                break;
            case NPlayer::Left :
                player->addPosX(-3);
                break;
            default :
                break;
        }
        player->setState(NPlayer::Direction, 0);
        m_mapQuery << NWorldMap::Update << player->id() << NPlayer::Position << player->getPosition();
    }
}


