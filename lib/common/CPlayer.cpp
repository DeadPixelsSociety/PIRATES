//
//  @ Project :   PIRATES
//  @ File NAme : CPlayer.cpp
//  @ Date :      12/11/2014
//  @ Author :    Romain
//


#include <common/CPlayer.h>


CPlayer::CPlayer(std::string name, int x, int y) :
m_sName(name),
m_vPosition(x, y)
{

}

CPlayer::~CPlayer()
{

}

