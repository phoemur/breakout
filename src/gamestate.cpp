#include "gamestate.h"
#include "intro.h"
#include "level1.h"
#include "texture.h"
#include "font.h"
#include "locator.hpp"
#include "mainwindow.h"

#include <SDL.h>

GameStates GameState::curr_state = GameStates::Intro;
GameStates GameState::next_state = GameStates::Null;
GameState::~GameState() noexcept = default;

void won()
{
    auto* win = Locator<MainWindow>::get();
    Texture back, t;
    back.loadFromFile("breakout_assets/background.jpg");
    Font f;
    f.loadFromFile("./breakout_assets/Purisa-BoldOblique.ttf", 30);
    t.loadFromRenderedText("YOU WIN!!!", f,SDL_Color{0xFF,0,0,0xFF});

    win->clear();
    back.render(0,0);
    t.render(static_cast<int>((win->getWidth() - t.getWidth()) / 2),
             static_cast<int>((win->getHeight() - t.getHeight()) / 2));
    win->update();

    SDL_Delay(2000);
}

void lost()
{
    auto* win = Locator<MainWindow>::get();
    Texture back, t;
    back.loadFromFile("breakout_assets/background.jpg");
    Font f;
    f.loadFromFile("./breakout_assets/Purisa-BoldOblique.ttf", 30);
    t.loadFromRenderedText("YOU LOST!!!", f,SDL_Color{0xFF,0,0,0xFF});

    win->clear();
    back.render(0,0);
    t.render(static_cast<int>((win->getWidth() - t.getWidth()) / 2),
             static_cast<int>((win->getHeight() - t.getHeight()) / 2));
    win->update();

    SDL_Delay(2000);
}

void changeState(std::unique_ptr<GameState>& state)
{
    if (GameState::next_state != GameStates::Null) {
        switch (GameState::next_state) {
            case GameStates::Intro:
                state.reset(nullptr);
                state = std::make_unique<Intro>();
                break;
            case GameStates::Level1:
                state.reset(nullptr);
                state = std::make_unique<Level1>();
                break;
            case GameStates::Won:
                won();
                GameState::next_state = GameStates::Intro;
                state.reset(nullptr);
                state = std::make_unique<Intro>();
                break;
            case GameStates::Lost:
                lost();
                GameState::next_state = GameStates::Intro;
                state.reset(nullptr);
                state = std::make_unique<Intro>();
                break;
            default:
                break;
        }

        GameState::curr_state = GameState::next_state;
        GameState::next_state = GameStates::Null;
    }
}
