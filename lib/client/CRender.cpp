#include <client/CRender.h>


CRender::CRender(sf::Texture* in) :
m_texture(in),
m_vSprites(),
m_sprite(0)
{
    m_vSprites.push_back(sf::Sprite());
    m_vSprites.back().setTexture(*m_texture);
}

CRender::~CRender()
{

}

void    CRender::update()
{

}

void    CRender::update(sf::Vector2f in)
{
    for (std::vector<sf::Sprite>::iterator it = m_vSprites.begin(); it != m_vSprites.end(); it++)
        it->setPosition(in);
}

void    CRender::render(CRenderWindow* in)
{
    in->draw(m_vSprites[m_sprite]);
}


