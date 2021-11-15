#include <SDL.h>
#include <GL/glew.h>
#include <iostream>
#include <GL/GLU.h>
#include <string>

#include "./engine/Timer.h"
#include "./engine/Window.h"
#include "./engine/Game.h"

using std::cin;
using std::cout;
using std::endl;
using std::string;

constexpr int SCREEN_WIDTH = 640;
constexpr int SCREEN_HEIGHT = 480;
bool aiControlledPaddle = false;

void gameplayLoop(Game game, Window window, Timer timer, float dt)
{
    string playerInput;
    cout << "Welcome lover of Tennis, grab a seat and let's play!" << endl;

    if (game.getIsInit())
    {
        cout << "Would you like to play against a super strong AI?" << endl;
        cout << "If you would like that, please insert 'YES' or 'Y'" << endl;
        cin >> playerInput;
        for (int i = 0; i < playerInput.length(); i++)
        {
            playerInput[i] = tolower(playerInput[i]);
        }
        if (playerInput == "yes" || playerInput == "y")
        {
            aiControlledPaddle = true;
        }
        else if (playerInput == "no" || playerInput == "n")
        {
            aiControlledPaddle = false;
        }
        game.init(SCREEN_WIDTH, SCREEN_HEIGHT, aiControlledPaddle);
        game.load();
        game.setIsRunning(true);
        game.setIsInit(false);
    }

    while (game.getIsRunning())
    {
        dt = static_cast<float>(timer.computeDeltaTime()) / 1000.0f;
        game.handleInputs();

        game.update(dt);
        //Draw
        window.clearScreen();
        game.render();

        window.swapBuffer();
    }

    if (game.getIsGameOver())
    {
        cout << "The game is now over" << endl;
        cout << "The winner of this game is the " << game.getWinner() << " who scored 8 points" << endl;
        cout << "CONGRATULATIONS!" << endl;
        cout << "To restart the game press the SPACE button" << endl;
    }

    while (game.getIsGameOver())
    {
        game.handleInputs();
        window.clearScreen();
        if (game.getIsInit())
            gameplayLoop(game, window, timer, dt);
    }
}

int main(int argc = 0, char **argv = nullptr)
{
    //Handle args
    if (argc > 0)
    {
        for (int i = 0; i < argc; ++i)
        {
            cout << argv[i] << endl;
        }
    }

    Window window = Window("Tennis Game");
    if (!window.init(SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, false))
    {
        cout << "Error in initialising window" << endl;
        return 1;
    }

    //Get info
    const GLubyte *renderer = glGetString(GL_RENDERER);
    const GLubyte *version = glGetString(GL_VERSION);
    cout << "Renderer: " << renderer << endl;
    cout << "OpenGL version supported: " << version << endl;

    Timer timer;
    Game game;
    float dt;

    gameplayLoop(game, window, timer, dt);

    //Quit
    window.clean();

    return 0;
}