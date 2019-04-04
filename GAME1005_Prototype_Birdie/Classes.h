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

class Player : public SPRITE
{
public:
	Player()
	{
		m_rSrc.x = 0;	m_rDst.x = 1024 / 2;
		m_rSrc.y = 0;	m_rDst.y = 768 / 2;
		m_rSrc.w = 98;	m_rDst.w = 98;
		m_rSrc.h = 85;	m_rDst.h = 85;

		speed = 5;

	}
	
	void movex(int m)
	{
		m_rDst.x += m * speed;
	}
	void movey(int m)
	{
		m_rDst.y += m * speed;
	}
	void animation()
	{
		if (delayCtr == delayMax)
		{
			if (frameCtr < frameMax)
			{
				m_rSrc.x = 99 * frameCtr;
				frameCtr++;
			}
			else if (frameCtr == frameMax)
			{
				frameCtr = 0;
			}
			delayCtr = 0;
		}
		delayCtr++;

	}

private:
	int speed;
	int frameCtr = 0;
	int frameMax = 3;
	int delayCtr = 0;
	int delayMax = 8;
};
