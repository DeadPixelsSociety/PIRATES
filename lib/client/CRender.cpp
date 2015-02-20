#include <client/CRender.h>


CRender::CRender(std::string name, sf::Texture* in) :
m_texture(in),
m_vSprite(),
m_sprite()
{
    m_vSprites.push_back();
    m_vSprites.back().setTexture(m_texture);
    m_sprite = m_vSprites.begin();
}

CRender::~CRender()
{

}

void    CRender::update(sf::Vector2f in)
{
    m_sprite->setPosition(in);
}

void    CRender::render(sf::RenderWindow& in)
{
    in.draw(*m_sprite);
}


