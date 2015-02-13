//
//  @ Project : PIRATES
//  @ File Name : CWorld.h
//  @ Date : 20/10/2014
//  @ Author : Romain
//


#ifndef _CWORLD_H
#define _CWORLD_H


#include <Box2D/Box2D.h>
#include <common/SFML.h>

#include <common/CWorldMap.h>


class CWorldMap;

class CWorldBox
{
  public :
    CWorldBox();
    ~CWorldBox();

    std::string  update(CWorldMap *worldMap, sf::Time elapsed);

  private :
    b2Vec2    m_gravity;
    b2World   m_world;
    b2Body*   m_pGroundBody;
};



#endif // _CWORLD_H

