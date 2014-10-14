# Makefile
#
# Copyright 2014 PIRATES
# http://dps.univ-fcomte.fr/projects/pirates.html
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
# MA 02110-1301, USA.
#
# 

CC=g++
CPPFLAGS=-Wall -Wextra -pedantic -Wpointer -arith -Wcast-qual -Wcast-align -O2 -s
SFML= -lsfml-graphics -lsfml-window -lsfml-system
TARGET=GameName

all: ${TARGET}

${TARGET}: main.o
	@echo "** Building the game **"
	${CC} -o ${TARGET} $^ ${SFML}

main.o: main.cpp
	@echo "** Building $@ **"
	${CC} -c ${CPPFLAGS} -o $@ $<

%.o: %.cpp %.hpp
	@echo "** Building $@ **"
	${CC} -c ${CPPFLAGS} -o $@ $<

clean:
	@echo "** Removing object files and executable... **"
	rm -f *.o *.gch

mrproper: clean
	rm -f ${TARGET}

install:
	@echo "** Installing... **"
	cp ${TARGET} /usr/bin/

uninstall:
	@echo "** Uninstalling... **"
	$(RM) /usr/bin/${TARGET}
