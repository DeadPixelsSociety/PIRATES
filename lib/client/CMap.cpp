/*
 * CMap.cpp
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

#include <client/CMap.h>

CMap::CMap ()
{
	if(!tMapEau.loadFromFile("../asset/image/eau.jpg"))
	{
		//Affichage du message d'erreur et passage a la ligne
		std::cout<<"Erreur"<< std::endl;
		exit(1);
	}
	spMapEau.setTexture(tMapEau);
	spMapEau.setPosition(0,0);
	spMapEau.setScale(3.3f, 3.3f);

	if(!tMapSable.loadFromFile("../asset/image/sable.jpg"))
	{
		//Affichage du message d'erreur et passage a la ligne
		std::cout<<"Erreur"<< std::endl;
		exit(1);
	}
	spMapSable.setTexture(tMapSable);
	spMapSable.setScale(1.5f, 1.5f);
	spMapSable.setPosition(50,50);
}

CMap::~CMap(void)
{

};

void CMap::render (sf::RenderWindow& window)
{
	window.draw(spMapEau);
	window.draw(spMapSable);
}
