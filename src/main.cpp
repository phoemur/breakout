#include "mainwindow.h"
#include "gamestate.h"
#include "intro.h"

#include <SDL.h>
#include <memory>

int main()
{
    // MainWindow must be the first object instanciated
    MainWindow win (640, 480, "Breakout game remake");
    win.setIcon("./breakout_assets/ball.png");

    std::unique_ptr<GameState> currentState {std::make_unique<Intro>()};

    while (GameState::curr_state != GameStates::Quit) {
        currentState->handle_events();
        currentState->logic();
        currentState->render();

        changeState(currentState);
    }

    return 0;
}
