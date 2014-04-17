#include "waisr.hpp"

// oblicz IQ i wyniki czynnikowe
short int* WAISR::Calculate2(short int wp[WP1])
{
    short int wc_select[WP1] = {0,2,0,2,0,0,1,1,1,1,2};
    short int ii,jj;
    short int sum_wc[3],sum[3];
    short int *wc_res = new short int[WC_RES];

    for(ii=0;ii<3;ii++)
    {
        sum_wc[ii]=0;
        sum[ii]=0;
    }
    // sumowanie
    for(ii=0;ii<WP1;ii++)
    {
        if(ii<6)    sum[0]+=wp[ii];
        else        sum[1]+=wp[ii];
        sum_wc[wc_select[ii]]+=wp[ii];
    }
    sum[2] = sum[0]+sum[1];

    // wyniki czynnikowe
    for(ii=0;ii<WC_POINTS;ii++)
        for(jj=1;jj<4;jj++)
            if(wc_matrix[jj][ii]==sum_wc[jj-1])
                wc_res[(jj-1)+3] = wc_matrix[0][ii];
    // IQ
    for(ii=0;ii<IQ_POINTS;ii++)
        for(jj=1;jj<4;jj++)
            if(iq_matrix[jj][ii][0]==sum[jj-1] || (iq_matrix[jj][ii][1]==sum[jj-1] && iq_matrix[jj][ii][1]>0 && jj==3))
                wc_res[jj-1] = iq_matrix[0][ii][0];

    return wc_res;
}

// oblicz wartosci przeliczone WAIS
short int* WAISR::Calculate(short int wp1[WP1], int age)
{
    short int ii,jj;
    short int *wais_res = new short int[WP1];

    for(ii=0;ii<AGE_SCOPE;ii++)
        if(age<=age_scope[ii])
        {
            age = ii;
            break;
        }
    for(jj=0;jj<WP1;jj++)
    {
        for(ii=WP2-1;ii>=0;ii--)
        {
            if(wp1[jj]<=wais_matrix[age][ii][jj][0] || wp1[jj]<=wais_matrix[age][ii][jj][1])
            {
                wais_res[jj]=WP2-ii;
                break;
            }
            else
                wais_res[jj]=0;
        }
    }
    return wais_res;
}
