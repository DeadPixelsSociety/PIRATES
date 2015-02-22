#include <common/CMapQuery.h>


sf::Packet& operator>>(sf::Packet& packet, sf::Vector2f& in)
{
    return packet >> in.x >> in.y;
}

sf::Packet& operator<<(sf::Packet& packet, sf::Vector2f in)
{
    return packet << in.x << in.y;
}


