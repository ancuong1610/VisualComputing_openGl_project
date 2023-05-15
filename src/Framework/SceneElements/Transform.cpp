#include "Transform.h"



void Transform::updateTransformMatrix()
{
	m_transformMatrix = glm::translate(m_position) * glm::toMat4(m_rotation) * glm::scale(m_scale);

	m_xaxis = glm::normalize(glm::vec3(m_transformMatrix[0]));
	m_yaxis = glm::normalize(glm::vec3(m_transformMatrix[1]));
	m_zaxis = glm::normalize(glm::vec3(m_transformMatrix[2]));
}

Transform::Transform() :
	m_position(0.0f),
    m_rotation(glm::vec3(0,0,0)),
	m_scale(1.0f),
	m_transformMatrix(),
	m_xaxis(1.0f, 0.0f, 0.0f),
	m_yaxis(0.0f, 1.0f, 0.0f),
	m_zaxis(0.0f, 1.0f, 0.0f),
	m_matrixDirty(true)
{}

Transform::Transform(const glm::mat4 & transformMatrix) :
	m_position(transformMatrix[3]),
	m_rotation(glm::quat_cast(transformMatrix)),
	m_scale(glm::length(glm::vec3(transformMatrix[0])), glm::length(glm::vec3(transformMatrix[1])), glm::length(glm::vec3(transformMatrix[2]))),
	m_transformMatrix(transformMatrix),
	m_xaxis(glm::normalize(glm::vec3(transformMatrix[0]))),
	m_yaxis(glm::normalize(glm::vec3(transformMatrix[1]))),
	m_zaxis(glm::normalize(glm::vec3(transformMatrix[2]))),
	m_matrixDirty(true)
{
}

Transform::Transform(const glm::vec3 & position, const glm::quat & rotation, const glm::vec3 & scale) :
	m_position(position),
	m_rotation(rotation),
	m_scale(scale),
	m_transformMatrix(glm::translate(position) * glm::toMat4(rotation) * glm::scale(scale)),
	m_xaxis(glm::normalize(glm::vec3(toMat3(rotation)[0]))),
	m_yaxis(glm::normalize(glm::vec3(toMat3(rotation)[1]))),
	m_zaxis(glm::normalize(glm::vec3(toMat3(rotation)[2]))),
	m_matrixDirty(true)
{}

const glm::vec3 & Transform::getPosition()
{
	return m_position;
}

const glm::quat & Transform::getRotation()
{
	return m_rotation;
}

const glm::vec3 & Transform::getScale()
{
	return m_scale;
}

void Transform::setPosition(const glm::vec3 & position)
{
	m_position = position;
	m_matrixDirty = true;
}

void Transform::setRotation(const glm::quat & rotation)
{
	m_rotation = rotation;
	m_matrixDirty = true;
}

void Transform::setScale(const glm::vec3 & scale)
{
	m_scale = scale;
	m_matrixDirty = true;
}

const glm::mat4 & Transform::getMatrix()
{
	if (m_matrixDirty)
	{
		updateTransformMatrix();
		m_matrixDirty = false;
	}
	return m_transformMatrix;
}

void Transform::setMatrix(const glm::mat4 & matrix)
{
	Transform tmp(matrix);
	m_position = tmp.m_position;
	m_rotation = tmp.m_rotation;
	m_scale = tmp.m_scale;
	m_transformMatrix = matrix;
	m_xaxis = tmp.m_xaxis;
	m_yaxis = tmp.m_yaxis;
	m_zaxis = tmp.m_zaxis;
	m_matrixDirty = false;
}

void Transform::translate(const glm::vec3 & deltaPos)
{
	m_position += deltaPos;
	m_matrixDirty = true;
}

void Transform::translateLocal(const glm::vec3 & deltaPos)
{
	m_position += deltaPos.x * m_xaxis + deltaPos.y * m_yaxis + deltaPos.z * m_zaxis;
	m_matrixDirty = true;
}

void Transform::rotate(const glm::quat & deltaRot)
{
	m_rotation = glm::normalize(deltaRot * m_rotation);
	m_matrixDirty = true;
}

void Transform::rotateLocal(const glm::quat & deltaRot)
{
	m_rotation = glm::normalize(m_rotation * deltaRot);
	m_matrixDirty = true;
}

void Transform::scale(const glm::vec3 & scale)
{
	m_scale *= scale;
	m_matrixDirty = true;
}

const glm::vec3 & Transform::getXAxis()
{
	if (m_matrixDirty)
	{
		updateTransformMatrix();
		m_matrixDirty = false;
	}
	return m_xaxis;
}

const glm::vec3 & Transform::getYAxis()
{
	if (m_matrixDirty)
	{
		updateTransformMatrix();
		m_matrixDirty = false;
	}
	return m_yaxis;
}

const glm::vec3 & Transform::getZAxis()
{
	if (m_matrixDirty)
	{
		updateTransformMatrix();
		m_matrixDirty = false;
	}
	return m_zaxis;
}

const glm::mat4 & Transform::getTransformMatrix()
{
	if (m_matrixDirty)
	{
		updateTransformMatrix();
		m_matrixDirty = false;
	}
	return m_transformMatrix;
}

glm::vec3 Transform::getDirection()
{
	return -getZAxis();
}

void Transform::lookinto(const glm::vec3 & direction)
{
	glm::vec3 ndir(glm::normalize(-direction));
	glm::vec3 right = glm::normalize(glm::cross(glm::vec3(0.0f, 1.0f, 0.0f), ndir));
	glm::vec3 up = glm::normalize(glm::cross(ndir, right));

	//construct a 3x3 rotation matrix from direction and global up vector
	glm::mat3 rot(right, up, ndir);

	setRotation(glm::quat_cast(rot));
}

glm::mat4 Transform::getInverseMatrix()
{
	if (m_matrixDirty)
	{
		updateTransformMatrix();
		m_matrixDirty = false;
	}
	return glm::inverse(m_transformMatrix);
}

void Transform::rotateAroundPoint(const glm::vec3 point, const glm::quat &deltaRot) {

    glm::mat4x4 mm = getMatrix();
    mm = glm::translate(point)*mm;
    mm = glm::toMat4(deltaRot)*mm;
    mm = glm::translate(-point) *mm;
    setMatrix(mm);

}


Transform::~Transform()
{}
