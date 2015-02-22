#ifndef CRENDERPLAYER_H
#define CRENDERPLAYER_H


#include <string>

#include <common/SFML.h>
#include <client/CRender.h>
#include <common/CWorldMap.h>
#include <common/CPlayer.h>


class CRenderPlayer : public CRender
{
    public :
        CRenderPlayer(sf::Texture* in, CPlayer* player);

        virtual void    update();

    private :
        CPlayer*    m_player;
};


#endif


