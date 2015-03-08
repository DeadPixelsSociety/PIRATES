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
#include <common/TMX.h>
#include <common/CObject.h>
#include <common/CQuery.h>
#include <common/CPlayer.h>


#define SCALING 30.f


class CMapQuery;
class CMapObject;
class CPlayer;

class CWorldBox
{
  public :
    CWorldBox(const std::string& tmxFile);

    CMapQuery   update(CWorldMap& worldMap);
    void        update(CPlayer* player);


  private :
    tmx::Map    m_map;

    sf::Clock   m_clock;
    sf::Time    m_elapsed;

    b2World   m_world;

    std::map<int, b2Body*>  m_mBodyObjects;
};



#endif // _CWORLD_H

