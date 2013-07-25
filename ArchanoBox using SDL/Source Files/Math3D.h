#pragma once

#include "stdafx.h"

#define ToRadian(x) (float)(((x) * M_PI / 180.0f))
#define ToDegree(x) (float)(((x) * 180.0f / M_PI))

// Plane old data-structure
struct SVector2i
{
	int x;
	int y;
};

struct SVector2f
{
	float x;
	float y;

	SVector2f() {}

	SVector2f(float _x, float _y)
	{
		x = _x;
		y = _y;
	}
};

// Plane old data-structure
struct SVector3f
{
	float x;
	float y;
	float z;

	SVector3f() {}

	// Plane old data-structure
	SVector3f(float _x, float _y, float _z)
	{
		x = _x;
		y = _y;
		z = _z;
	}

	SVector3f& operator+=(const SVector3f& r)
	{
		x += r.x;
		y += r.y;
		z += r.z;

		return *this;
	}

	SVector3f& operator-=(const SVector3f& r)
	{
		x -= r.x;
		y -= r.y;
		z -= r.z;

		return *this;
	}

	SVector3f& operator*=(float f)
	{
		x *= f;
		y *= f;
		z *= f;

		return *this;
	}

	// * cross product between two vector3f objects (this and the one given)
	// * A cross product between two vectors produces a vector which is perpendicular to the plane defined by the vectors
	SVector3f crossProduct(const SVector3f& v) const;

	// normalizing a vector means that it reduces each coord such that the sum is equal to 1
	//		this is achieved by dividing each coord in the vector by the distance of the vector
	SVector3f& normalize();

	void rotate(float angle, const SVector3f& axis);
};

inline SVector3f operator+(const SVector3f& l, const SVector3f& r)
{
	SVector3f Ret(l.x + r.x,
	              l.y + r.y,
	              l.z + r.z);

	return Ret;
}

inline SVector3f operator-(const SVector3f& l, const SVector3f& r)
{
	SVector3f Ret(l.x - r.x,
	              l.y - r.y,
	              l.z - r.z);

	return Ret;
}

inline SVector3f operator*(const SVector3f& l, float f)
{
	SVector3f Ret(l.x * f,
	              l.y * f,
	              l.z * f);

	return Ret;
}

// * plane old data structure
// * used to map vertex coords to texture coords
struct SVertex
{
	SVector3f m_position;
	SVector2f m_texture;

	SVertex() {}

	SVertex(SVector3f position, SVector2f texture)
	{
		m_position = position;
		m_texture = texture;
	}
};



class CMatrix4f
{
public:
	float m[4][4];

	CMatrix4f() {}

	// performs scale transformation based on global vars set
	void initScaleTransform(float scaleX, float scaleY, float scaleZ);

	// performs rotation transformation based on global vars set
	void initRotateTransform(float rotateX, float rotateY, float rotateZ);

	// performs translation transformation based on global vars set
	void initTranslationTransform(float x, float y, float z);

	// * camera transformation
	// * only the target and up vectors are supplied in non normalized form (then normalized)
	// * the 'V' or 'right' vector is produced by the cross product of the 'target' and 'up', it is just easier that way
	//		(it will always produce a perfect 90 degree vector from the plane produced by 'target and 'up)
	void initCameraTransform(const SVector3f& target, const SVector3f& up);

	// maps 3D space onto 2D screen coords based on camera information set
	// * FOV stands for field of view (the angle between the top and bottom of the viewing screen
	void initPerspectiveProjection(float FOV, float width, float height, float zNear, float zFar);

	inline void InitIdentity()
	{
		m[0][0] = 1.0f;
		m[0][1] = 0.0f;
		m[0][2] = 0.0f;
		m[0][3] = 0.0f;
		m[1][0] = 0.0f;
		m[1][1] = 1.0f;
		m[1][2] = 0.0f;
		m[1][3] = 0.0f;
		m[2][0] = 0.0f;
		m[2][1] = 0.0f;
		m[2][2] = 1.0f;
		m[2][3] = 0.0f;
		m[3][0] = 0.0f;
		m[3][1] = 0.0f;
		m[3][2] = 0.0f;
		m[3][3] = 1.0f;
	}

	inline CMatrix4f operator*(const CMatrix4f& right) const
	{
		CMatrix4f ret;

		for (unsigned int i = 0 ; i < 4 ; i++)
		{
			for (unsigned int j = 0 ; j < 4 ; j++)
			{
				ret.m[i][j] = m[i][0] * right.m[0][j] +
				              m[i][1] * right.m[1][j] +
				              m[i][2] * right.m[2][j] +
				              m[i][3] * right.m[3][j];
			}
		}

		return ret;
	}
};

struct SQuaternion
{
	float x, y, z, w;

	SQuaternion(float _x, float _y, float _z, float _w);

	void normalize();

	SQuaternion conjugate();
};

SQuaternion operator*(const SQuaternion& l, const SQuaternion& r);

SQuaternion operator*(const SQuaternion& q, const SVector3f& v);