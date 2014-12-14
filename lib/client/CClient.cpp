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
m_pirate(0, 0),
m_map(),
m_window(sf::VideoMode(windowWidth, windowHeight), name),
m_threadLoopSocket(&CClient::loopSocket, this),
m_mutex(),
m_socket()
{
    m_window.setFramerateLimit(60);

    m_threadLoopSocket.launch();
}

CClient::~CClient()
{
    m_running = false;
    m_threadLoopSocket.wait();
}

void CClient::loopSocket()
{
    sf::TcpSocket   tcpSocket;
    sf::Packet      packet;
    sf::IpAddress   ipServer = SERVER_IP;
    unsigned short  portServer = SERVER_PORT;
    std::string     sPacketData;

    if (tcpSocket.connect(ipServer, SERVER_PORT) == sf::Socket::Done)
    {
        int port;
        tcpSocket.receive(packet);
        packet >> m_idClient >> port;
        m_socket.bind(port);
        tcpSocket.disconnect();
        for (int i = 0; i < m_idClient; i++)
            m_worldMap.addPlayer(std::string("Player ") + std::to_string(i), 0, 0);
        m_worldMap.addPlayer(m_name, 0, 0);
    }

    while (m_running)
    {
        packet.clear();
        if (m_socket.receive(packet, ipServer, portServer) == sf::Socket::Done)
        {
            packet >> sPacketData;
            m_mutex.lock();
            m_worldMap.update(sPacketData);
            m_mutex.unlock();
        }

        sf::sleep(sf::milliseconds(50));
    }
}

void CClient::loopGame()
{
    sf::Packet      packet;
    sf::IpAddress   ipServer = SERVER_IP;
    unsigned short  portServer = SERVER_PORT;

    while (m_running)
    {
        update();
        m_mutex.lock();
        m_worldMap.update(m_sUpdate);
        m_mutex.unlock();
        render();

        packet.clear();
        packet << m_sUpdate;
        m_socket.send(packet, ipServer, portServer);
        m_sUpdate.clear();

        if (!m_window.isOpen())
            m_running = false;

        sf::sleep(sf::milliseconds(50));
    }
}

void CClient::update()
{
    sf::Event   event;
    m_sUpdate = std::to_string(NWorldMap::PLAYER) + std::to_string(m_idClient);
    static int  i = 0;

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
                m_sUpdate += std::to_string(NPlayer::DIRECTION);
                if(event.key.code == sf::Keyboard::Up)
                    i += NPlayer::UP;
                else if(event.key.code == sf::Keyboard::Right)
                    i += NPlayer::RIGHT;
                else if(event.key.code == sf::Keyboard::Down)
                    i += NPlayer::DOWN;
                else if(event.key.code == sf::Keyboard::Left)
                    i += NPlayer::LEFT;
                m_sUpdate += std::to_string(i);
                break;
            }
            case sf::Event::KeyReleased :
            {
                m_sUpdate += std::to_string(NPlayer::DIRECTION);
                if(event.key.code == sf::Keyboard::Right)
                    i -= NPlayer::UP;
                else if(event.key.code == sf::Keyboard::Left)
                    i -= NPlayer::RIGHT;
                else if(event.key.code == sf::Keyboard::Up)
                    i -= NPlayer::DOWN;
                else if(event.key.code == sf::Keyboard::Down)
                    i -= NPlayer::LEFT;
                m_sUpdate += std::to_string(i);
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
    m_pirate.render(m_window);
    m_window.display();
}


