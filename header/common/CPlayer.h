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
    CPlayer();
    ~CPlayer();
    
  private :
    string            m_sName;
    sf::Vector2<int>  m_vPosition;
}


#endif

