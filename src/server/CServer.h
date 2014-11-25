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
 
#ifndef _CSERVER_H
#define _CSERVER_H


#include "SFML.h"
#include "CWorldMap.h"
#include "CWorldBox.h"


class CServer
{
  public :
          CServer(int nbMaxPlayer);
          ~CServer();
          
  	void  LoopSocket();
  	void  LoopGame();
  	
  	
  private :
    sf::Thread    m_threadLoopSocket; // Thread gérant la partie réseau
    sf::Thread    m_threadLoopGame;   // Thread gérant la partie physique
  
  	CWorldMap     m_worldMap; // Carte des élements dynamiques et de leurs états
  	CWorldBox     m_worldBox; // Univers physique Box2D
  	
  	sf::Clock     m_clock;
  	
  	std::list<sf::UdpSocket*> m_lSocket;
  	sf::SocketSelector        m_socketSelector;
  	
  	bool  m_running;
};

#endif  //_CSERVER_H
