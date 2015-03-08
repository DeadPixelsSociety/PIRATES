#include <client/CRenderWindow.h>
#include <client/CRenderPlayer.h>


CRenderWindow::CRenderWindow(std::string name) :
sf::RenderWindow(sf::VideoMode(800, 600), name),
m_tileMap("../asset/maps/collision.tmx"),
m_vTextures(),
m_mRenders()
{
    setFramerateLimit(60);
    m_vTextures.push_back(new sf::Texture());
    m_vTextures.back()->loadFromFile("../asset/images/Player.png");
}

CRenderWindow::~CRenderWindow()
{
    for (auto render : m_mRenders)
        delete render.second;
    for (auto texture : m_vTextures)
        delete texture;
}

void    CRenderWindow::update(CWorldMap& mObjects)
{
    for (auto object : mObjects)
    {
        if (object.second->isVisible()
        && m_mRenders.find(object.first) == m_mRenders.end())
            m_mRenders[object.first] = new CRenderPlayer(m_vTextures.back(), (CPlayer*)(object.second));
        else if (!object.second->isVisible()
        && m_mRenders.find(object.first) != m_mRenders.end())
                m_mRenders.erase(object.first);
    }
    for (auto render : m_mRenders)
        render.second->update();
}

void    CRenderWindow::render()
{
    clear(sf::Color::White);
    draw(m_tileMap);
    for (auto render : m_mRenders)
        render.second->render(this);
    display();
}

