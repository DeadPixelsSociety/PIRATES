#ifndef CRENDERWINDOW_H
#define CRENDERWINDOW_H


#include <vector>

#include <common/SFML.h>
#include <common/CWorldMap.h>
#include <client/CRender.h>


class CRender;


class CRenderWindow : public sf::RenderWindow
{
    public :
                CRenderWindow(std::string name);
                ~CRenderWindow();

        void    update(CWorldMap& in);
        void    render();

    private :
        std::vector<sf::Texture*>   m_vTextures;
        std::vector<CRender*>       m_vRenders;
};

#endif


