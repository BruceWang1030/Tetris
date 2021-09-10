#ifndef PARSER_H
#define PARSER_H

#include <vector>
#include <string>
#include <map>
#include <memory>
#include "../include/commands/Command.h"

class Parser
{
    // Specification fields:

	// commandNames_ = map of the shortest unique prefix as keys to the full command  names
	// blockCommands_ = vector of all the block commands

    std::map<std::string, std::string> commandNames_ =
        {{"lef", "left"},
         {"ri", "right"},
         {"do", "down"},
         {"cl", "clockwise"},
         {"co", "counterclockwise"},
         {"dr", "drop"},
         {"levelu", "levelup"},
         {"leveld", "leveldown"},
         {"n", "norandom"},
         {"ra", "random"},
         {"s", "sequence"},
         {"re", "restart"},
         {"h", "hint"},
         {"I", "blocktype"},
         {"J", "blocktype"},
         {"L", "blocktype"},
         {"S", "blocktype"},
         {"Z", "blocktype"},
         {"O", "blocktype"},
         {"T", "blocktype"}
         };
    
    std::vector<std::string> blockCommands_ = {"I", "J", "L", "S", "Z", "O", "T"};

    // Helper methods
    // split the user commands if there is a multiplicity or if there is a file name given
    void splitUserCommand_(const std::string &userInput, int &multiplicity, std::string &fullCommand, std::string &fileName, std::string &blockType);
    // For the sequence command: get all the commands in the command sequence file
    std::vector<std::string> fetchSequenceCommands(std::string filename);

public:

    void addCommand(std::string prefix, std::string command);
    // takes: a prefix string and a command string
    // ensures: the given pair is added to CommandNames_

    std::vector< std::vector< std::shared_ptr<Command> > > parseStringCommand(const std::string &);
    // takes: a string command
    // throws: ParseCommandInvalid if the string command is invalid
    // ensures: multiplicity, and file names are taken, and the right commands is created (multiple if multiplicity or sequence file)
    // returns: a 2D vector of commands (1 for each string command)

    // For error handling: Throws in splitUserCommand_ if the user input is invalid
    class ParseCommandInvalid
    {
        std::string command_;
    public:
        ParseCommandInvalid(std::string command) : command_(command) {}
        // ensures: initialization of this
        // takes: command
        
        std::string getCommand() const { return command_; }
        // returns: command_
    };
};

#endif