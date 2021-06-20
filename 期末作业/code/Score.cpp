#include "Score.h"

void Score::SetScore(int ChineseScore, int MathScore)
{
    m_chineseScore = ChineseScore;
    m_mathScore = MathScore;
}

int Score::GetScore()
{
    return m_chineseScore + m_mathScore;
}
