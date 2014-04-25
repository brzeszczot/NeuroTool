#include "mmpi2.hpp"

MMPI2::Calc::Calc()
{
    reset_arrays();
    reset_raw_answers();
}

MMPI2::Calc::~Calc()
{

}

void MMPI2::Calc::reset_raw_answers()
{
    for(size_t ii=0; ii < Q_QUESTIONS; ii++)
        raw_answers[ii] = false;
}

void MMPI2::Calc::reset_arrays()
{
    trin_result = vrin_result = 0;
    for(size_t ii=0; ii < Q_SCALES; ii++)
        scales_result[ii] = 0;
}

void MMPI2::Calc::update()
{
    reset_arrays();

    // calculate scales
    for(int scale=0; scale < Q_SCALES; scale++)
    {
        for(int nr=0; nr < Q_QUESTIONS; nr++)
        {
            int q_nr_true = m_scales[scale][0][nr];
            if(q_nr_true != 0 && raw_answers[q_nr_true - 1])
                scales_result[scale]++;

            int q_nr_false = m_scales[scale][1][nr];
            if(q_nr_false != 0 && !raw_answers[q_nr_false - 1])
                scales_result[scale]++;

            if(q_nr_true == 0 && q_nr_false == 0)
                break;
        }
    }

    // calculate trin
    for(int ii=0; ii < Q_TRIN1; ii++)
    {
        if(raw_answers[m_trin1[ii][0] - 1] && raw_answers[m_trin1[ii][1] - 1])
            trin_result++;
    }
    for(int ii=0; ii < Q_TRIN2; ii++)
    {
        if(!raw_answers[m_trin2[ii][0] - 1] && !raw_answers[m_trin2[ii][1] - 1])
            trin_result--;
    }
    trin_result+=10;

    // calculating vrin
    for(int ii=0; ii < Q_VRIN; ii++)
    {
        bool l_pair, r_pair;
        m_vrin[ii][1] == 1 ? l_pair = true : l_pair = false;
        m_vrin[ii][3] == 1 ? r_pair = true : r_pair = false;
        if(raw_answers[m_vrin[ii][0] - 1] == l_pair && raw_answers[m_vrin[ii][2] - 1] == r_pair)
            vrin_result++;
    }

    // implement K values
    int index;
    for(int ii=0; ii < Q_K; ii++)
        if(m_k[ii][0] == scales_result[K])
        {
            index = ii;
            break;
        }
    scales_result[HS] += m_k[index][1];
    scales_result[PD] += m_k[index][2];
    scales_result[PT] += m_k[index][0];
    scales_result[SC] += m_k[index][0];
    scales_result[MA] += m_k[index][3];
}
