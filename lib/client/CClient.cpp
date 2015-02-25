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


CClient::CClient(std::string name) :
m_name(name),
m_id(),
m_running(true),
m_mapQuery(),
m_worldMap(),
m_window(m_name),
m_threadLoopSocket(&CClient::loopSocket, this),
m_socket(),
m_ipServer(SERVER_IP),
m_portServer(SERVER_PORT)
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
    CMapQuery       mapQuery;

    if (tcpSocket.connect(m_ipServer, m_portServer) == sf::Socket::Done
        && tcpSocket.receive(mapQuery) == sf::Socket::Done)
    {
        mapQuery >> m_portServer >> m_id;
        m_socket.bind(sf::Socket::AnyPort);

        mapQuery.clear();
        mapQuery << m_socket.getLocalPort();
        tcpSocket.send(mapQuery);

        mapQuery.clear();
        tcpSocket.receive(mapQuery);
        m_worldMap.update(mapQuery);

        mapQuery.clear();
        m_socket.receive(mapQuery, m_ipServer, m_portServer);
        m_worldMap.update(mapQuery);
    }
}

void CClient::loopSocket()
{
    CMapQuery       mapQuery;
    sf::IpAddress   ipServer = m_ipServer;
    unsigned short  portServer = m_portServer;

    while (m_running)
    {
        mapQuery.clear();
        if (m_socket.receive(mapQuery, ipServer, portServer) == sf::Socket::Done)
        {
            m_worldMap.update(mapQuery);
            m_window.update(m_worldMap.getVObjects());
        }
    }
}

void CClient::loopGame()
{
    while (m_running)
    {
        getEvent();
        if (!m_window.isOpen())
            m_running = false;

        m_mapQuery.clear();
        m_mapQuery << NWorldMap::Update << m_id;
        CController::getInput(m_mapQuery);

        m_socket.send(m_mapQuery, m_ipServer, m_portServer);

        m_window.render();
        sf::sleep(sf::milliseconds(20));
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


