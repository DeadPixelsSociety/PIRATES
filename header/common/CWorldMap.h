//
//  @ Project :   PIRATES
//  @ File Name : CWorldMap.h
//  @ Date :      20/10/2014
//  @ Author : 
//


#ifndef _CWORLDMAP_H
#define _CWORLDMAP_H


#include "string.h"


class CWorldMap
{
  public :
    CWorldMap();
    ~CWorldMap();
    
    void  addPlayer(std::string name, int x, int y);
    void  removePlayer(std::string name);
    void  update(std::string in);
    
  private:
  	std::list<CPlayer*>      m_lPlayers;
};


#endif  //_CWORLDMAP_H

