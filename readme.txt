How to get DriftEngine working:
-------------------------------
1) Enter these linux commands :
	sudo apt-get update
	sudo apt-get install cmake
	sudo apt-get install libglfw3
	sudo apt-get install libglfw3-dev

2) Clone this repository wherever you want on your machine :
	git clone https://github.com/apolloLemon/driftEngin
or download Release Version https://github.com/apolloLemon/driftEngin/releases and unzip

3) Download and move last assimp version :
	wget https://github.com/assimp/assimp/archive/v5.0.1.zip
	unzip assimp-5.0.1.zip
	mv assimp-5.0.1/ driftEngin/ENG/includes/assimp/

4) Compile the project :
	cp driftEngin/GameName/CMakeLists.txt driftEngin/cmake/
	cd driftEngin/cmake/
	cmake .
	make

5) Execute the game :
	./gamename.exe


Informations about cmake
------------------------
Each game has its own CMakeLists.txt
When you want to compile a game, just copy the gamename/CMakeLists.txt into the cmake/ folder, then compile with 'cmake .' and 'make'