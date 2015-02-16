//
//  @ Project :   PIRATES
//  @ File Name : CPlayer.h
//  @ Date :      12/11/2014
//  @ Author :    Romain
//


#ifndef CPLAYER_H
#define CPLAYER_H


#include <string>
#include <iostream>

#include <common/SFML.h>
#include <common/CWorldMap.h>


namespace NPlayer
{
    enum EUpdate
    {
        NAME,
        POSITION,
        STATE
    };

    enum EState
    {
        DIRECTION,
        SPEED,
        NB_ITEMS = 2
    };

    enum EDirection
    {
        UP          = 1,
        RIGHT       = 2,
        DOWN        = 4,
        LEFT        = 8,
    };

    enum ESpeed
    {
        STATIC,
        WALK,
        RUN,
        SPRINT
    };
}


class CMapQuery;

class CPlayer
{
    friend class CWorldBox;

  public :
    CPlayer(std::string name, int x, int y);
    ~CPlayer();

    int    update(CMapQuery &in);

    inline std::string getName()    {return m_sName;}
    inline sf::Vector2<int> getPos()    {return m_vPosition;}

  private :
    std::string         m_sName;
    sf::Vector2<int>    m_vPosition;
    int                 m_iState[NPlayer::NB_ITEMS];
};


#endif

