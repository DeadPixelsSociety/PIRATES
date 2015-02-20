#ifndef CRENDERPLAYER_H
#define CRENDERPLAYER_H


#include <string>

#include <common/SFML.h>
#include <client/CRender.h>
#include <common/CWorldMap.h>
#include <common/CPlayer.h>


class CRenderPlayer : CRender
{
    public :
        CRenderPlayer(std::string name, sf::Texture* in);
        ~CRenderPlayer();

        void    update(CWorldMap &in);

    private :

}


#endif


