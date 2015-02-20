#ifndef CRENDERWINDOW_H
#define CRENDERWINDOW_H


#include <vector>

#include <common/SFML.h>
#include <common/CWorldMap.h>


class CRenderWindow
{
    public :
        CRenderWindow(int width, int height, sf::String name);
        ~CRenderWindow();

        void    update(CWorldMap &in);
        void    render();

    private :
        sf::RenderWindow        m_window;
        std::vector<CRender*>   m_vRenders;
};

#endif


