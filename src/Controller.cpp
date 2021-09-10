#include <string>
#include <vector>
#include <iostream>
#include <memory>
#include "../include/commands/Command.h"
#include "../include/Controller.h"
#include "../include/Parser.h"

using namespace std;

// Getters + Setters
void Controller::setShouldTerminate(bool shouldTerminate){
    shouldTerminate_ = shouldTerminate;
}
bool Controller::shouldTerminate() const{
    return shouldTerminate_;
}

// Prompt user command and execute the command
void Controller::playTurn()
{
    string command;
    vector<vector<shared_ptr<Command>>> commandVector2D;

    // gamePlay start turn setup (hint is set back to nullptr)
    gamePlay_->startTurn();
    gamePlay_->setHintBlock(nullptr);

    // Check if in AI Mode
    if(gamePlay_->isAIMode()){
        // Check if the game is over
        if(gamePlay_->isGameOver()){
            // Exit AI Mode
            gamePlay_->setAIMode(false);
            // Print game over
            cout << "I'm just an AI...This is the best I can do! Enter \"restart\" to play again." << endl;
        } else {
            // Play AI turn
            gamePlay_->playTurnAI();
            gamePlay_->updateScore(true);
        }
        return;
    }

    // Prompt user input until command is valid
    while (commandVector2D.size() == 0)
    {
        getline(cin, command);
        if (cin.fail())
        {
            setShouldTerminate(true);
            return;
        }

        // Parse the user input to get the corresponding Command objects
        try
        {
            commandVector2D = parser_.parseStringCommand(command);
        }
        catch(Parser::ParseCommandInvalid &e)
        {
            cout << e.getCommand() << " is not a valid command." << endl;
        }
    }

    // Modify + flatten commandVector2D
    vector<shared_ptr<Command>> commandVector = gamePlay_->modifyCommands(commandVector2D);

    // Execute commands
    for (auto commandObj : commandVector)
    {
        if (gamePlay_->isGameOver() && !commandObj->isRestartCommand())
            return;
        commandObj->execute(*gamePlay_);
        // Update the score
        gamePlay_->updateScore(commandObj->isDropCommand());
        // Check if game is over
        if (gamePlay_->isGameOver())
        {
            cout << "Game Over! Enter \"restart\" to play again." << endl;
            return;
        }
    }
}