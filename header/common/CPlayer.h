//
//  @ Project :   PIRATES
//  @ File Name : CPlayer.h
//  @ Date :      12/11/2014
//  @ Author :    Romain
//


#ifndef _CPLAYER_H
#define _CPLAYER_H


#include "SFML.h"


class CPlayer
{
  public :
    CPlayer(std::string name, int x, int y);
    ~CPlayer();
    
    inline  void  setName(std::string in)   {m_sName = in;}
    inline  void  setPosition(int x, int y) {m_vPosition.x = x; m_vPosition.y = y;}
    
    inline  std::string       getName()     {return m_sName;}
    inline  sf::Vector2<int>  getPosition() {return m_vPosition;}
    
  private :
    std::string       m_sName;
    sf::Vector2<int>  m_vPosition;
};


#endif

