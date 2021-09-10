#include "../include/Parser.h"
#include "../include/CommandFactory.h"
#include "../include/commands/Command.h"
#include "../include/commands/BlockTypeCommand.h"
#include "../include/commands/NoRandomCommand.h"

#include <map>
#include <vector>
#include <string>
#include <cctype>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <memory>

using namespace std;

void Parser::addCommand(string prefix, string command){
    commandNames_[prefix] = command;
}

// Get the multiplicity (if exists), full command name and file name (if exists)
void Parser::splitUserCommand_(const string &userInput, int &multiplicity, string &fullCommand, string &fileName, string &blockType)
{
    // Get all the prefix digits
    int digitEnd = 0;
    while (isdigit(userInput[digitEnd]))
    {
        digitEnd++;
    }

    // Remove the multiplicity (if exists)
    string command = userInput.substr(digitEnd);

    // Find space in command name (for file name detection) and split if there is
    size_t space = command.find(" ");
    if (space != std::string::npos)
    {
        int spaceInd = static_cast<int>(space);
        fileName = command.substr(spaceInd + 1);
        command = command.substr(0, spaceInd);
    }

    // If the command is empty, error
    if (command.size() == 0)
        throw ParseCommandInvalid(command);

    // Then we check all the prefixes one by one for a full command name
    string subCommand;
    for (int index = 0; index <= command.size(); index++)
    {
        subCommand = command.substr(0, index);
        if (commandNames_.count(subCommand) > 0)
        {
            fullCommand = commandNames_[subCommand];
            if (find(blockCommands_.begin(), blockCommands_.end(), subCommand) != blockCommands_.end())
                blockType = subCommand;
            break;
        }
    }

    // If the commands accepts a multiplicity, we set it
    if (digitEnd && fullCommand != "restart" && fullCommand != "hint" && fullCommand != "random" && fullCommand != "norandom")
    {
        multiplicity = stoi(userInput.substr(0, digitEnd));
        if (multiplicity < 0)
            throw ParseCommandInvalid(command);
    }

    // exception if subcommand not a substring of fullcommand (non blocktype)
    if (blockType == "" && fullCommand.find(command) == string::npos)
        throw ParseCommandInvalid(command);

    // exception if blocktype command and original command not 1 letter
    if (blockType.length() > 0 && command.length() > 1)
        throw ParseCommandInvalid(command);
}

// For sequence file commands (get them)
vector<string> Parser::fetchSequenceCommands(string filename)
{
    // open the sequence file
    ifstream sequenceFile(filename);
    vector<string> out;
    string cmd;

    // if the file exists (is opened)
    if (sequenceFile.is_open())
    {
        while (sequenceFile >> cmd) // for each string command, we append it to out
            out.emplace_back(cmd);

        sequenceFile.close();
    }
    return out;
}

// Parse a string command
vector<vector<shared_ptr<Command>>> Parser::parseStringCommand(const string &userInput)
{
    // Variable to hold multiplicity, full command name and file name
    int multiplicity = 1;
    string fullCommand = "";
    string fileName = "";
    string blockType = "";
    vector<vector<shared_ptr<Command>>> outCommands;

    // Try splitting the commands, else throw ParseCommandInvalid
    try
    {
        splitUserCommand_(userInput, multiplicity, fullCommand, fileName, blockType);
    }
    catch (Parser::ParseCommandInvalid &e)
    {
        throw ParseCommandInvalid(e.getCommand());
    }

    // If the command is sequence, intercept and process every string command in the file
    vector<shared_ptr<Command>> tempOut;
    if (fullCommand == "sequence") 
    {
        vector<string> sequenceCommands = fetchSequenceCommands(fileName);
        for (auto stringCmd : sequenceCommands)
        {
            vector<vector<shared_ptr<Command>>> tempSequenceOut = parseStringCommand(stringCmd);
            outCommands.insert(outCommands.end(), tempSequenceOut.begin(), tempSequenceOut.end());
        }
        return outCommands;
    }

    // Create commands x multiplicity for each command
    for (int commandRepeat = 0; commandRepeat < multiplicity; commandRepeat++)
    {
        shared_ptr<Command> cmd = CommandFactory::createCommand(fullCommand);
        cmd->setFileName(fileName);
        cmd->setBlockType(blockType);
        tempOut.emplace_back(cmd);
        outCommands.emplace_back(tempOut);
        tempOut.clear();
    } 

    return outCommands;
}
