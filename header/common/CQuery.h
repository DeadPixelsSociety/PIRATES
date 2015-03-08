#ifndef CQUERY_H
#define CQUERY_H


#include <common/SFML.h>


sf::Packet&  operator>>(sf::Packet& packet, sf::Vector2f& in);
sf::Packet&  operator<<(sf::Packet& packet, sf::Vector2f in);


class CQuery : public sf::Packet
{
    public :
        inline int          nextInt()       {int i; sf::Packet::operator>>(i); return i;};
        inline std::string  nextString()    {std::string i; sf::Packet::operator>>(i); return i;}
        inline sf::Vector2f nextVector2f()  {sf::Vector2f i; *this >> i; return i;}

};


#endif


