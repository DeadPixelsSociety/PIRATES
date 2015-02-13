/*
 * CClient.cpp
 *
 * Copyright 2014 PIRATES
 * http://dps.univ-fcomte.fr/projects/pirates.html
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 *
 *
 */


#include <client/CClient.h>


CClient::CClient(int windowWidth, int windowHeight, sf::String name) :
m_name(name),
m_idClient(),
m_sUpdate(),
m_running(true),
m_worldMap(),
m_pirate(50, 50),
m_map(),
m_window(sf::VideoMode(windowWidth, windowHeight), name),
m_threadLoopSocket(&CClient::loopSocket, this),
m_mutex(),
m_socket(),
m_ipServer(SERVER_IP),
m_portServer(SERVER_PORT)
{
    m_window.setFramerateLimit(60);
    connectServer();
    m_threadLoopSocket.launch();
}

CClient::~CClient()
{
    m_running = false;
}

void CClient::connectServer()
{
    sf::TcpSocket   tcpSocket;
    sf::Packet      packet;

    if (tcpSocket.connect(m_ipServer, m_portServer) == sf::Socket::Done
        && tcpSocket.receive(packet) == sf::Socket::Done)
    {
        packet >> m_portServer >> m_idClient;
        m_socket.bind(sf::Socket::AnyPort);
        packet << m_socket.getLocalPort();
        tcpSocket.send(packet);
        for (int i = 0; i < m_idClient; i++)
            m_worldMap.addPlayer(std::string("Player ") + std::to_string(i), 50, 50);
        m_worldMap.addPlayer(m_name, 50, 50);
    }
}

void CClient::loopSocket()
{
    sf::Packet      packet;
    std::string     sPacketData;
    sf::IpAddress   ipServer = m_ipServer;
    unsigned short  portServer = m_portServer;

    while (m_running)
    {
        packet.clear();
        if (m_socket.receive(packet, ipServer, portServer) == sf::Socket::Done)
        {
            sPacketData.clear();
            packet >> sPacketData;
            m_worldMap.printUpdate(sPacketData);
            m_worldMap.update(sPacketData);
        }
        sf::sleep(sf::milliseconds(50));
    }
}

void CClient::loopGame()
{
    sf::Packet      packet;

    while (m_running)
    {
        m_sUpdate.clear();
        update();

        if (m_sUpdate.length() > 2)
        {
            m_worldMap.printUpdate(m_sUpdate);
            packet.clear();
            packet << m_sUpdate;
            m_socket.send(packet, m_ipServer, m_portServer);
        }

        if (!m_window.isOpen())
            m_running = false;

        render();
        sf::sleep(sf::milliseconds(50));
    }
}

void CClient::update()
{
    sf::Event   event;
    m_sUpdate += NWorldMap::PLAYER;
    m_sUpdate += m_idClient;

    while (m_window.pollEvent(event))
    {
        switch(event.type)
        {
            case sf::Event::Closed :
            {
                m_window.close();
                break;
            }
            case sf::Event::KeyPressed :
            {
                m_sUpdate += NPlayer::STATE;
                m_sUpdate += NPlayer::DIRECTION;
                switch(event.key.code)
                {
                    case sf::Keyboard::Up :
                        m_sUpdate += NPlayer::UP;
                        break;
                    case sf::Keyboard::Right :
                        m_sUpdate += NPlayer::RIGHT;
                        break;
                    case sf::Keyboard::Down :
                        m_sUpdate += NPlayer::DOWN;
                        break;
                    case sf::Keyboard::Left :
                        m_sUpdate += NPlayer::LEFT;
                        break;
                    case sf::Keyboard::Escape :
                        m_running = false;
                        break;
                    default :
                        break;
                }
                break;
            }
            default :
                break;
        }
    }
}

void CClient::render()
{
    m_window.clear(sf::Color::White);
    m_map.render(m_window);
    m_pirate.update(m_worldMap.m_vPlayers[0]->getPos());
    m_pirate.render(m_window);
    m_window.display();
}


