/*
Michael Martinez
COP 3003
Fall 2021

Guides used:
Lazy Foo' Productions
Youtube - Ather Omar

Sprites used:
Megaman Battle Network 6 Cybeast Gregar
Titlescreen Background - Ethan Mercado
*/

#include "GameManager.h"

int main(int argc, char* argv[]) {

	QuickSDL::GameManager* game = QuickSDL::GameManager::Instance();

	game->Run();

	QuickSDL::GameManager::Release();
	game = NULL;

	return 0;
}