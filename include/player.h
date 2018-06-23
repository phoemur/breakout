#ifndef PLAYER_H
#define PLAYER_H

#include "rect.h"

class MainWindow;

class Player : public Rect {
    MainWindow* win;
public:
    Player(int x, int y);
    Player(const Player&) = default;
    Player& operator=(const Player&) = default;
    Player(Player&&) = default;
    Player& operator=(Player&&) = default;

    void handleEvents(SDL_Event& e);
};

#endif // PLAYER_H
