#include "stdafx.h"

SVector3f SVector3f::crossProduct(const SVector3f& v) const
{
	const float _x = y * v.z - z * v.y;
	const float _y = z * v.x - x * v.z;
	const float _z = x * v.y - y * v.x;

	return SVector3f(_x, _y, _z);
}


SVector3f& SVector3f::normalize()
{
	const float Length = sqrtf(x * x + y * y + z * z);

	x /= Length;
	y /= Length;
	z /= Length;

	return *this;
}


void SVector3f::rotate(float angle, const SVector3f& axis)
{
	const float sin_halfAngle = sinf(ToRadian(angle / 2));
	const float cos_halfAngle = cosf(ToRadian(angle / 2));

	const float Rx = axis.x * sin_halfAngle;
	const float Ry = axis.y * sin_halfAngle;
	const float Rz = axis.z * sin_halfAngle;
	const float Rw = cos_halfAngle;
	SQuaternion rotationQ(Rx, Ry, Rz, Rw);

	SQuaternion conjugateQ = rotationQ.conjugate();
	//conjugateQ.normalize();
	SQuaternion W = rotationQ * (*this) * conjugateQ;

	x = W.x;
	y = W.y;
	z = W.z;
}


void CMatrix4f::initScaleTransform(float scaleX, float scaleY, float scaleZ)
{
	// Matrix info:
	// x	0	0	0
	// 0	y	0	0
	// 0	0	z	1
	m[0][0] = scaleX;
	m[0][1] = 0.0f;
	m[0][2] = 0.0f;
	m[0][3] = 0.0f;

	m[1][0] = 0.0f;
	m[1][1] = scaleY;
	m[1][2] = 0.0f;
	m[1][3] = 0.0f;

	m[2][0] = 0.0f;
	m[2][1] = 0.0f;
	m[2][2] = scaleZ;
	m[2][3] = 0.0f;

	m[3][0] = 0.0f;
	m[3][1] = 0.0f;
	m[3][2] = 0.0f;
	m[3][3] = 1.0f;
}


void CMatrix4f::initRotateTransform(float rotateX, float rotateY, float rotateZ)
{
	CMatrix4f rx, ry, rz;

	const float x = ToRadian(rotateX);
	const float y = ToRadian(rotateY);
	const float z = ToRadian(rotateZ);

	// Matrix info:
	// 1		0				0			0
	// 0		cosf(x)			-sinf(x)	0
	// 0		sinf(x)			cosf(x)		0
	// 0		0				0			1
	rx.m[0][0] = 1.0f;
	rx.m[0][1] = 0.0f;
	rx.m[0][2] = 0.0f;
	rx.m[0][3] = 0.0f;

	rx.m[1][0] = 0.0f;
	rx.m[1][1] = cosf(x);
	rx.m[1][2] = -sinf(x);
	rx.m[1][3] = 0.0f;

	rx.m[2][0] = 0.0f;
	rx.m[2][1] = sinf(x);
	rx.m[2][2] = cosf(x) ;
	rx.m[2][3] = 0.0f;

	rx.m[3][0] = 0.0f;
	rx.m[3][1] = 0.0f;
	rx.m[3][2] = 0.0f;
	rx.m[3][3] = 1.0f;

	// Matrix info:
	// cosf(y)		0			-sinf(y)	0
	// 0			1			0			0
	// sinf(y)		0			cosf(y)		0
	// 0			0			0			1
	ry.m[0][0] = cosf(y);
	ry.m[0][1] = 0.0f;
	ry.m[0][2] = -sinf(y);
	ry.m[0][3] = 0.0f;

	ry.m[1][0] = 0.0f;
	ry.m[1][1] = 1.0f;
	ry.m[1][2] = 0.0f;
	ry.m[1][3] = 0.0f;

	ry.m[2][0] = sinf(y);
	ry.m[2][1] = 0.0f;
	ry.m[2][2] = cosf(y);
	ry.m[2][3] = 0.0f;

	ry.m[3][0] = 0.0f;
	ry.m[3][1] = 0.0f;
	ry.m[3][2] = 0.0f;
	ry.m[3][3] = 1.0f;

	// Matrix info:
	// cosf(z)		-sinf(z)	0			0
	// sinf(z)		cosf(z)		0			0
	// 0			0			1			0
	// 0			0			0			1
	rz.m[0][0] = cosf(z);
	rz.m[0][1] = -sinf(z);
	rz.m[0][2] = 0.0f;
	rz.m[0][3] = 0.0f;

	rz.m[1][0] = sinf(z);
	rz.m[1][1] = cosf(z);
	rz.m[1][2] = 0.0f;
	rz.m[1][3] = 0.0f;

	rz.m[2][0] = 0.0f;
	rz.m[2][1] = 0.0f;
	rz.m[2][2] = 1.0f;
	rz.m[2][3] = 0.0f;

	rz.m[3][0] = 0.0f;
	rz.m[3][1] = 0.0f;
	rz.m[3][2] = 0.0f;
	rz.m[3][3] = 1.0f;

	*this = rz * ry * rx;
}


void CMatrix4f::initTranslationTransform(float x, float y, float z)
{
	// Matrix info:
	// 1  0  0  x
	// 0  1  0  y
	// 0  0  1  z
	// 0  0  0  1
	m[0][0] = 1.0f;
	m[0][1] = 0.0f;
	m[0][2] = 0.0f;
	m[0][3] = x;

	m[1][0] = 0.0f;
	m[1][1] = 1.0f;
	m[1][2] = 0.0f;
	m[1][3] = y;

	m[2][0] = 0.0f;
	m[2][1] = 0.0f;
	m[2][2] = 1.0f;
	m[2][3] = z;

	m[3][0] = 0.0f;
	m[3][1] = 0.0f;
	m[3][2] = 0.0f;
	m[3][3] = 1.0f;
}


void CMatrix4f::initCameraTransform(const SVector3f& Target, const SVector3f& Up)
{
	// N - The vector from the camera to its target. Also known as the 'look at' vector in some
	//		3D literature. This vector corresponds to the Z axis
	// V - When standing upright this is the vector from your head to the sky. If you are writing
	//		a flight simulator and the plane is reversed that vector may very well point to the
	//		ground. This vector corresponds to the Y axis.
	// U - This vector points from the camera to its "right" side". It corresponds to the X axis.

	SVector3f N = Target;
	N.normalize();
	SVector3f U = Up;
	U.normalize();
	U = U.crossProduct(N);
	SVector3f V = N.crossProduct(U);

	// matrix info:
	// U.x		U.y		U.z		0
	// V.x		V.y		V.z		0
	// N.x		N.y		N.z		0
	// 0		0		0		1
	m[0][0] = U.x;
	m[0][1] = U.y;
	m[0][2] = U.z;
	m[0][3] = 0.0f;

	m[1][0] = V.x;
	m[1][1] = V.y;
	m[1][2] = V.z;
	m[1][3] = 0.0f;

	m[2][0] = N.x;
	m[2][1] = N.y;
	m[2][2] = N.z;
	m[2][3] = 0.0f;

	m[3][0] = 0.0f;
	m[3][1] = 0.0f;
	m[3][2] = 0.0f;
	m[3][3] = 1.0f;
}


void CMatrix4f::initPerspectiveProjection(float FOV, float width, float height, float zNear, float zFar)
{
	const float aspectRatio         = width / height;
	const float _zNear				= zNear;
	const float _zFar				= zFar;
	const float zRange				= _zNear - _zFar;
	const float tanHalfFieldOfView	= tanf(ToRadian(FOV / 2.0f));

	// matrix info:
	// 1/(ar * tan(fov/2))	0				0								0
	// 0					1/(tan(fov/2))	0								0
	// 0					0				(-zNear - zFar)/(zNear - zFar)	(2 * zFar * zNear)/(zNear - zFar)
	// 0					0				1								0
	m[0][0] = 1.0f / (tanHalfFieldOfView * aspectRatio);
	m[0][1] = 0.0f;
	m[0][2] = 0.0f;
	m[0][3] = 0.0;

	m[1][0] = 0.0f;
	m[1][1] = 1.0f / tanHalfFieldOfView;
	m[1][2] = 0.0f;
	m[1][3] = 0.0;

	m[2][0] = 0.0f;
	m[2][1] = 0.0f;
	m[2][2] = (-zNear - zFar) / zRange ;
	m[2][3] = 2.0f * zFar * zNear / zRange;

	m[3][0] = 0.0f;
	m[3][1] = 0.0f;
	m[3][2] = 1.0f;
	m[3][3] = 0.0;
}


SQuaternion::SQuaternion(float _x, float _y, float _z, float _w)
{
	x = _x;
	y = _y;
	z = _z;
	w = _w;
}


void SQuaternion::normalize()
{
	float length = sqrtf(x * x + y * y + z * z + w * w);

	x /= length;
	y /= length;
	z /= length;
	w /= length;
}


SQuaternion SQuaternion::conjugate()
{
	SQuaternion ret(-x, -y, -z, w);
	return ret;
}


SQuaternion operator*(const SQuaternion& l, const SQuaternion& r)
{
	const float w = (l.w * r.w) - (l.x * r.x) - (l.y * r.y) - (l.z * r.z);
	const float x = (l.x * r.w) + (l.w * r.x) + (l.y * r.z) - (l.z * r.y);
	const float y = (l.y * r.w) + (l.w * r.y) + (l.z * r.x) - (l.x * r.z);
	const float z = (l.z * r.w) + (l.w * r.z) + (l.x * r.y) - (l.y * r.x);

	SQuaternion ret(x, y, z, w);

	return ret;
}


SQuaternion operator*(const SQuaternion& q, const SVector3f& v)
{
	const float w = - (q.x * v.x) - (q.y * v.y) - (q.z * v.z);
	const float x = (q.w * v.x) + (q.y * v.z) - (q.z * v.y);
	const float y = (q.w * v.y) + (q.z * v.x) - (q.x * v.z);
	const float z = (q.w * v.z) + (q.x * v.y) - (q.y * v.x);

	SQuaternion ret(x, y, z, w);

	return ret;
}