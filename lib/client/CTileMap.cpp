#include <client/CTileMap.h>


CTileMap::CTileMap(const std::string& tmxFile) :
sf::Drawable(),
sf::Transformable(),
m_map(tmxFile),
m_vVertices(),
m_tileset()
{
    m_tileset.loadFromFile(m_map.getTilesets().back().getImage().getSource());

    for (auto layer : m_map.getLayers())
    {
        m_vVertices.push_back(sf::VertexArray());
        m_vVertices.back().setPrimitiveType(sf::Quads);

        int tw = m_map.getTilewidth(), th = m_map.getTileheight();
        unsigned int i = 0;
        for (auto tile : layer->getData())
        {
            if (tile.getId())
            {
                int tx = (tile.getId() - m_map.getTilesets().back().getFirstGid()) % (m_tileset.getSize().x / tw);
                int ty = (tile.getId() - m_map.getTilesets().back().getFirstGid()) / (m_tileset.getSize().x / tw);

                sf::Vertex quad[4];

                quad[0].position = sf::Vector2f((i % m_map.getWidth()) * tw, (i / m_map.getWidth()) * th);
                quad[1].position = sf::Vector2f(((i % m_map.getWidth()) + 1) * tw, (i / m_map.getWidth()) * th);
                quad[2].position = sf::Vector2f(((i % m_map.getWidth()) + 1) * tw, ((i / m_map.getWidth()) + 1) * th);
                quad[3].position = sf::Vector2f((i % m_map.getWidth()) * tw, ((i / m_map.getWidth()) + 1) * th);

                quad[0].texCoords = sf::Vector2f(tx * tw, ty * th);
                quad[1].texCoords = sf::Vector2f((tx + 1) * tw, ty * th);
                quad[2].texCoords = sf::Vector2f((tx + 1) * tw, (ty + 1) * th);
                quad[3].texCoords = sf::Vector2f(tx * tw, (ty + 1) * th);

                for (int j = 0; j < 4; j++)
                    m_vVertices.back().append(quad[j]);
            }
            i++;
        }
    }
}

void    CTileMap::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    states.texture = &m_tileset;
    for (auto vertices : m_vVertices)
        target.draw(vertices, states);
}


