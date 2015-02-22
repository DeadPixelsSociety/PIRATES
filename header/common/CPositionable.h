#ifndef CPOSITIONABLE_H
#define CPOSITIONABLE_H


#include <common/SFML.h>


class CPositionable
{
    public :
        inline  CPositionable(sf::Vector2f in) : m_position(in) {}

        inline  const sf::Vector2f&    getPosition() const      {return m_position;}
        inline  void            setPosition(sf::Vector2f in)    {m_position = in;}
        inline  void            setPosX(float in)               {m_position.x = in;}
        inline  void            setPosY(float in)               {m_position.y = in;}
        inline  void            addPosX(float in)               {m_position.x += in;}
        inline  void            addPosY(float in)               {m_position.y += in;}

    protected :
        sf::Vector2f    m_position;
};


#endif


