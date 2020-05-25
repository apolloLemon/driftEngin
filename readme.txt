How to get DriftEngine working:
-------------------------------
1) Enter these linux commands :
	sudo apt-get update
	sudo apt-get install cmake
	sudo apt-get install libglfw3
	sudo apt-get install libglfw3-dev

2) Clone this repository wherever you want on your machine :
	git clone https://github.com/apolloLemon/driftEngin

3) Download and move last assimp version :
	wget https://github.com/assimp/assimp/archive/v5.0.1.zip
	unzip assimp-5.0.1.zip
	mv assimp-5.0.1/ driftEngin/ENG/includes/assimp/

4) Compile the project :
	cd driftEngin/cmake/
	cmake .
	make

5) Execute the game :
	./gamename.exe


Informations about cmake
------------------------
The compiled game is selected in the cmake, you have to add your gameobjects source files to the CMakeLists.txt
You can add them after "# gameobjects" at Line 14, don't forget to replace the old game's ones.