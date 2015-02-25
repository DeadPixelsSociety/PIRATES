#include <client/CRender.h>


CRender::CRender(sf::Texture* in) :
m_texture(in)
{
    m_sprite.setTexture(*m_texture);
}

CRender::~CRender()
{

}

void    CRender::makeRects(int nbTile, int tileWidth, int tileHeight)
{
    for (int i = 0; i < nbTile; i++)
        m_vRects.push_back(sf::IntRect((i % (m_texture->getSize().x / tileWidth)) * tileWidth, (i / (m_texture->getSize().x / tileWidth)) * tileHeight, tileWidth , tileHeight));
}

void    CRender::update()
{
    m_sprite.setTextureRect(m_vRects[m_rect]);
}

void    CRender::update(sf::Vector2f in)
{
    m_sprite.setPosition(in);
}

void    CRender::render(CRenderWindow* in)
{
    in->draw(m_sprite);
}


