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
 
#ifndef __CCLIENT_H
#define __CCLIENT_H


class CServer {
	public:	
		explicit       		CServer (void);
		virtual        		~CServer (void);
		void 				initialize ();
		void 				run	();

	private:
		void				update ();
		void				sendData ();
		void				receivedData ();
		
		std::array<bool, 4>			m_inputs;
		sf::UdpSocket 				m_socket;
		sf::IpAddress 				m_serverIp 	= "127.0.0.1";
		sf::Packet 					m_packet;
		int							m_port 		= 56747;
};

#endif  //__CCLIENT_H
