#ifndef CTILEMAP_H
#define CTILEMAP_H


#include <vector>

#include <common/SFML.h>
#include <common/TMX.h>


class CTileMap : public sf::Drawable, public sf::Transformable
{
    public :
        CTileMap(const std::string& tmxFile);

    private :
        virtual void    draw(sf::RenderTarget& target, sf::RenderStates states) const;

        tmx::Map        m_map;
        std::vector<sf::VertexArray> m_vVertices;
        sf::Texture     m_tileset;
};


#endif


