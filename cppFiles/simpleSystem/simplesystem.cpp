#include "simplesystem.h"

SimpleSystem::SimpleSystem(float value)
{
    m_integrator = new Integrator(value);
}

float SimpleSystem::getOutput() const
{
    return m_integrator->state();
}

float SimpleSystem::update(float value, float dt)
{
    float tmp = m_integrator->state();

    m_integrator->update(value - tmp, dt);

    return tmp;
}
