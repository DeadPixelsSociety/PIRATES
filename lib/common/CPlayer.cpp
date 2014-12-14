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

void    CPlayer::update(std::string in)
{
    int i = 0;

    while (in[i])
    {
        switch (in[i])
        {
            case NPlayer::NAME :
                m_sName = in.substr(i + 2, in[i + 1]);
                i = in[i + 1] + 1;
                break;
            case NPlayer::POSITION :
                m_vPosition.x = atoi(in.substr(i + 1, 4).data());
                m_vPosition.y = atoi(in.substr(i + 5, 4).data());
                i += 9;
                break;
            case NPlayer::STATE :
                m_iState[(int)in[i + 1]] = in[i + 2];
                i += 2;
                break;
            default :
                i++;
                break;
        }
    }
}

