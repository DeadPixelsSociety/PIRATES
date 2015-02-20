#ifndef CRENDER_H
#define CRENDER_H


#include <iostream>

#include <common/SFML.h>
#include <common/CWorldMap.h>


class CRender
{
    public :
        CRender(std::string name);
        CRender(std::string name, sf::Texture in);
        ~CRender();

        void    update(sf::Vector2f in);
        void    render(sf::RenderWindow& in);

    private :
        sf::Texture*            m_texture;
        std::vector<sf::Sprite> m_vSprites;
        sf::Sprite*             m_sprite;
};

#endif


