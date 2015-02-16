//
//  @ Project :   PIRATES
//  @ File NAme : CPlayer.cpp
//  @ Date :      12/11/2014
//  @ Author :    Romain
//


#include <common/CPlayer.h>


CPlayer::CPlayer(std::string name, int x, int y) :
m_sName(name),
m_vPosition(x, y),
m_iState()
{
    for (int i = 0; i < NPlayer::NB_ITEMS; i++)
        m_iState[i] = 0;
}

CPlayer::~CPlayer()
{

}

int    CPlayer::update(CMapQuery &in)
{
    int i;
    while (in >> i)
    {
        switch (i)
        {
            case NPlayer::POSITION :
                in >> m_vPosition.x >> m_vPosition.y;
                break;
            case NPlayer::STATE :
                m_iState[in.next()] = in.next();
                break;
            default :
                return i;
                break;
        }
    }
    return i;
}

