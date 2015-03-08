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


sf::IpAddress   serverIp = "127.0.0.1";
unsigned short  tcpPort = 56747;
unsigned short  udpPort = 56666;


CClient::CClient(std::string name) :
m_running(true),
m_window("PIRATES"),
m_threadLoopSocket(&CClient::loopSocket, this)
{
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
    CQuery          query;

    if (tcpSocket.connect(serverIp, tcpPort) == sf::Socket::Done
        && tcpSocket.receive(query) == sf::Socket::Done)
    {
        query >> m_id;
        m_socket.bind(udpPort);

        query.clear();
        tcpSocket.receive(query);
        m_worldMap.update(query);

        query.clear();
        m_socket.receive(query, serverIp, udpPort);
        m_worldMap.update(query);
    }
}

void CClient::loopSocket()
{
    CQuery       query;

    while (m_running)
    {
        query.clear();
        if (m_socket.receive(query, serverIp, udpPort) == sf::Socket::Done)
        {
            m_worldMap.update(query);
            m_window.update(m_worldMap.getVObjects());
        }
    }
}

void CClient::loopGame()
{
    CQuery      query;
    sf::Clock   phase;

    while (m_running)
    {
        getEvent();
        if (!m_window.isOpen())
            m_running = false;
        query.clear();
        query << NWorldMap::Update << m_id;
        CController::getInput(query);
        m_socket.send(query, serverIp, udpPort);
        m_worldMap.update(query);
        m_window.render();
        sf::sleep(sf::milliseconds(PERIOD) - phase.restart());
    }
}

void    CClient::getEvent()
{
    sf::Event   event;

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
                switch(event.key.code)
                {
                    case sf::Keyboard::Escape :
                        m_running = false;
                        break;
                    default :
                        break;
                }
                break;
            }
            case sf::Event::Resized :
                m_window.setView(sf::View(sf::FloatRect(0, 0, event.size.width, event.size.height)));
                break;
            default :
                break;
        }
    }
}


