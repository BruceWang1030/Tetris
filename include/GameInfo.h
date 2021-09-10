#ifndef _GAMEINFO_H_
#define _GAMEINFO_H_

#include <memory>
#include "./blocks/Block.h"
#include "Board.h"
#include "Scoreboard.h"
#include "./levels/Level.h"
#include "HintGenerator.h"

class Level;
class HintGenerator;

struct GameInfo
{
    std::shared_ptr<Block> currBlock_;
    std::shared_ptr<Block> nextBlock_;
    std::shared_ptr<Block> hintBlock_;
    std::shared_ptr<Board> board_;
    std::shared_ptr<Scoreboard> scoreboard_;
    std::shared_ptr<HintGenerator> hintGen_;

    std::string blockSequenceFile_;
    std::string commandSequenceFile_;
    int startLevel_;

    std::shared_ptr<Level> currLevel_;
    bool isRestarting_ = false;
    bool isAIMode_;
    bool isShowingGameOver = false;
};

#endif