#ifndef CMAPQUERY_H
#define CMAPQUERY_H


#include <common/SFML.h>


sf::Packet&  operator>>(sf::Packet& packet, sf::Vector2f& in);
sf::Packet&  operator<<(sf::Packet& packet, sf::Vector2f in);


class CMapQuery : public sf::Packet
{
    public :
        inline  CMapQuery() : sf::Packet()   {};

        inline  int nextInt()  {int i; sf::Packet::operator>>(i); return i;};
        inline  std::string nextString()  {std::string i; sf::Packet::operator>>(i); return i;}
        inline  sf::Vector2f    nextVector2f()  {sf::Vector2f i; *this >> i; return i;}

};


#endif


