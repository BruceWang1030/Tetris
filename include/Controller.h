#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <vector>
#include <string>
#include <memory>
#include "Parser.h"
#include "Gameplay.h"
#include "GraphicDisplay.h"

// Note: the GraphicDisplay is passed in following the MVC pattern, however we do not make use of it since 
//       we do not have user inputs that are handled via the display

class Controller
{
    // Specification fields:

	// parser_ = Parser object
	// gamePlay_ = Gameplay pointer (MVC pattern)
	// graphicDisplay_ = GraphicDisplay pointer (MVC pattern)

    Parser parser_;
    std::shared_ptr<Gameplay> gamePlay_;
    std::shared_ptr<GraphicDisplay> graphicDisplay_;

    bool shouldTerminate_;
    
public:
    
    Controller(std::shared_ptr<Gameplay> const &gamePlay, std::shared_ptr<GraphicDisplay> const &graphicDisplay, bool aimode): 
        gamePlay_(gamePlay), graphicDisplay_(graphicDisplay), parser_(Parser()), shouldTerminate_(false) {
            if(aimode){
                parser_.addCommand("a", "aimode");
            }
        };
    // takes: gamePlay pointer, GraphicDisplay pointer
    // ensures: initialization of this

    void playTurn();
    // ensures: user is prompted to input a command, and executes all commands
    // modifies: gamePlay_ (and potentially parser_)
    
    
    void setShouldTerminate(bool shouldTerminate);
    // takes: bool
    // ensures: shouldTerminate_ is set to the input bool

    bool shouldTerminate() const;
    // ensures: nothing is changed
    // returns shouldTerminate_
};

#endif
