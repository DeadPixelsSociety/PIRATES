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
#include <common/CMapObject.h>
#include <common/CMapQuery.h>
#include <common/CPlayer.h>


class CMapQuery;
class CMapObject;
class CPlayer;

class CWorldBox
{
  public :
    CWorldBox();
    ~CWorldBox();

    CMapQuery   update(std::vector<CMapObject*>& vObject, sf::Time elapsed);
    void        update(CPlayer* player);


  private :
    CMapQuery   m_mapQuery;

    sf::Time    m_elapsed;

    b2Vec2    m_gravity;
    b2World   m_world;
    b2Body*   m_pGroundBody;
};



#endif // _CWORLD_H

