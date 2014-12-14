//
//  @ Project :   PIRATES
//  @ File Name : CWorldMap.h
//  @ Date :      20/10/2014
//  @ Author :
//


#ifndef CWORLDMAP_H
#define CWORLDMAP_H


#include <string>
#include <vector>

#include <common/CPlayer.h>


namespace NWorldMap
{
    enum EUpdate
    {
        PLAYER
    };
}


class CWorldMap
{
    public :
        CWorldMap();
        ~CWorldMap();

        void  addPlayer(std::string name, int x, int y);
        void  removePlayer(std::string name);
        void  update(std::string in);

    private :
        std::vector<CPlayer*> m_vPlayers;
};


#endif

