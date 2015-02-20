#include <client/CRenderWindow.h>


CRenderWindow::CRenderWindow(int width, int height, sf::String name) :
m_window(sf::VideoMode(width, height), name),
m_vTextures(),
m_vRenders()
{
    m_window.setFramerateLimit(30);
    m_vTextures.push_back(new sf::Texture());
    m_vTextures.back()->loadFromFile("../asset/image/violet.png");
    m_vRenders.push_back(new CRenderPlayer(name), m_vTextures.back());
}

CRenderWindow::~CRenderWindow()
{
    for (std::vector<CRender*>::iterator it = m_vRenders.begin(); it != m_vRenders.end(); it++)
        delete (*it);

    for (std::vector<sf::Texture*>::iterator it = m_vTextures.begin(); it != m_vTextures.end(); it++)
        delete (*it);
}

CRenderWindow::update(CWorldMap &in)
{
    for (std::vector<CRender*>::iterator it = m_vRenders.begin(); it != m_vRenders.end(); it++)
        (*it)->update(in);
}

CRenderWindow::render()
{
    window.clear(sf::Color::White);
    for (std::vector<CRender*>::iterator it = m_vRenders.begin(); it != m_vRenders.end(); it++)
        (*it)->draw(&m_window);
}

