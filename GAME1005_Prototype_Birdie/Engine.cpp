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
				m_pBirdSurface = IMG_Load("Bird.png");
				m_pBirdTexture = SDL_CreateTextureFromSurface(m_pRenderer, m_pBirdSurface);
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
void Engine::update(Player &p)
{
	if (m_bUp == true && p.m_rDst.y > 0)
	{
		p.movey(-1);
	}
	if (m_bDown == true && p.m_rDst.y < 768 - 85)
	{
		p.movey(1);
	}
	if (m_bLeft == true && p.m_rDst.x > 0)
	{
		p.movex(-1);
	}
	if (m_bRight == true && p.m_rDst.x < 1024 - 98)
	{
		p.movex(1);
	}
	if (m_bUp || m_bDown || m_bLeft || m_bRight)
	{
		p.animation();
	}
}
void Engine::render(BACKGROUND &bg, Player &p)
{
	SDL_RenderClear(m_pRenderer);
	SDL_RenderCopy(m_pRenderer, m_pBackgroundTexture, bg.getSource(), bg.getDes());
	SDL_RenderCopy(m_pRenderer, m_pBirdTexture, p.getSource(), p.getDes());
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
			case'w':
			case 'W':
				if (!m_bUp)
				{
					m_bUp = true;
				}
				break;
			case'a':
			case 'A':
				if (!m_bLeft)
				{
					m_bLeft = true;
				}
				break;
			case's':
			case 'S':
				if (!m_bDown)
				{
					m_bDown = true;
				}
				break;
			case'd':
			case 'D':
				if (!m_bRight)
				{
					m_bRight = true;
				}
				break;

			}
			break;
		case SDL_KEYUP:
			switch (event.key.keysym.sym)
			{
			case'w':
			case 'W':
				m_bUp = false;
				break;
			case'a':
			case 'A':
				m_bLeft = false;
				break;
			case's':
			case 'S':
				m_bDown = false;
				break;
			case'd':
			case 'D':
				m_bRight = false;
				break;

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