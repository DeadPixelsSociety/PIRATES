#ifndef CRENDERPLAYER_H
#define CRENDERPLAYER_H


#include <string>
#include <Thor/Animations.hpp>

#include <common/SFML.h>
#include <client/CRender.h>
#include <common/CPlayer.h>


class CRenderPlayer : public CRender
{
    public :
        CRenderPlayer(sf::Texture* in, CPlayer* player);

        virtual void    update();
        void            render(CRenderWindow* in);

    private :
        CPlayer*                m_player;
        thor::FrameAnimation    m_animation[4];
        thor::Animator<sf::Sprite, int> m_animator;
        sf::Clock               m_frameClock;
};


#endif


