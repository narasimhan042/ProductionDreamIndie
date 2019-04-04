#pragma once
#include <iostream>
#include <string>
#include "SDL.h"
#include "SDL_image.h"
using namespace std;

class SPRITE
{
public:

	SDL_Rect m_rSrc;
	SDL_Rect m_rDst;
	const SDL_Rect*getSource()
	{
		return &m_rSrc;
	}
	const SDL_Rect*getDes()
	{
		return &m_rDst;
	}
	
private:

};

class BACKGROUND : public SPRITE
{
public:
	BACKGROUND()
	{
		m_rSrc.x = 0;
		m_rSrc.y = 0;
		m_rSrc.w = 1600;
		m_rSrc.h = 900;

		m_rDst.x = 0;
		m_rDst.y = 0;
		m_rDst.w = 1024;
		m_rDst.h = 768;
		
	}

private:

};
