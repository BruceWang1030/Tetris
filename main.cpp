#include <iostream>
#include <sstream>
#include <string>
#include <memory>
#include <cstdlib>

#include "include/Controller.h"
#include "include/Gameplay.h"
#include "include/TextDisplay.h"
#include "include/GraphicDisplay.h"

using namespace std;

int main(int argc, char *argv[])
{
    // Default values for command line flags
    string arg;
    string scriptFile = "sequence.txt";
    bool text = false;
    int seed = 1;
    int level = 0;
    bool aimode = false;
    bool showGameOver = false;

    // If the user uses flags, change the value of the default variables
    if (argc >= 2)
    {
        int argInd = 1;
        while (argInd < argc)
        {
            arg = argv[argInd];
            if (arg == "-text")
            {
                text = true;
            }
            else if (arg == "-seed")
            {
                seed = atoi(argv[argInd + 1]);
                srand(seed);

                argInd++;
            }
            else if (arg == "-scriptfile")
            {
                scriptFile = argv[argInd + 1];
                argInd++;
            }
            else if (arg == "-startlevel")
            {
                level = atoi(argv[argInd + 1]);
                argInd++;
            }
            else if (arg == "-aimode")
            {
                aimode = true;
                argInd++;
            }
            else if (arg == "-showGameOver")
            {
                showGameOver = true;
                argInd++;
            }
            else
            {
                cout << "Command line argument not found." << endl;
                argInd = argc;
            }
            argInd++;
        }
    }

    // Create all 3 components of the MVC pattern (the Gameplay is a facade pattern)
    shared_ptr<Gameplay> gamePlay(new Gameplay(scriptFile, level));
    // Create the 2 observers
    shared_ptr<TextDisplay> textDisplay(new TextDisplay(std::cout, gamePlay));
    shared_ptr<GraphicDisplay> graphicDisplay = (text) ? nullptr : make_shared<GraphicDisplay>(gamePlay);
    // Create the controller
    Controller controller = Controller(gamePlay, graphicDisplay, aimode);

    // Attach the textDisplay (requires access to shared_ptr)
    gamePlay->attach(textDisplay);
    // Attach the graphicDisplay (requires access to shared_ptr)
    if (graphicDisplay != nullptr)
    {
        gamePlay->attach(graphicDisplay);
    }
    //enable bonus feature show Game Over
    gamePlay->setShowGameOver(showGameOver);

    while (!controller.shouldTerminate())
    {
        controller.playTurn();
    }

    // Detach the textDisplay
    gamePlay->detach(textDisplay);
    // Detach the graphicDisplay
    if (graphicDisplay != nullptr)
    {
        gamePlay->detach(graphicDisplay);
    }

    return 0;
}
