#ifndef SINANALOG_H
#define SINANALOG_H
#include <vector>
#include <cstdint>
#include "blocks/integrator/integrator.h"

class SinAnalog
{
public:
    SinAnalog(std::vector<float> &initial_conditions,
               std::vector<std::vector<float>> &matrix_A,
               std::vector<float> &matrix_B,
               std::vector<float> &matrix_C,
               std::vector<float> &matrix_D);

    ~SinAnalog();

    float getOutput();
    float update(float input, float dt);

private:
    Integrator *m_integrator_X1;
    Integrator *m_integrator_X2;

    float m_previous_input = 0.0;

    std::vector<std::vector<float>> m_matrix_A;
    std::vector<float> m_matrix_B;
    std::vector<float> m_matrix_C;
    std::vector<float> m_matrix_D;

    std::vector<float> m_initial_conditions;
};

#endif // SINANALOG_H



