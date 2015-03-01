PIRATES
=======

PIRATES is a open source multiplayer game. You are on an island, looking for all the treasures that you'll need to win the pirates' competition of the year!  
In that way, a lot of competitors are fighting to be the first pirate of the year. Run fast and take care of the trees, we don't know whatever is behind them...

To win, you have to be the first to get all the treasures and come back to your ship.

Developper install
------------------

1. clone the PIRATES repository :
    git clone http://github.com/DeadPixelsSociety/PIRATES.git

2. Install SFML packages from your OS (apt-get, pacman, or download from http://www.sfml-dev.org)

3. Install Box2D library :
    - Download the archive (outside the git folder) :
        wget http://box2d.googlecode.com/files/Box2D_v2.3.0.7z
    - Extract with 7z (download it... :p) :
        7z x Box2d_v2.3.0.7z -o box2d
    - Configure with cmake
        cmake .
        cmake --help (check the bottom list if you use an IDE)
    - Build the library
        make
    - Installing on your computer
        make install
    - copy the PIRATES/doc/box2d.pc to /usr/lib/pkgconfig/
        cd PIRATES/
        cp pkg-config/box2d.pc /usr/lib/pkgconfig/

4. install TMXLib :
    - Download and install boost library
    - copy the pkgconfig file :
        cp pkg-config/boost.pc /usr/lib/pkgconfig/
    - Download the git repository :
        git clone http://github.com/aquemy/TMXLib
    - Build the library :
        cd TMXLib
        mkdir build
        cd build
        cmake ..
        make
    - Install in your system
        make install
    - copy the pkgconfig file :
        cp pkg-config/libtmx.pc /usr/lib/pkgconfig/

5. install Thor library :
    - git clone http://github.com/Bromeon/Thor
    - cp pkg-config/thor.pc /usr/lib/pkgconfig/
    - cd Thor; make . ; make; make install
    If you have a problem a the execution of client, you have to do this :
        echo "/usr/local/lib" > /etc/ld.so.conf.d/locale.conf; ldconfig
    If -ltmx not found, you have to :
        ln -s /usr/local/lib32(ou 64)/libtmx.a /usr/local/lib

5. Configure
    - mkdir build; cd build
    - use cmake with your IDE type as argument
        cmake .. -G "Unix Makefiles"
        /!\ it's `cmake ..` not `cmake .` don't compile in the root directory for keep a clean repository
    - if you have pkgconfig error, then you have not install correctly libraries

6. Compile
    - make server or make client or just make for both
    - make doc to build a html and latex doxygen documentation of the project :)


Install
-------

Go to the game's folder and type:

### Windows ###

    // Nothing to do with a Windows install...
    
### Linux ###

    // Not implemented yet
Enjoy !


Documentation
-------------

PIRATES is made by a team of [Dead Pixel Society](http://dps.univ-fcomte.fr/projects/pirates.html).


License
-------

PIRATES is under the LGPL license. See the LICENSE file to learn more about it.
