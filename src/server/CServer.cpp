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
 
#include "header.h"

CServer::CServer()
{
};

CServer::~CServer(void)
{
	
};

void CServer::initialize() 
{
	//Init map
	//init player
	
	//Init network
	if (m_socket.bind(m_port) != sf::Socket::Done)
	{
		std::cout << "Erreur de création du socket" << std::endl;
		std::exit(1);
	}
}

void CServer::run() 
{
	//Put that shit on a thread
	receivedData();
		
		
	update();
		
	//Put that shit on a thread
	sendData();
}

void CServer::update() 
{
	std::cout << "right"  	<< m_inputs[0] << std::endl;
	std::cout << "left"  	<< m_inputs[1] << std::endl;
	std::cout << "up" 		<< m_inputs[2] << std::endl;
	std::cout << "down" 	<< m_inputs[3] << std::endl;
}

void CServer::sendData() 
{
	for(int nInput = 0; nInput < 4; ++nInput)
	{
		m_packet << m_inputs[nInput];
	}
	
	if (m_socket.send(m_packet, m_serverIp, m_port) != sf::Socket::Done)
	{
		// error...
	}
}

void CServer::receivedData() 
{
	for(int nInput = 0; nInput < 4; ++nInput)
	{
		m_packet << m_inputs[nInput];
	}
	
	if (m_socket.send(m_packet, m_serverIp, m_port) != sf::Socket::Done)
	{
		// error...
	}
}
