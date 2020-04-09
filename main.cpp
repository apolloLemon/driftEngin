#include "phyx.h"

#include <iostream>
#include <SDL2/SDL.h>

#include <thread>
#include <chrono>
using namespace std::literals::chrono_literals; //for sleep_for(0.01s)

int main(){
	SDL_Event event;
	
	PhyxObj2D p; //point
	p.X(0);p.Y(300); //start pos
	p.XV(0);p.YV(0); //start velocity u/s
	p.XA(0);p.YA(0); //acceleration u2/s
	p.InitTime();


	while(1){
		std::cout	<<"x: "<<p.X()
					<<", y: "<<p.Y()
					<<",\tspeed: "<<p.V()
					<<std::endl;

	
	while( SDL_PollEvent( &event ) ){
		/* We are only worried about SDL_KEYDOWN and SDL_KEYUP events */
		switch( event.type ){
			case SDL_KEYDOWN:
				printf( "Key press detected\n" );
				p.YV(1);
				break;

			case SDL_KEYUP:
				printf( "Key release detected\n" );
				p.YV(0);
				break;

			default:break;
		}
	}



		p.Update();
		std::this_thread::sleep_for(0.1s);
	}

	return 0;
}