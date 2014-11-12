/*
 * main.cpp
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

#include <Thread.hpp>
#include <Mutex.hpp>

// Inputs reception thread's function
void receiveInputs(void)
{
	
}

int main (int argc, char **argv)
{
	// Create a thread to receive inputs from the server
	sf::Thread reception(receiveInputs);
	
	// TODO Create a thread to display the game
	sf::Thread display();
	
	// Create a mutex to communicate between reception & display
	sf::Mutex inputsCommunication;
	
	reception.launch();
	display.launch();
}
