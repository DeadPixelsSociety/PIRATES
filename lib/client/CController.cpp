#include <client/CController.h>


void    CController::getInput(CQuery& in)
{
    int i = 0;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        i = NPlayer::Up;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        i = NPlayer::Right;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        i = NPlayer::Down;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        i = NPlayer::Left;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)
    && sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        i = NPlayer::UpRight;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)
    && sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        i = NPlayer::RightDown;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)
    && sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        i = NPlayer::DownLeft;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)
    && sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        i = NPlayer::LeftUp;

    in << NPlayer::State << NPlayer::Direction << i;
}


