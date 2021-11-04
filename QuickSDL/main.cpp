/*
Michael Martinez
COP 3003
Fall 2021

The purpose of the program is to recreate the game Megaman Battle Network 6.
Current program outputs Start Screen. The battle stage will be added next.

Files used:
SDL2
QuickSDL by Ather Omar

Guides used:
Lazy Foo' Productions
Youtube - Ather Omar

Sprites used:
Megaman Battle Network 6 Cybeast Gregar

New files created:
StartScreen.h
StartScreen.cpp
*/

#include "GameManager.h"

int main(int argc, char* argv[]) {

	QuickSDL::GameManager* game = QuickSDL::GameManager::Instance();

	game->Run();

	QuickSDL::GameManager::Release();
	game = NULL;

	return 0;
}