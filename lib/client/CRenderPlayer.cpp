#include <client/CRenderPlayer.h>


CRenderPlayer::CRenderPlayer(std::string name, sf::Texture* in) : CRender(name, in)
{
    m_vSprites.push_back();
    m_vSprites.back().setTexture(m_texture);
    m_vSprites.push_back();
    m_vSprites.back().setTexture(m_texture);
    m_vSprites.push_back();
    m_vSprites.back().setTexture(m_texture);
}

CRenderPlayer::~CRenderPlayer()
{

}

void    CRenderPlayer::update(CWorldMap &in)
{
    switch (in.getPlayer(name)->getState(NPlayer::DIRECTION))
    {
        case NPlayer::UP :
            m_sprite = m_vSprites[0];
            break;
        case NPlayer::LEFT :
            m_sprite = m_vSprites[1];
            break;
        case NPlayer::DOWN :
            m_sprite = m_vSprites[2];
            break;
        case NPlayer::RIGHT :
            m_sprite = m_vSprites[3];
            break;
        default :
            break;
    }
}


