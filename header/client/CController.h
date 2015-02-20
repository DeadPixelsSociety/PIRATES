#ifndef CCONTROLLER_H
#define CCONTROLLER_H


#include <common/SFML.h>
#include <client/CRenderWindow.h>


class CController
{
    public :
        CController(sf::Input& input);
        ~CController();

        void    getEvent
        void    process

    private :
        sf::Input*  m_input;
}


#endif


