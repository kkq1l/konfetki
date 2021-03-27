#include <iostream>
#include<cstdlib>
#include<ctime>
#include<iostream>
#include<time.h>
#include "Game.h"


#include <windows.h>

using namespace std;

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	srand(static_cast<unsigned>(time(0)));
	Game game;

	while (game.getWindow().isOpen())
	{
		game.update();
		game.render();
	}


	return 0;
}