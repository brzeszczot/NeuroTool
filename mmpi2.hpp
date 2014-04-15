#ifndef MMPI2_HPP
#define MMPI2_HPP

#include <String>

namespace MMPI2
{
    enum Q_VAR
    {
        Q_QUESTIONS = 20,  // 567
        Q_SCALES    = 20,  // ???
        Q_VRIN      = 67,
        Q_TRIN1     = 13,
        Q_TRIN2     = 10,
        Q_NORMS     = 200, // ???
        TRUE_INT    = 1,
        FALSE_INT   = 0
    };

    const std::string scales_names[Q_SCALES] =
    {
        "Skala F", "Skala D", "Skala D", "Skala D", "Skala D", "Skala D", "Skala D", "Skala D", "Skala D", "Skala D",
        "Skala F", "Skala D", "Skala D", "Skala D", "Skala D", "Skala D", "Skala D", "Skala D", "Skala D", "Skala D"
    };

    const unsigned short int m_scales[Q_SCALES][2][Q_QUESTIONS] =
    {
        {{11,18,24},{2,6,29}},
        {{12,19,25,31},{3,7}},
        {{13,10,26,100,130,190},{4,8,31,200,210,280,270,500}}
    };

    const unsigned short int m_vrin[Q_VRIN][4] =
    {
        {22,1,277,0}, {103,1,344,0}, {226,1,267,0}, {365,1,452,0},
        {28,1,111,0}, {103,0,344,1}, {246,1,407,0}, {372,1,405,0},
        {28,0,111,1}, {105,0,431,1}, {259,0,333,1}, {395,1,435,0},
        {31,1,299,0}, {116,0,430,1}, {265,0,337,1}, {396,1,403,0},
        {32,0,316,1}, {135,0,482,1}, {271,1,285,0}, {397,1,438,0},
        {46,1,265,0}, {136,0,302,1}, {277,0,306,1}, {411,0,485,1},
        {49,1,280,0}, {144,1,336,0}, {290,0,556,1}, {413,1,449,0},
        {60,0,311,1}, {146,1,532,0}, {302,1,444,0}, {413,0,449,1},
        {65,1,305,0}, {147,1,325,0}, {303,0,506,1}, {435,0,555,1},
        {71,0,454,1}, {147,0,325,1}, {323,1,324,0}, {472,1,533,0},
        {73,0,377,1}, {161,1,289,0}, {323,0,324,1}, {489,1,502,0},
        {84,1,105,0}, {166,1,268,0}, {331,0,442,1}, {491,1,509,0},
        {86,0,359,1}, {175,0,464,1}, {339,0,394,1}, {506,1,520,0},
        {95,0,388,1}, {180,1,316,0}, {349,0,515,1}, {513,1,542,0},
        {96,1,311,0}, {192,1,276,0}, {350,0,521,1}, {533,0,565,1},
        {99,1,138,0}, {196,0,415,1}, {353,0,370,1}, {539,1,554,0},
        {99,0,138,1}, {199,0,467,1}, {364,0,554,1}
    };

    // TRIN1 - pary tylko dla wartosci PRAWDA
    const unsigned short int m_trin1[Q_TRIN1][2] =
    {
        {6,478}, {62,272}, {141,464}, {318,450}, {12,166}, {91,247}, {167,342}, {40,224}, {95,303}, {209,351}, {53,208}, {99,314}, {261,471}
    };

    // TRIN2 - pary tylko dla wartosci FALSZ
    const unsigned short int m_trin2[Q_TRIN2][2] =
    {
        {9,56}, {75,303}, {265,353}, {405,444}, {49,167}, {165,472}, {273,561}, {73,239}, {262,275}, {306,383}
    };

    const unsigned short int m_norms[Q_SCALES][Q_NORMS] =
    {
        {9,56}, {75,303}, {265,353}, {405,444}, {49,167}, {165,472}, {273,561}, {73,239}, {262,275}, {306,383}
    };

    const std::string questions[Q_QUESTIONS] =
    {
        "Pytanie numer 1",
        "Pytanie numer 2",
        "Pytanie numer 3",
        "Pytanie numer 4",
        "Pytanie numer 5",
        "Pytanie numer 6",
        "Pytanie numer 7",
        "Baaaardzo długie pytanie numer 8 dotyczace wszsytkiego co się tyczy wszystkich o wszechobecnej wszechności!"
    };

    class Calc
    {
        public:
            Calc();
            virtual ~Calc();
            bool raw_answers[Q_QUESTIONS];
    };
}

#endif // MMPI2_HPP
