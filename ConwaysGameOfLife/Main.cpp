#include "Game.h"

int main()
{
	GameOfLife demo;
	if (demo.Construct({ 1280, 720 }, Engine::FullscreenMode::WINDOWED, Engine::RefreshRate::VSYNC))
		demo.Start();
}
