#ifndef CRENDER_H
#define CRENDER_H


#include <iostream>

#include <common/SFML.h>
#include <common/CWorldMap.h>
#include <client/CRenderWindow.h>


class CRenderWindow;


class CRender
{
    public :
                        CRender(sf::Texture* in);
        virtual         ~CRender();

        virtual void    update();
        virtual void    update(sf::Vector2f in);
        virtual void    render(CRenderWindow* in);

    protected :
        sf::Texture*            m_texture;
        std::vector<sf::Sprite> m_vSprites;
        int                     m_sprite;
};

#endif


