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
#include <common/CMapQuery.h>


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


class CWorldMap
{
    public :
        CWorldMap();
        ~CWorldMap();

        int     update(CMapQuery &in);
        inline  CMapObject*    getObject(int id)   {return m_vObjects[id];}
        inline  std::vector<CMapObject*>&   getVObjects()  {return m_vObjects;}

    private :
        std::vector<CMapObject*> m_vObjects;
};


#endif

