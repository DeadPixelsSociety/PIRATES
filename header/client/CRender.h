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

                void    makeRects(int nbTile, int tileWidth, int tileHeight);

    protected :
        sf::Texture*                m_texture;
        sf::Sprite                  m_sprite;
        std::vector<sf::IntRect>    m_vRects;
        int                         m_rect;

};

#endif


