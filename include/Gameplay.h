#ifndef _GAMEPLAY_H_
#define _GAMEPLAY_H_

#include <vector>
#include <tuple>
#include <memory>
#include "./commands/Command.h"
#include "GameInfo.h"
#include "Board.h"
#include "Scoreboard.h"
#include "Subject.h"
#include "./levels/Level.h"

class Command;

class Gameplay : public Subject
{
public:
    // Constructor
    Gameplay(std::string blockSequenceFile, int startLevel);

    // GETTERS
    std::shared_ptr<Block> getCurrBlock() const;
    std::shared_ptr<Block> getNextBlock() const;
    std::shared_ptr<Block> getHintBlock() const;
    std::shared_ptr<Board> getBoard() const;
    std::shared_ptr<Scoreboard> getScoreboard() const;
    std::shared_ptr<HintGenerator> getHintGen() const;
    std::shared_ptr<Board> getBoardState() const;
    int getStartLevel() const;
    std::string getBlockSequenceFile() const;
    std::string getCommandSequenceFile() const;
    std::shared_ptr<Level> getLevel() const;
    bool getRestarting() const;
    bool isShowGameOver() const;
    bool isAIMode() const;

    // SETTERS
    void setCurrBlock(std::shared_ptr<Block>);
    void setNextBlock(std::shared_ptr<Block>);
    void setHintBlock(std::shared_ptr<Block>);
    void setBoard(std::shared_ptr<Board> newBoard);
    void setScoreboard(std::shared_ptr<Scoreboard> newScoreboard);
    void setHintGen(std::shared_ptr<HintGenerator> hintGen);
    void setStartLevel(int startLevel);
    void setBlockSequenceFile(std::string file);
    void setCommandSequenceFile(std::string file);
    void setLevel(int level);
    void setRestarting(bool isRestarting);
    void setAIMode(bool AIMode);
    void setShowGameOver(bool showGameOver);

    void startTurn();
    void updateScore(bool isDropCmd);
    bool isGameOver();
    std::vector<std::shared_ptr<Command>> modifyCommands(std::vector<std::vector<std::shared_ptr<Command>>>);

    void playTurnAI();
    // modifies: current block
    // ensures: the current Block is set to the Hint Block

    /* Block Generation */
    void generateBlock(std::string blockType);

    /* Moves */
    bool moveLeft(std::shared_ptr<Block>);
    bool moveRight(std::shared_ptr<Block>);
    bool moveDown(std::shared_ptr<Block>);
    void dropBlock();

    /* Rotations */
    void rotateClockwise();
    void rotateCounterClockwise();

    /* Level */
    void levelUp();
    void levelDown();

    void noRandom(std::string fileName);
    void random();
    void restart();
    void useSequence();
    void generateHint();

private:
    // HELPERS
    bool hasCollision(int x, int y, std::vector<std::vector<char>> currRotation);
    void addBlockToBoard(std::shared_ptr<Block> block, std::shared_ptr<Board> board) const;
    void addToScore(int pointsToAdd);
    void dropBrownBlockToBoard(std::shared_ptr<Block> bblk);

    // Private Implementation
    std::shared_ptr<GameInfo> gameInfo_;
    friend class HintGenerator;
};

#endif