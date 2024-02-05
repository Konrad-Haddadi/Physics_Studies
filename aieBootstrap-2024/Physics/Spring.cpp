#include "Spring.h"
#include "RigidBody.h"

#include <glm/glm.hpp>

glm::vec2 Spring::GetContact1(float _alpha)
{
    return m_body1 ? m_body1->ToWorld(m_contact1, _alpha) : m_contact1;
}

glm::vec2 Spring::GetContact2(float _alpha)
{
    return m_body2 ? m_body2->ToWorld(m_contact2, _alpha) : m_contact2;
}

void Spring::FixedUpdate(glm::vec2 _gravity, float _timeStep)
{
    glm::vec2 p1 = GetContact1(1);
    glm::vec2 p2 = GetContact2(1);

    float length = glm::distance(p1, p2);
    glm::vec2 direction = glm::normalize(p2 - p1);

    glm::vec2 relativeVelocity = m_body2->GetVelocity() - m_body1->GetVelocity();

    glm::vec2 force = direction * m_springCoefficent * (m_restLength - length) - m_damping * relativeVelocity;

    m_body1->ApplyForce(-force * _timeStep, p1 - m_body1->GetPosition());
    m_body2->ApplyForce(force * _timeStep, p2 - m_body2->GetPosition());
}

void Spring::Draw(float _alpha)
{
}

float Spring::GetPotentialEnergy(glm::vec2 _gravity)
{
    return 0.0f;
}
