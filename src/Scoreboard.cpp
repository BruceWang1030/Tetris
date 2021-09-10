#include "../include/Scoreboard.h"

// Getters
int Scoreboard::getScore() const
{
    return score_;
}

int Scoreboard::getHighScore() const
{
    return highScore_;
}

// Setters
void Scoreboard::setScore(const int score)
{
    score_ = score;
    setHighScore(score);
}

void Scoreboard::setHighScore(const int score)
{
    if (score > highScore_)
    {
        highScore_ = score;
    }
}