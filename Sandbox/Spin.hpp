#pragma once

#include "Core/Time.h"
#include "SceneManagement/Scripting/Behavior.h"
#include "SceneManagement/GameObject.h"
#include "glm/ext/quaternion_geometric.hpp"

class Spinner : public Dread::Behavior {
public:
    float m_Pitch, m_Yaw;
    float m_RotationSpeed = 75.0f;

    void OnCreate() override {
        m_Pitch = 0.0f;
        m_Yaw = 0.0f;
    }

    void OnUpdate() override {
        m_Pitch += m_RotationSpeed * Dread::Time::deltaTime;
        m_Yaw += m_RotationSpeed * Dread::Time::deltaTime;

		glm::quat qPitch = glm::angleAxis(glm::radians(m_Pitch), glm::vec3(1, 0, 0));
		glm::quat qYaw = glm::angleAxis(glm::radians(m_Yaw), glm::vec3(0, -1, 0));

        gameObject->m_Transform.m_Rotation = glm::normalize(qPitch * qYaw);
    }

};