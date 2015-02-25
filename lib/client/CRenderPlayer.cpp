#include <client/CRenderPlayer.h>


CRenderPlayer::CRenderPlayer(sf::Texture* in, CPlayer* player) :
CRender(in),
m_player(player)
{
    makeRects(16, 32, 65);
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
            m_animation[i].addFrame(1.f, m_vRects[i * 4 + j]);
        m_animator.addAnimation(i, m_animation[i], sf::seconds(1.f));
    }
}

void    CRenderPlayer::update()
{
    int anim = -1;
    switch (m_player->getState(NPlayer::Direction))
    {
        case NPlayer::Up :
            anim = 3;
            break;
        case NPlayer::Right :
            anim = 2;
            break;
        case NPlayer::Down :
            anim = 0;
            break;
        case NPlayer::Left :
            anim = 1;
            break;
        case NPlayer::UpRight :
            anim = 2;
            break;
        case NPlayer::RightDown :
            anim = 2;
            break;
        case NPlayer::DownLeft :
            anim = 1;
            break;
        case NPlayer::LeftUp :
            anim = 1;
            break;
        default :
            if (m_animator.isPlayingAnimation())
                m_animator.stopAnimation();
            break;
    }
    if (anim != - 1
    && (!m_animator.isPlayingAnimation()
    || (m_animator.isPlayingAnimation() && m_animator.getPlayingAnimation() != anim)))
    {
        m_rect = anim * 4;
        m_animator.playAnimation(anim);
    }

    CRender::update();
    CRender::update(m_player->getPosition());
    if (m_animator.isPlayingAnimation())
    {
        m_animator.update(m_frameClock.restart());
        m_animator.animate(m_sprite);
    }
}

void    CRenderPlayer::render(CRenderWindow* in)
{
    CRender::render(in);
}


