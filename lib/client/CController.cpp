#include <client/CController.h>


void    CController::getInput(CMapQuery& in)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        in << NPlayer::State << NPlayer::Direction << NPlayer::Up;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        in << NPlayer::State << NPlayer::Direction << NPlayer::Right;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        in << NPlayer::State << NPlayer::Direction << NPlayer::Down;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        in << NPlayer::State << NPlayer::Direction << NPlayer::Left;
}


