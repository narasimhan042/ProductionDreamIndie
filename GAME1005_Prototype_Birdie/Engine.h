#pragma once
#include "Classes.h"
#define fps 60

class Engine
{
public:
	Engine():m_iFps(fps),m_bGotTick (false){}
	~Engine(){}

	bool init(const char*title,int xpos, int ypos, int width,int height, int flags);
	bool running();
	bool tick();
	void update();
	void render(BACKGROUND &bg);
	void handleEvents();
	void clean();
private:
	bool m_bRunning;
	bool m_bGotTick;
	SDL_Window*m_pWindow;
	SDL_Renderer*m_pRenderer;
	int m_iFps;
	SDL_Surface*m_pBackgroundSurface;
	SDL_Texture*m_pBackgroundTexture;

};

