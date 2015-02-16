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

#include <common/SFML.h>
#include <common/CPlayer.h>
#include <worldBox/CWorldBox.h>


namespace NWorldMap
{
    enum EUpdate
    {
        PLAYER
    };
}


class CMapQuery : public sf::Packet
{
    public :
        inline  CMapQuery() : Packet()   {};
        inline  ~CMapQuery()             {};

        inline  int next()  {int i; operator>>(i); return i;};
};

class CPlayer;

class CWorldMap
{
    friend class CWorldBox;
    friend class CClient;

    public :
        CWorldMap();
        ~CWorldMap();

        void    addPlayer(std::string name, int x, int y);
        void    removePlayer(std::string name);
        inline  CPlayer*    getPlayer(int in)   {return m_vPlayers[in];}
        int     update(CMapQuery &in);

    private :
        std::vector<CPlayer*> m_vPlayers;
};


#endif

