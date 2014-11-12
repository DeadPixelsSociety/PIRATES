//
//  @ Project :   PIRATES
//  @ File Name : CWorldMap.h
//  @ Date :      20/10/2014
//  @ Author : 
//


#ifndef _CWORLDMAP_H
#define _CWORLDMAP_H


class CWorldMap
{
  public :
    CWorldMap();
    ~CWorldMap();
    
  private:
  	std::list<CPlayer*>      m_lPlayers;
};


#endif  //_CWORLDMAP_H

