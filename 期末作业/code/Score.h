#ifndef SCORE_H
#define SCORE_H


class Score
{
public:
    void SetScore(int ChineseScore, int MathScore);
    int GetScore();//获取学生总成绩
private:
    int m_chineseScore;//语文成绩
    int m_mathScore;   //数学成绩
};

#endif // SCORE_H
