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

CClient::CClient(int windowWidth, int windowHeight, sf::String name)
: m_window(sf::VideoMode(windowWidth, windowHeight), "PIRATES!")
, m_player()
, m_map()
{
	m_window.setFramerateLimit(60);
	initialize();
};

CClient::~CClient(void)
{
	exitGame();
};

void CClient::initialize() 
{
	// Init map
	// Init player
	
	// Init network
	if (m_socket.bind(m_port) != sf::Socket::Done)
	{
		std::cout << "Erreur de création du socket" << std::endl;
		std::exit(1);
	}
	
	// Lock the network communication thread
	m_networkThread = new sf::Thread(sendData);
	m_serverCommunication.lock();
}

void CClient::run() 
{
	while (m_window.isOpen())
	{
		processEvents();
		update();
		render();
		
		// Allow the network thread to send an update
		m_serverCommunication.unlock();
	}
}

void CClient::exitGame()
{
	// TODO fermer les sockets, les threads et tout le bazar
	delete m_networkThread;
}

void CClient::processEvents() 
{
	sf::Event event;
	while (m_window.pollEvent(event)) //Gestion des evvenements
	{
		switch(event.type)
		{
			//fermeture de la fenetre lorsque l'utilisateur le souhaite.
			case sf::Event::Closed:
			{
				m_window.close();
			}
			break;
			case sf::Event::KeyPressed:
			{
				//Si on appuie sur les fleches
				if(event.key.code == sf::Keyboard::Right)
				{
					m_inputs[0] = true;
				}
				else if(event.key.code == sf::Keyboard::Left)
				{
					m_inputs[1] = true;
				}
				else if(event.key.code == sf::Keyboard::Up)
				{
					m_inputs[2] = true;
				}
				else if(event.key.code == sf::Keyboard::Down)
				{
					m_inputs[3] = true;
				}

			}
			break;
			case sf::Event::KeyReleased:
			{
				//Si on relache les fleches
				if(event.key.code == sf::Keyboard::Right)
				{
					m_inputs[0] = false;
				}
				else if(event.key.code == sf::Keyboard::Left)
				{
					m_inputs[1] = false;
				}
				else if(event.key.code == sf::Keyboard::Up)
				{
					m_inputs[2] = false;
				}
				else if(event.key.code == sf::Keyboard::Down)
				{
					m_inputs[3] = false;
				}
			}
			break;
			default :
			{
			}
			break;
		}
	}
}

void CClient::update() 
{
	std::cout << "right"  	<< m_inputs[0] << std::endl;
	std::cout << "left"  	<< m_inputs[1] << std::endl;
	std::cout << "up" 		<< m_inputs[2] << std::endl;
	std::cout << "down" 	<< m_inputs[3] << std::endl;
}

void CClient::sendData() 
{
	m_packet.clear();
	for(int nInput = 0; nInput < 4; ++nInput)
	{
		m_packet << m_inputs[nInput];
	}
	
	m_socket::Status request = m_socket.send(m_packet, m_serverIp, m_port);
	
	if (request == m_socket::Status::Error)
	{
		cerr << "An error occurred during the communication with the server." << endl;
		exitGame();
	}
	else if	(request == m_socket::Status::Disconnected)
	{
		cerr << "You have been disconnected from the host." << endl;
		exitGame();
	}
}

void CClient::render() 
{
	m_window.clear(sf::Color::White);
	m_map.render(m_window);
	m_player.render(m_window);
	m_window.display();
}
