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

}

CPlayer::~CPlayer()
{

}

int    CPlayer::update(std::string in)
{
    unsigned int i = 0;
    while (in[i])
    {
        switch (in[i])
        {
            case NPlayer::POSITION :
                m_vPosition.x += 3;
                std::cout << "position x = " << m_vPosition.x << "\n";
                i += 1;
                break;
            case NPlayer::STATE :
                m_iState[(int)in[i + 1]] = in[i + 2];
                i += 3;
                break;
            default :
                return i;
                break;
        }
    }
    return i;
}

