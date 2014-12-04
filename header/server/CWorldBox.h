//
//  @ Project : PIRATES
//  @ File Name : CWorld.h
//  @ Date : 20/10/2014
//  @ Author : Romain
//


#ifndef _CWORLD_H
#define _CWORLD_H


#include "Box2D.h"
#include "SFML.h"


class CWorldBox
{
  public :
    CWorldBox();
    ~CWorldBox();
    
    void  update(sf::Time elapsed);
  
  private :
    b2Vec2    m_gravity;
    b2World   m_world;
    b2Body*   m_pGroundBody;
};



#endif // _CWORLD_H

