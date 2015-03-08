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
#include <common/CObject.h>
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


class CObject;


class CWorldMap : public std::map<int, CObject*>
{
    public :
        int                 update(CQuery &in);
        inline CObject*  getObject(int id)       {return at(id);}
};


#endif

