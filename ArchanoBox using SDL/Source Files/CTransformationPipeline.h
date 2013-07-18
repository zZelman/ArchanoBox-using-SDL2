#pragma once

#include "stdafx.h"

class CTransformationPipeline
{
public:
	CTransformationPipeline()
	{
		m_sScaleInfo		= SVector3f(1.0f, 1.0f, 1.0f);
		m_sWorldPos			= SVector3f(0.0f, 0.0f, 0.0f);
		m_sRotationInfo		= SVector3f(0.0f, 0.0f, 0.0f);
	}

	// scales BY not TO
	void setScaleInfo(float x, float y, float z)
	{
		m_sScaleInfo.x = x;
		m_sScaleInfo.y = y;
		m_sScaleInfo.z = z;
	}

	// world position coords BY not To
	void setWorldPos(float x, float y, float z)
	{
		m_sWorldPos.x = x;
		m_sWorldPos.y = y;
		m_sWorldPos.z = z;
	}

	// rotates BY not TO
	void setRotateInfo(float x, float y, float z)
	{
		m_sRotationInfo.x = x;
		m_sRotationInfo.y = y;
		m_sRotationInfo.z = z;
	}

	// sets perspective information
	void setPerspectiveProjection(float fieldOfView, float width, float height, float zNear, float zFar)
	{
		m_sPerspectiveProjection.fieldOfView	= fieldOfView;
		m_sPerspectiveProjection.width			= width;
		m_sPerspectiveProjection.height			= height;
		m_sPerspectiveProjection.zNear			= zNear;
		m_sPerspectiveProjection.zFar			= zFar;
	}

	// set camera information for matrix transformations
	// camera values are determined elsewhere, but are used for matrix transformations here
	// * 'position' is location
	// * 'target' is the vector between the camera and what it is looking at
	// * 'up' is what defines what direction is up for the camera
	void setCamera(const SVector3f& position, const SVector3f& target, const SVector3f& up)
	{
		m_sCamera.position = position;
		m_sCamera.target = target;
		m_sCamera.up = up;
	}

	// concatenates all transformations
	const CMatrix4f* getTransformations();

private:
	struct
	{
		float fieldOfView; // angle between top and bottom view side
		float width;
		float height;
		float zNear;
		float zFar;
	} m_sPerspectiveProjection; // holds all camera information

	struct
	{
		SVector3f position;	// position of camera
		SVector3f target;	// the vector between the camera and what it is looking at
		SVector3f up;		// what is 'up' for the camera
	} m_sCamera; // camera information (copy)

	SVector3f m_sScaleInfo;		// scaling vector (what to scale by - not to)
	SVector3f m_sWorldPos;		// translation vector (what to translate by - not to)
	SVector3f m_sRotationInfo;	// rotation vector (what to rotate by - not to)

	CMatrix4f m_transformationMatrix;	// saved translation information (post calc) for optimization
};