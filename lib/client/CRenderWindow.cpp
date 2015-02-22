#include <client/CRenderWindow.h>
#include <client/CRenderPlayer.h>


CRenderWindow::CRenderWindow(std::string name) :
sf::RenderWindow(sf::VideoMode(800, 600), name),
m_vTextures(),
m_vRenders()
{
    setFramerateLimit(30);
    m_vTextures.push_back(new sf::Texture());
    m_vTextures.back()->loadFromFile("../asset/image/violet.png");
}

CRenderWindow::~CRenderWindow()
{
    for (std::vector<CRender*>::iterator it = m_vRenders.begin(); it != m_vRenders.end(); it++)
        delete (*it);

    for (std::vector<sf::Texture*>::iterator it = m_vTextures.begin(); it != m_vTextures.end(); it++)
        delete (*it);
}

void    CRenderWindow::update(CWorldMap& in)
{
    if (in.getVObjects().size() > m_vRenders.size())
    {
        m_vRenders.push_back(new CRenderPlayer(m_vTextures.back(), (CPlayer*)in.getVObjects().back()));
        std::cout << "Création dun render player\n";
    }

    for (std::vector<CRender*>::iterator it = m_vRenders.begin(); it != m_vRenders.end(); it++)
        (*it)->update();
}

void    CRenderWindow::render()
{
    clear(sf::Color::White);
    for (std::vector<CRender*>::iterator it = m_vRenders.begin(); it != m_vRenders.end(); it++)
        (*it)->render(this);
    display();
}

