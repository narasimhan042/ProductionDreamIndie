#include "Engine.h"
#include <chrono>
using namespace chrono;

bool Engine::init(const char*title, int xpos, int ypos, int width, int height, int flags) 
{
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) 
	{
		cout << "SDL INIT SUCCESS" << endl;
		m_pWindow = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		if (m_pWindow != 0)
		{
			cout << "Window Creation Successful" << endl;
			m_pRenderer = SDL_CreateRenderer(m_pWindow,-1,0);
			if (m_pRenderer != 0)
			{
				cout << "Renderer Creation successful" << endl;
				IMG_Init(IMG_INIT_PNG);
				m_pBackgroundSurface = IMG_Load("Birdie_Background.png");
				m_pBackgroundTexture = SDL_CreateTextureFromSurface(m_pRenderer, m_pBackgroundSurface);
			}
			else
			{
				cout << "Renderer Failed" << endl;
				return false;
			}
		}
		else
		{
			cout << "WINDOW CREATION Failed" << endl;
			return false;
		}
	}
	else
	{
		cout << "SDL SYSTEMS Failed" << endl;
		return false;
	}
	cout << "Everything worked" << endl;
	m_bRunning = true;
		return true;
}

bool Engine::running()
{
	return m_bRunning;
}
bool Engine::tick()
{
	auto duration = steady_clock::now().time_since_epoch();
	auto count = duration_cast<microseconds>(duration).count();
	int tick = 1000000 / m_iFps;

	if (count % tick < 100) // Drops potential duplicate frames.
	{
		if (m_bGotTick == false)
		{
			m_bGotTick = true;
			//cout << "Tick " << tick << " @ " << count << endl;
			return true;
		}
		return false;
	}
	else m_bGotTick = false;
	return false;
}
void Engine::update()
{

}
void Engine::render(BACKGROUND &bg)
{
	SDL_RenderClear(m_pRenderer);
	SDL_RenderCopy(m_pRenderer, m_pBackgroundTexture, bg.getSource(), bg.getDes());
	//SDL_SetRenderDrawColor(m_pRenderer,0,255,0,255);
	SDL_RenderPresent(m_pRenderer);
}
void Engine::handleEvents()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			m_bRunning = false;
			break;
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym)
			{

			}
			break;
		case SDL_KEYUP:
			switch (event.key.keysym.sym)
			{

			}
			break;
		}
	}
}
void Engine::clean()
{
	SDL_DestroyRenderer(m_pRenderer);
	SDL_DestroyWindow(m_pWindow);
	IMG_Quit();
	SDL_Quit();
}