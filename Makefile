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
SFML= -lsfml-network -lsfml-graphics -lsfml-window -lsfml-system
BOX2D= libBox2D.a libBox2D.so

# Folders
DIR_BIN=bin/
DIR_HEADER=header/
DIR_SRC=src/
DIR_SRV=server/
DIR_CLT=client/
DIR_CMN=common/
DIR_LIB=lib/

# Files output
SERVER=server
CLIENT=client

# Inserer ici la liste des fichiers a compiler sans extension
SRV=server CServer CWorldBox
CLT=client CClient CClientPirate CMap
CMN=CWorldMap CPlayer
 
SRVOBJ=${addsuffix .o, ${SRV}}
SRVOBJ:=$(addprefix ${DIR_SRC}${DIR_SRV}, ${SRVOBJ})
CLTOBJ=$(addsuffix .o, ${CLT})
CLTOBJ:=$(addprefix ${DIR_SRC}${DIR_CLT}, ${CLTOBJ})
CMNOBJ=$(addsuffix .o, ${CMN})
CMNOBJ:=$(addprefix ${DIR_SRC}${DIR_CMN}, ${CMNOBJ})
BOX2D:=${addprefix ${DIR_LIB}, ${BOX2D}}

all: ${SERVER} ${CLIENT}

${SERVER}: ${SRVOBJ} ${CMNOBJ}
	@echo "** Making ${DIR_BIN}${DIR_SRV}${SERVER} **"
	${CC} -o ${DIR_BIN}${DIR_SRV}${SERVER} $^ ${SFML} ${BOX2D}

${CLIENT}: ${CLTOBJ} ${CMNOBJ}
	@echo "** Making ${DIR_BIN}${DIR_CLT}${CLIENT} **"
	${CC} -o ${DIR_BIN}${DIR_CLT}${CLIENT} $^ ${SFML}

${DIR_SRC}${DIR_SRV}%.o: ${DIR_SRC}${DIR_SRV}%.cpp
	@echo "** Building $@ **"
	${CC} -c ${CPPFLAGS} -o $@ $< -I ${DIR_HEADER}${DIR_SRV} -I ${DIR_HEADER}${DIR_CMN}
	
${DIR_SRC}${DIR_CLT}%.o: ${DIR_SRC}${DIR_CLT}%.cpp
	@echo "** Building $@ **"
	${CC} -c ${CPPFLAGS} -o $@ $< -I ${DIR_HEADER}${DIR_CLT} -I ${DIR_HEADER}${DIR_CMN}
	
${DIR_SRC}${DIR_CMN}%.o: ${DIR_SRC}${DIR_CMN}%.cpp
	@echo "** Building $@ **"
	${CC} -c ${CPPFLAGS} -o $@ $< -I ${DIR_HEADER}${DIR_CMN}

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
