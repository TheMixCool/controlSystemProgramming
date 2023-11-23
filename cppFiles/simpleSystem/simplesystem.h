#ifndef SIMPLESYSTEM_H
#define SIMPLESYSTEM_H

#include "blocks/integrator/integrator.h"

class SimpleSystem
{
public:
    SimpleSystem(float value);
    float getOutput() const;
    float update(float value, float dt);

private:
   Integrator *m_integrator;
};

#endif // SIMPLESYSTEM_H
