#include <client/CRenderWindow.h>
#include <client/CRenderPlayer.h>


CRenderWindow::CRenderWindow(std::string name) :
sf::RenderWindow(sf::VideoMode(800, 600), name),
m_tileMap("../asset/maps/map.tmx"),
m_vTextures(),
m_mRenders()
{
    setFramerateLimit(60);
    m_vTextures.push_back(new sf::Texture());
    m_vTextures.back()->loadFromFile("../asset/images/violet.png");
}

CRenderWindow::~CRenderWindow()
{
    for (std::map<int, CRender*>::iterator it = m_mRenders.begin(); it != m_mRenders.end(); it++)
        delete it->second;

    for (std::vector<sf::Texture*>::iterator it = m_vTextures.begin(); it != m_vTextures.end(); it++)
        delete (*it);
}

void    CRenderWindow::update(std::vector<CMapObject*>& vObjects)
{
    for (std::vector<CMapObject*>::iterator it = vObjects.begin(); it != vObjects.end(); it++)
    {
        if (m_mRenders.find((*it)->id()) == m_mRenders.end())
            m_mRenders[(*it)->id()] = new CRenderPlayer(m_vTextures.back(), (CPlayer*)(*it));
    }

    for (std::map<int, CRender*>::iterator it = m_mRenders.begin(); it != m_mRenders.end(); it++)
        it->second->update();
}

void    CRenderWindow::render()
{
    clear(sf::Color::White);
    draw(m_tileMap);
    for (std::map<int, CRender*>::iterator it = m_mRenders.begin(); it != m_mRenders.end(); it++)
        it->second->render(this);
    display();
}

