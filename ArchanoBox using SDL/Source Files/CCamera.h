#pragma once

#include "stdafx.h"

class CCamera
{
public:
	~CCamera();
	CCamera(int windowWidth, int windowHeight, float stepScale = 0.1f);
	CCamera(int windowWidth, int windowHeight,
	        const SVector3f& position, const SVector3f& target, const SVector3f& up,
	        float stepScale = 0.1f);

	// set camera information
	// * 'position' is location
	// * 'target' is the vector between the camera and what it is looking at
	// * 'up' is what defines what direction is up for the camera
	void setCamera(SVector3f& position, SVector3f& target, SVector3f& up);

	void setStepScale(float stepScale)
	{
		m_stepScale = stepScale;
	}

	const SVector3f& getPosition() const
	{
		return m_position;
	}
	const SVector3f& getTarget() const
	{
		return m_target;
	}
	const SVector3f& getUp() const
	{
		return m_up;
	}

	bool isCamera_key(SDL_Event& keyboardEvent); // defines what keys the camera will accept to do work on
	void proccess_key(SDL_Event& keyboardEvent); // completes action based on individual keys pressed

	bool isCamera_mouse(SDL_Event& mouseEvent); // defines what mouse movements the camera will accept to do work on
	void proccess_mouse(SDL_Event& mouseEvent); // completes actions based on mouse movement


private:
	SVector3f m_position;
	SVector3f m_target;
	SVector3f m_up;

	int m_windowWidth;
	int m_windowHeight;

	float m_angleHorizontal;
	float m_angleVertical;
	float m_stepScale;

	SVector2i m_sMousePosition;

	void init();
	void update();
};