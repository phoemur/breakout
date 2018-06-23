#include "level1.h"
#include "locator.hpp"
#include "mainwindow.h"

#include <SDL.h>

Level1::Level1()
    : win{Locator<MainWindow>::get()},
      background {},
      colOb{win->getWidth(), win->getHeight()},
      audio{},
      b((win->getWidth() + 200) / 2, win->getHeight() - 55, 3.0, 3.0),
      p((win->getWidth() + 100) / 2, win->getHeight() - 50),
      bricks{}
{
    background.loadFromFile("breakout_assets/background.jpg");

    // Add observers
    b.addObserver(&audio);
    b.addObserver(&colOb);
    p.addObserver(&colOb);

    // Create Bricks
    for (int i=40; i<win->getWidth() - 40; i += 80 ) {
        for (int j=40; j <200; j += 30) {
            bricks.push_back(std::make_unique<Rect>(i, j, 80, 30, SDL_Color{0,0,0,0xFF}, SDL_Color{0xFF,0xFF,0,0xFF}));
            auto* r = bricks.back().get();
            r->addObserver(&colOb);
        }
    }

}

void Level1::handle_events()
{
    SDL_Event e;

    while (SDL_PollEvent(&e) != 0) {
        if (e.type == SDL_QUIT) {
            GameState::next_state = GameStates::Quit;
        }
        else if (e.type == SDL_MOUSEBUTTONDOWN) {
            b.is_moving = true;
        }
        else {
            p.handleEvents(e);
        }
    }
}

void Level1::logic()
{
    b.move();
}

void Level1::render()
{
    win->clear();

    background.render(0,0);
    for (auto& br: bricks) {
        br->render();
    }
    b.render();
    p.render();

    win->update();
}
