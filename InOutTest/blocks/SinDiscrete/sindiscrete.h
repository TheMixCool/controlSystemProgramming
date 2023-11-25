#ifndef SINDISCRETE_H
#define SINDISCRETE_H
#include <vector>
#include <cstdint>

class SinDiscrete
{
public:
    SinDiscrete(std::vector<float> &initial_conditions,
                std::vector<std::vector<float>> &matrix_A,
                std::vector<float> &matrix_B,
                std::vector<float> &matrix_C,
                std::vector<float> &matrix_D);

    float getOutput();

    float update(float input);

private:
    std::vector<std::vector<float>> m_matrix_A;
    std::vector<float> m_matrix_B;
    std::vector<float> m_matrix_C;
    std::vector<float> m_matrix_D;

    std::vector<float> m_initial_conditions;

    float m_previous_input = 0.0;
};

#endif // SINDISCRETE_H


