#include <iostream>
#include<cstdlib>
#include<ctime>
#include<iostream>
#include<time.h>
#include "Game.h"
#include <windows.h> 

using namespace std;
//int main() //Dlya Debuga
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) //Dlya Releasa  
{ 
	srand(static_cast<unsigned>(time(0)));
	Game game;

	while (game.getWindow().isOpen())
	{
		game.update();
		game.render();
	}


	return 0;
}