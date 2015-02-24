#include <client/CController.h>


void    CController::getInput(CMapQuery& in)
{
    int i = 0;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        i += NPlayer::Up;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        i += NPlayer::Right;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        i += NPlayer::Down;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        i += NPlayer::Left;

    in << NPlayer::State << NPlayer::Direction << i;
}


