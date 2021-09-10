#include "../include/HintGenerator.h"
#include "../include/Gameplay.h"
#include "../include/BlockFactory.h"
using namespace std;


// Calculate the score of a given drop location
int HintGenerator::calculateScore(Gameplay* gameplay, shared_ptr<Block> hintBlock)
{
    int score = 0;

    // Check for height and add to score
    tuple<int, int> hintCoords = hintBlock->getCoordinates();
    vector<vector<char>> hintRotation = hintBlock->getCurrRotation();
    score += hintRotation.size() + (BOARD_NUM_ROWS - 1 - get<1>(hintCoords));

    // Check for empty space next and add to score
    vector<int> xToCheck{-1, -1, -1, -1};

    for (int blockY = 0; blockY < hintRotation.size(); blockY++)
    {
        for (int blockX = 0; blockX < hintRotation.at(blockY).size(); blockX++)
        {
            if (hintRotation.at(blockY).at(blockX) != ' ')
                xToCheck.at(blockX) = get<1>(hintCoords) - hintRotation.size() + blockY + 1 + 1;
        }
    }

    shared_ptr<Board> board = gameplay->getBoard();
    for (int x = 0; x < xToCheck.size(); x++)
    {
        if (xToCheck.at(x) != -1)
        {
            int boardX = get<0>(hintCoords) + x;
            score += (2 * board->getNextNonEmpty(xToCheck.at(x), boardX));
        }
    }
    
    return score;
}

// Get the lowest score drop location
void HintGenerator::generateHint(Gameplay* gameplay)
{
    shared_ptr<Block> currBlock = gameplay->getCurrBlock();
    shared_ptr<Block> hintBlock = BlockFactory::createBlock(string(1, currBlock->getBlockChar()) + "Block");

    // X and Y correspond to bottom-left cell in current block
    tuple<int, int> hintCoords = currBlock->getCoordinates();
    int hintY = get<1>(hintCoords);
    get<0>(hintCoords) = 0;
    
    // Keeps track of every possible drop location's score (maximum of 11 entries)
    // tuple: x, y, rotation
    map<int, tuple<int, int, int>> columnScores;

    for (int rotation = 0; rotation < 4; rotation++)
    {
        hintBlock->setCoordinates(hintCoords);
        hintBlock->setRotation(rotation);
        if (gameplay->hasCollision(get<0>(hintCoords), get<1>(hintCoords), hintBlock->getCurrRotation()))
            continue;

        bool movedRight = true;
        while (movedRight)
        {
            tuple<int, int> movedHintCoords = hintBlock->getCoordinates();
            bool canMoveDown = true;
            while (canMoveDown)
            {
                canMoveDown = gameplay->moveDown(hintBlock);
            }
            int colScore = calculateScore(gameplay, hintBlock);
            const tuple<int, int> &currHintCoords = hintBlock->getCoordinates();
            columnScores[colScore] = make_tuple(get<0>(currHintCoords), get<1>(currHintCoords), rotation);
            
            hintBlock->setCoordinates(movedHintCoords);
            movedRight = gameplay->moveRight(hintBlock);
        }
    }

    // Find lowest score
    tuple <int,int,int> hintInfo = columnScores.begin()->second;
    get<0>(hintCoords) = get<0>(hintInfo);
    get<1>(hintCoords) = get<1>(hintInfo);
    hintBlock->setCoordinates(hintCoords);

    hintBlock->setRotation(get<2>(hintInfo));
    hintBlock->setCharToHint();
    gameplay->setHintBlock(hintBlock);
}
