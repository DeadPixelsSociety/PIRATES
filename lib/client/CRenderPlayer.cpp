#include <client/CRenderPlayer.h>


CRenderPlayer::CRenderPlayer(sf::Texture* in, CPlayer* player) :
CRender(in),
m_player(player)
{
    m_vSprites.back().setTextureRect(sf::IntRect(0, 0, 32, 65));
    for (int i = 1; i < 16 ; i++)
    {
        m_vSprites.push_back(sf::Sprite());
        m_vSprites.back().setTexture(*m_texture);
        m_vSprites.back().setTextureRect(sf::IntRect((i % 4) * 32, (i / 4) * 65, 32, 65));
    }
}


void    CRenderPlayer::update()
{
    switch (m_player->getState(NPlayer::Direction))
    {
        case NPlayer::Up :
            m_sprite = 13;
            break;
        case NPlayer::Left :
            m_sprite = 5;
            break;
        case NPlayer::Down :
            m_sprite = 1;
            break;
        case NPlayer::Right :
            m_sprite = 9;
            break;
        default :
            m_sprite = 0;
            break;
    }
    CRender::update(m_player->getPosition());
}


