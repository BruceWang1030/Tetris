#ifndef _SCOREBOARD_H_
#define _SCOREBOARD_H_

class Scoreboard
{

    // Specification fields:

	// score_ = integer score to keep track of 
	// highScore_ = integer high score to keep track of

    int score_;
    int highScore_;

public:

    Scoreboard(int score = 0, int highScore = 0) : score_(score), highScore_(highScore) {}
    // takes: initial score, initial high score
    // ensures: initialization of this

    int getScore() const;
    // returns: score

    int getHighScore() const;
    // returns: high score

    void setScore(const int score);
    // takes: int score
    // ensures: score_ field is set to score 
    // modifies: score_

    void setHighScore(const int score);
    // takes: int score
    // ensures: highScore_ field is set to score 
    // modifies: highScore_
};

#endif