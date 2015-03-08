/*
 * CClient.h
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


#ifndef CCLIENT_H
#define CCLIENT_H


#include <array>
#include <string>
#include <iostream>

#include <common/SFML.h>
#include <common/CWorldMap.h>
#include <client/CRenderWindow.h>
#include <client/CController.h>


#define PERIOD      20


class CClient
{
    public :
        CClient();
        ~CClient();

        void    loopGame();

    private :
        void    connectServer();
        void    loopSocket();
        void    getEvent();

        int             m_id;
        bool            m_running;
        CWorldMap       m_worldMap;
        CRenderWindow   m_window;
        sf::Thread      m_threadLoopSocket;
        sf::UdpSocket   m_socket;
};


#endif


