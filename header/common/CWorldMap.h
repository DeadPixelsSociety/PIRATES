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
#include <common/CQuery.h>


namespace NWorldMap
{
    enum EUpdate
    {
        Add,
        Delete,
        Update
    };

    enum EObject
    {
        Player
    };
}


class CMapObject;


class CWorldMap : public std::map<int, CMapObject*>
{
    public :
        int                 update(CMapQuery &in);
        inline CMapObject*  getObject(int id)       {return at(id);}
};


#endif

