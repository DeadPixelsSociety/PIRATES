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
CPPFLAGS=-Wall -std=c++11
SFML= -lsfml-graphics -lsfml-window -lsfml-system
BOX2D=

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

# Insérer ici la liste des fichiers à compiler sans extension
SRV=server
CLT=client
CMN=

SRVOBJ=${addsuffix .o, ${SRV}}
# l'affectation ":=" indique à make de créer la variable avant d'y accéder
# En fait make ne créé les variables qu'à leur utilisation dans le code
# Il refuse donc de créer une variable qui dépend d'elle-même puisqu'elle n'a pas été créée
# Donc avec ":=" on force make à créer la variable, avant de la rédéfinir à partir d'elle-même
SRVOBJ:=$(addprefix ${DIR_SRC}${DIR_SRV}, ${SRVOBJ})
CLTOBJ=$(addsuffix .o, ${CLT})
CLTOBJ:=$(addprefix ${DIR_SRC}${DIR_CLT}, ${CLTOBJ})
CMNOBJ=$(addsuffix .o, ${CMN})
CMNOBJ:=$(addprefix ${DIR_SRC}${DIR_CMN}, ${CMNOBJ})

all: ${SERVER} ${CLIENT}

${SERVER}: ${SRVOBJ} ${CMNOBJ}
	@echo "** Making ${DIR_BIN}${DIR_SRV}${SERVER} **"
	${CC} -o ${DIR_BIN}${DIR_SRV}${SERVER} $^ ${SFML} ${BOX2D}

${CLIENT}: ${CLTOBJ} ${CMNOBJ}
	@echo "** Making ${DIR_BIN}${DIR_CLT}${CLIENT} **"
	${CC} -o ${DIR_BIN}${DIR_CLT}${CLIENT} $^ ${SFML}

${DIR_SRC}${DIR_SRV}%.o: ${DIR_SRC}${DIR_SRV}%.cpp
	@echo "** Building $@ **"
	${CC} -c ${CPPFLAGS} -o $@ $<
	
${DIR_SRC}${DIR_CLT}%.o: ${DIR_SRC}${DIR_CLT}%.cpp
	@echo "** Building $@ **"
	${CC} -c ${CPPFLAGS} -o $@ $<
	
${DIR_SRC}${DIR_CMN}%.o: ${DIR_SRC}${DIR_CMN}%.cpp
	@echo "** Building $@ **"
	${CC} -c ${CPPFLAGS} -o $@ $<

clean:
	@echo "** Removing object files and executable... **"
	rm -f ${DIR_SRC}${DIR_SRV}*.o ${DIR_SRC}${DIR_CLT}*.o ${DIR_SRC}${DIR_CMN}*.o 

mrproper: clean
	rm -f ${DIR_BIN}${DIR_SRV}${SERVER} ${DIR_BIN}${DIR_CLT}${CLIENT}

install:
	@echo "** Installing... **"
	cp ${TARGET} /usr/bin/

uninstall:
	@echo "** Uninstalling... **"
	$(RM) /usr/bin/${TARGET}
