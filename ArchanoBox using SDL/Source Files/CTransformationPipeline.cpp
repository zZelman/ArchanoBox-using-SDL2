#include "stdafx.h"

#include "CTransformationPipeline.h"

const CMatrix4f* CTransformationPipeline::getTransformations()
{
	CMatrix4f	ScaleTransform, RotateTransform, TranslationTransform,
	            CameraTranslationTransform, CameraRotateTransformation,
	            PerspectiveTransform;

	ScaleTransform				.initScaleTransform(m_sScaleInfo.x, m_sScaleInfo.y, m_sScaleInfo.z);
	RotateTransform				.initRotateTransform(m_sRotationInfo.x, m_sRotationInfo.y, m_sRotationInfo.z);
	TranslationTransform		.initTranslationTransform(m_sWorldPos.x, m_sWorldPos.y, m_sWorldPos.z);

	CameraTranslationTransform	.initTranslationTransform(-m_sCamera.position.x, -m_sCamera.position.y, -m_sCamera.position.z);
	CameraRotateTransformation	.initCameraTransform(m_sCamera.target, m_sCamera.up);

	PerspectiveTransform		.initPerspectiveProjection(m_sPerspectiveProjection.fieldOfView,
	        m_sPerspectiveProjection.width, m_sPerspectiveProjection.height,
	        m_sPerspectiveProjection.zNear, m_sPerspectiveProjection.fieldOfView);

	// save information for optimization
	m_transformationMatrix =	PerspectiveTransform *
	                            CameraRotateTransformation * CameraTranslationTransform *
	                            TranslationTransform * RotateTransform * ScaleTransform;

	return &m_transformationMatrix;
}