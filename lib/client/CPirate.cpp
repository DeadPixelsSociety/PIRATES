/*
 * CClientPirate.cpp
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

#include <client/CPirate.h>


CPirate::CPirate(int x, int y)
{
	if(!tPirate.loadFromFile("../asset/image/violet.png"))
	{
		//Affichage du message d'erreur et passage a la ligne
		std::cout<<"Erreur"<< std::endl;
		exit(1);
	}
	spPirate.setTexture(tPirate);
	spPirate.setPosition(x, y);
}

CPirate::~CPirate()
{

}

void CPirate::update(sf::Vector2<int> in)
{
    spPirate.setPosition(in.x, in.y);
}

void CPirate::render(sf::RenderWindow& window)
{
    window.draw(spPirate);
}


