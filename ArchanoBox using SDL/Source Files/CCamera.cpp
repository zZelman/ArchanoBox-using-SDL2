#include "stdafx.h"

#include "CCamera.h"

CCamera::~CCamera()
{

}


CCamera::CCamera(int windowWidth, int windowHeight, float stepScale)
{
	m_windowWidth = windowWidth;
	m_windowHeight = windowHeight;

	m_position	= SVector3f(0.0f, 0.0f, 0.0f);
	m_target	= SVector3f(0.0f, 0.0f, 1.0f);
	m_target.normalize();
	m_up		= SVector3f(0.0f, 1.0f, 0.0f);

	m_stepScale = stepScale;

	init();
}


CCamera::CCamera(int windowWidth, int windowHeight,
                 const SVector3f& position, const SVector3f& target, const SVector3f& up,
                 float stepScale)
{
	m_windowWidth = windowWidth;
	m_windowHeight = windowHeight;

	m_position	= position;

	m_target	= target;
	m_target.normalize();

	m_up		= up;
	m_up.normalize();

	m_stepScale = stepScale;

	init();
}


void CCamera::init()
{
	SVector3f horizontalTarget(m_target.x, 0.0f, m_target.z);
	horizontalTarget.normalize();

	// horizontal angle processing
	if (horizontalTarget.z >= 0.0f)
	{
		if (horizontalTarget.x >= 0.0f)
		{
			m_angleHorizontal = 360.0f - ToDegree(asin(horizontalTarget.z));
		}
		else
		{
			m_angleHorizontal = 180.0f + ToDegree(asin(horizontalTarget.z));
		}
	}
	else
	{
		if (horizontalTarget.x >= 0.0f)
		{
			m_angleHorizontal = ToDegree(asin(-horizontalTarget.z));
		}
		else
		{
			m_angleHorizontal = 90.0f + ToDegree(asin(-horizontalTarget.z));
		}
	}

	// vertical angle processing
	m_angleVertical = -ToDegree(asin(m_target.y));

	m_sMousePosition.x = m_windowWidth / 2;
	m_sMousePosition.y = m_windowHeight / 2;

	SDL_WarpMouseInWindow(NULL, m_sMousePosition.x, m_sMousePosition.y);
}


void CCamera::setCamera(SVector3f& position, SVector3f& target, SVector3f& up)
{
	m_position	= position;

	m_target	= target;
	m_target.normalize();

	m_up		= up;
	m_up.normalize();
}


// defines what keys the camera will accept to do work on
bool CCamera::isCamera_key(SDL_Event& keyboardEvent)
{

	if (keyboardEvent.key.keysym.sym == SDLK_LEFT ||
	        keyboardEvent.key.keysym.sym == SDLK_RIGHT ||
	        keyboardEvent.key.keysym.sym == SDLK_UP ||
	        keyboardEvent.key.keysym.sym == SDLK_DOWN)
	{
		return true;
	}
	return false;
}


// completes action based on individual keys pressed
void CCamera::proccess_key(SDL_Event& keyboardEvent)
{
	switch (keyboardEvent.key.keysym.sym)
	{
	case SDLK_LEFT:
		{
			SVector3f left = m_target.crossProduct(m_up);
			left.normalize();
			left *= m_stepScale;
			m_position += left;
			break;
		}

	case SDLK_RIGHT:
		{
			SVector3f right = m_up.crossProduct(m_target);
			right.normalize();
			right *= m_stepScale;
			m_position += right;
			break;
		}

	case SDLK_UP:
		{
			m_position += (m_target * m_stepScale);
			break;
		}

	case SDLK_DOWN:
		{
			m_position -= (m_target * m_stepScale);
			break;
		}
	}
}


// defines what mouse movements the camera will accept to do work on
bool CCamera::isCamera_mouse(SDL_Event& mouseEvent)
{
	if (mouseEvent.type == SDL_MOUSEMOTION)
	{
		return true;
	}
	return false;
}


// completes actions based on mouse movement
void CCamera::proccess_mouse(SDL_Event& mouseEvent)
{
	int x, y;
	SDL_GetMouseState(&x, &y);

	const int deltaX = x - m_sMousePosition.x;
	const int deltaY = y - m_sMousePosition.y;

	m_sMousePosition.x = x;
	m_sMousePosition.y = y;

	m_angleHorizontal += (float)deltaX / 20.0f;
	m_angleVertical += (float)deltaY / 20.0f;

	update();
}


void CCamera::update()
{
	const SVector3f axis_vertical(0.0f, 1.0f, 0.0f);

	// Rotate the view vector by the horizontal angle around the vertical axis
	SVector3f view(1.0f, 0.0f, 0.0f);
	view.rotate(m_angleHorizontal, axis_vertical);
	view.normalize();

	// Rotate the view vector by the vertical angle around the horizontal axis
	SVector3f axis_horizontal = axis_vertical.crossProduct(view);
	axis_horizontal.normalize();
	view.rotate(m_angleVertical, axis_horizontal);

	m_target = view;
	m_target.normalize();

	m_up = m_target.crossProduct(axis_horizontal);
	m_up.normalize();
}