//
//  @ Project : PIRATES
//  @ File Name : CWorldBox.cpp
//  @ Date : 20/5/2014
//  @ Author : Romain
//


#include <server/CWorldBox.h>



CWorldBox::CWorldBox(const std::string& tmxFile) :
m_map(tmxFile),
m_world(b2Vec2(0.f, 0.f))
{
    for (auto layer : m_map.getLayers())
    {
        if (!layer->getProperties().empty()
        && layer->getProperties().find("collision") != layer->getProperties().end())
        {
            unsigned int i = 0;
            for (auto tile : layer->getData())
            {
                if (tile.getId() != 0)
                {
                    b2BodyDef bodyDef;
                    int x = i % m_map.getWidth();
                    int y = i / m_map.getWidth();
                    bodyDef.position.Set((x + 0.5f) * m_map.getTilewidth() / SCALING, (y + 0.5f) * m_map.getTileheight() / SCALING);
                    bodyDef.type = b2_staticBody;
                    b2Body* body = m_world.CreateBody(&bodyDef);
                    b2PolygonShape shape;
                    shape.SetAsBox(m_map.getTilewidth() / 2.f / SCALING, m_map.getTileheight() / 2.f / SCALING);
                    b2FixtureDef fixtureDef;
                    fixtureDef.density = 1.f;
                    fixtureDef.friction = 0.7f;
                    fixtureDef.shape = &shape;
                    body->CreateFixture(&fixtureDef);
                }
                i++;
            }
        }
    }
}

CWorldBox::~CWorldBox()
{

}

CMapQuery  CWorldBox::update(std::vector<CMapObject*>& vObjects, sf::Time elapsed)
{
    m_mapQuery.clear();
    m_elapsed = elapsed;
    m_world.Step(1/60.f, 8, 3);

    for (auto object : vObjects)
    {
        if (m_mBodyObjects.find(object->getId()) == m_mBodyObjects.end())
        {
            b2BodyDef bodyDef;
            bodyDef.position.Set((((CPlayer*)object)->getPosition().x + 32/2) / SCALING, (((CPlayer*)object)->getPosition().y + 65/2) / SCALING);
            bodyDef.type = b2_dynamicBody;
            m_mBodyObjects[object->getId()] = m_world.CreateBody(&bodyDef);
            b2PolygonShape shape;
            shape.SetAsBox(32 / 2.f / SCALING, 65 / 2.f / SCALING);
            b2FixtureDef fixtureDef;
            fixtureDef.density = 1.f;
            fixtureDef.friction = 0.7f;
            fixtureDef.shape = &shape;
            m_mBodyObjects[object->getId()]->CreateFixture(&fixtureDef);
        }
        update((CPlayer*)object);
    }

    return m_mapQuery;
}

void    CWorldBox::update(CPlayer* player)
{
        b2Vec2 vel = m_mBodyObjects[player->getId()]->GetLinearVelocity();
        switch(player->getState(NPlayer::Direction))
        {
            case NPlayer::Up :          vel.y = -10;             break;
            case NPlayer::Right :       vel.x = 10;              break;
            case NPlayer::Down :        vel.y = 10;              break;
            case NPlayer::Left :        vel.x = -10;             break;
            case NPlayer::UpRight :     vel.y = -10; vel.x = 10;  break;
            case NPlayer::RightDown :   vel.x = 10; vel.y = 10;   break;
            case NPlayer::DownLeft :    vel.y = 10; vel.x = -10;  break;
            case NPlayer::LeftUp :      vel.x = -10; vel.y = -10; break;
            default :                   vel.x = 0; vel.y = 0;   break;
        }
        m_mBodyObjects[player->getId()]->SetLinearVelocity(vel);
        player->setState(NPlayer::Direction, 0);
        player->setPosX(m_mBodyObjects[player->getId()]->GetPosition().x * SCALING);
        player->setPosY(m_mBodyObjects[player->getId()]->GetPosition().y * SCALING);
        m_mapQuery << NWorldMap::Update << player->getId() << NPlayer::Position << player->getPosition();
}


