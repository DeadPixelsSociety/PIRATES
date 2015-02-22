#include <client/CRenderPlayer.h>


CRenderPlayer::CRenderPlayer(sf::Texture* in, CPlayer* player) :
CRender(in),
m_player(player)
{
    m_vSprites.push_back(sf::Sprite());
    m_vSprites.back().setTexture(*m_texture);
    m_vSprites.push_back(sf::Sprite());
    m_vSprites.back().setTexture(*m_texture);
    m_vSprites.push_back(sf::Sprite());
    m_vSprites.back().setTexture(*m_texture);
}


void    CRenderPlayer::update()
{
    switch (m_player->getState(NPlayer::Direction))
    {
        case NPlayer::Up :
            m_sprite = 0;
            break;
        case NPlayer::Left :
            m_sprite = 1;
            break;
        case NPlayer::Down :
            m_sprite = 2;
            break;
        case NPlayer::Right :
            m_sprite = 3;
            break;
        default :
            break;
    }
    CRender::update(m_player->getPosition());
}


