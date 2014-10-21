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

# Folders
DIR_BIN=bin/
DIR_HEADER=header/
DIR_SRC=src/
DIR_SRV=server/
DIR_CLT=client/
DIR_CMN=common/

# Files
SERVER=server
CLIENT=client
SRV=server
CLT=client
CMN=
SRVOBJ=${addsuffix ".o", ${SRV}}
# l'affectation ":=" indique à make de créer la variable avant d'y accéder
# En fait make ne créé les variables qu'à leur utilisation dans le code
# Il refuse donc de créer une variable qui dépend d'elle-même puisqu'elle n'a pas été créée
# Donc avec ":=" on force make à créer la variable, avant de la rédéfinir à partir d'elle-même
SRVOBJ:=${addprefix ${DIR_SRC}${DIR_SRV}, ${SRVOBJ}}
CLTOBJ=${addsuffix ".o", ${CLT}}
CLTOBJ:=${addprefix ${DIR_SRC}${DIR_CLT}, ${CLTOBJ}}
CMNOBJ=${addsuffix ".o", ${CMN}}
CMNOBJ:=${addprefix ${DIR_SRC}${DIR_CMN}, ${CMNOBJ}}

all: ${TARGET}

${TARGET}: main.o
	@echo "** Building the game **"
	${CC} -o ${TARGET} $^ ${SFML}

# Je propose d'enlever cette règle, ou d'en faire une qui fabrique le serveur et le client (la règle all quoi)
main.o: main.cpp
	@echo "** Building $@ **"
	${CC} -c ${CPPFLAGS} -o $@ $<

${SERVER}: ${SRVOBJ} ${CMNOBJ}
	@echo "** Making ${DIR_BIN}${SERVER} **"
	${CC} -o ${DIR_BIN}${SERVER} $^ ${SFML} ${BOX2D}

${CLIENT}: ${CLTOBJ} ${CMNOBJ}
	@echo "** Making ${DIR_BIN}${CLIENT} **"
	${CC} -o ${DIR_BIN}${CLIENT} $^ ${SFML}

# Cette règle implique que chaque fichier .cpp possède son .hpp correspondant, sinon il sera ignoré
# Par contre l'avantage est que si un fichier hpp est modifié, le fichier cpp sera recompilé
# Cette règle permet aussi de ne recompiler que les fichiers qui ont été modifiés (gros gain de temps !)
# Il faut corriger cette règle car elle ne prend pas en compte les dossiers (genre src/server/server.cpp)
# Je (Romain) m'en occupe il faut juste que je retrouve la syntaxe exacte (je l'ai noté quelque part et j'avais mis plusieurs heures à la trouver... à l'époque...)
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
