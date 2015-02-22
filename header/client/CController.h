#ifndef CCONTROLLER_H
#define CCONTROLLER_H


#include <common/SFML.h>
#include <common/CWorldMap.h>
#include <common/CPlayer.h>


class CController
{
    public :
        static  void    getInput(CMapQuery& in);
};


#endif


