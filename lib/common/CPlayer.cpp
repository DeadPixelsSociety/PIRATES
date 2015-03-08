//
//  @ Project :   PIRATES
//  @ File NAme : CPlayer.cpp
//  @ Date :      12/11/2014
//  @ Author :    Romain
//


#include <common/CPlayer.h>


CPlayer::CPlayer(int id, sf::Vector2f position, std::string name) :
CObject(id),
CPositionable(position),
m_sName(name),
m_iState()
{
    for (int i = 0; i < NPlayer::NbStates; i++)
        m_iState[i] = 0;
}

int    CPlayer::update(CQuery &in)
{
    int i;
    while (in >> i)
    {
        switch (i)
        {
            case NPlayer::Position :
                in >> m_position;
                break;
            case NPlayer::State :
                m_iState[in.nextInt()] = in.nextInt();
                break;
            default :
                return i;
                break;
        }
    }
    return i;
}

