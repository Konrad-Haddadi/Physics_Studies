#include "Spring.h"
#include "RigidBody.h"
#include "Gizmos.h"
#include "PhysicsApp.h"
#include <glm/glm.hpp>

Spring::Spring(RigidBody* _body1, RigidBody* _body2, float _springCoefficient, float _damping, float _restLength, glm::vec4 _color, glm::vec2 _contact1, glm::vec2 _contact2)
    : PhysicsObject(JOINT), m_body1(_body1), m_body2(_body2), m_springCoefficent(_springCoefficient), m_damping(_damping), m_restLength(_restLength), m_contact1(_contact1), m_contact2(_contact2), m_color(_color)
{
    if (m_restLength == 0)
    {
        if (m_body1)
            m_body1->CalculateAxes();

        if (m_body2)
            m_body2->CalculateAxes();

        m_restLength = glm::distance(GetContact1(), GetContact2());
    }
}

Spring::~Spring()
{
}

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
    glm::vec2 p1 = GetContact1();
    glm::vec2 p2 = GetContact2();

    float length = glm::distance(p1, p2);
    glm::vec2 direction = glm::normalize(p2 - p1);

    glm::vec2 relativeVelocity = m_body2->GetVelocity() - m_body1->GetVelocity();

    // F = -kX - bv
    glm::vec2 force = direction * m_springCoefficent * (m_restLength - length) - m_damping * relativeVelocity;

    // cap the spring force to 1000 N to prevent numerical instability
   /* const float threshold = 1000.0f;
    float forceMag = glm::length(force);

    if (forceMag > threshold)
        force *= threshold / forceMag; */

    m_body1->ApplyForce(-force * _timeStep, p1 - m_body1->GetPosition());
    m_body2->ApplyForce(force * _timeStep, p2 - m_body2->GetPosition());


}

void Spring::Draw(float _alpha)
{
    aie::Gizmos::add2DLine(GetContact1(_alpha), GetContact2(_alpha), m_color);
}

float Spring::GetPotentialEnergy(glm::vec2 _gravity)
{
    return 0.0f;
}
