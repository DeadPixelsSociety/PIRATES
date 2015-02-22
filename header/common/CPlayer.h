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
#include <common/CPositionable.h>
#include <common/CMapObject.h>


namespace NPlayer
{
    enum EUpdate
    {
        Name,
        Position,
        State
    };

    enum EState
    {
        Direction,
        Speed,
        NbStates = 2
    };

    enum EDirection
    {
        Up          = 1,
        Right       = 2,
        Down        = 4,
        Left        = 8,
    };
}


class CMapQuery;

class CPlayer : public CMapObject, public CPositionable
{
  public :
    CPlayer(int id, sf::Vector2f position, std::string name);

    int    update(CMapQuery &in);

    inline  std::string getName()    {return m_sName;}
    inline  int         getState(int i) {return m_iState[i];}
    inline  void        setState(int i, int in) {m_iState[i] = in;}

  private :
    std::string     m_sName;
    int             m_iState[NPlayer::NbStates];
};


#endif

